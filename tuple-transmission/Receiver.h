/** @file
	@brief Header

	@date 2012

	@author
	Ryan Pavlik
	<rpavlik@iastate.edu> and <abiryan@ryand.net>
	http://academic.cleardefinition.com/
	Iowa State University Virtual Reality Applications Center
	Human-Computer Interaction Graduate Program
*/

//          Copyright Iowa State University 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#pragma once
#ifndef INCLUDED_Receiver_h_GUID_9e1418a4_6874_426b_9113_cc5e57ee3fb5
#define INCLUDED_Receiver_h_GUID_9e1418a4_6874_426b_9113_cc5e57ee3fb5

// Internal Includes
#include "detail/types/EnvelopeReceiveBuffer.h"
#include "detail/types/MessageIdType.h"
#include "detail/operations/DeserializeAndInvoke.h"

// Library/third-party includes
#include <boost/optional.hpp>

// Standard includes
// - none

namespace transmission {

	/** @brief Class that receives messages and passes them to a handler
		you create.

		Instantiate an object of your handler class.
		Pass your message collection as the template argument to this class,
		and initialize it with your handler object.

		@note This class keeps a pointer to the handler passed in the constructor,
		so it must outlive this object!

		You will need to write a void operator()(YourMessageType const&, [...] ) for each message
		type in the collection in your handler class.  If you intend to
		ignore some messages, see transmission::PartialHandlerBase.
	*/
	template<typename MessageCollection>
	class Receiver {
		private:
			typedef detail::EnvelopeReceiveBuffer<MessageCollection> receive_buffer_type;
			typedef Receiver<MessageCollection> receiver_type;
		public:
			typedef typename receive_buffer_type::buffer_size_type buffer_size_type;
			typedef void result_type;

			/// @brief Constructor that takes a reference to your handler,
			/// and stores a pointer to it.
			///
			/// Be sure the handler you pass in will outlive this object!
			///
			/// A function pointer to a function template instantiation is
			/// used so that this class does not need to take your
			/// functor's type as a template parameter.
			template<typename MessageFunctor>
			Receiver(MessageFunctor & handler)
				: _processor(&receiver_type::processMessagesImpl<MessageFunctor>)
				, _functorPointer(&handler) {}

			buffer_size_type getBufferAvailableSpace() const {
				return _recv.bufferAvailableSpace();
			}

			/// @brief Function to append additional data received from your
			/// data source if accessible by iterators.
			template<typename InputIterator>
			void appendReceived(InputIterator input_begin, InputIterator input_end) {
				_recv.bufferAppend(input_begin, input_end);
			}

			/// @brief Function to retrieve additional data from your source,
			/// give a function to pop one byte from the source and the
			/// number of bytes available.
			///
			/// Returns the number of bytes retrieved.
			template<typename Functor, typename SizeType>
			buffer_size_type appendUsing(Functor f, SizeType bytesAvailable) {
				buffer_size_type total = getBufferAvailableSpace();
				if (bytesAvailable < total) {
					total = bytesAvailable;
				}
				_recv.bufferEnsureSpace(total);
				for (buffer_size_type i = 0; i < total; ++i) {
					_recv.bufferPushBack(f());
				}
			}

			/// @brief Returns the ID of the last message received, if applicable.
			boost::optional<MessageIdType> getLastMessageId() const {
				return _lastMessageId;
			}

			/// @brief  Triggers message processing on the buffer, calling
			/// your receive functor with any successfully received.
			///
			/// Returns the number of messages processed.
			uint8_t processMessages() {
				//return processMessagesImpl();
				return (*_processor)(*this, 0);
			}

		private:

			/// @brief Static function template to recursively process messages.
			///
			/// Instantiated with knowledge of the message functor's type so
			/// it can safely cast it back from a void * - this is the only
			/// code that actually requires knowledge of the message functor.
			template<typename MessageFunctorType>
			static uint8_t processMessagesImpl(receiver_type & self, uint8_t msgCount) {
				if (self._recv.checkBufferForMessage()) {
					typedef typename MessageCollection::envelope_type::serialization_policy serialization_policy;
					typedef typename MessageCollection::message_types message_types;

					self._lastMessageId = self._recv.getCurrentMessageId();

					detail::operations::deserializeAndInvoke<message_types, serialization_policy>(
					    self._recv.getCurrentMessageId(),
					    *static_cast<MessageFunctorType *>(self._functorPointer),
					    self._recv.getDataIterator()
					);

					// Remove handled message
					self._recv.popMessage();

					// Repeat until no more.
					return processMessagesImpl<MessageFunctorType>(self, msgCount + 1);
				}
				return msgCount;
			}

			typedef uint8_t(*MessageProcessorFn)(receiver_type & self, uint8_t);

			receive_buffer_type _recv;
			//MessageFunctor _functor;
			MessageProcessorFn _processor;
			void * _functorPointer;
			boost::optional<MessageIdType> _lastMessageId;
	};
} // end of namespace transmission

#endif // INCLUDED_Receiver_h_GUID_9e1418a4_6874_426b_9113_cc5e57ee3fb5
