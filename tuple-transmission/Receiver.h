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
			typedef typename receive_buffer_type::buffer_const_iterator buffer_const_iterator;
			typedef Receiver<MessageCollection> receiver_type;
		public:
			typedef typename receive_buffer_type::buffer_size_type buffer_size_type;

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
				: _invoker(&receiver_type::deserializeAndInvoke<MessageFunctor>)
				, _functorPointer(&handler) {}

			/// @brief Function to change the handler object used for future
			/// calls to processMessages
			template<typename MessageFunctor>
			void setHandler(MessageFunctor & handler) {
				_invoker = &receiver_type::deserializeAndInvoke<MessageFunctor>;
				_functorPointer = &handler;
			}

			/// @brief Returns the number of bytes of available space in
			/// the buffer.
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
				return processMessagesImpl();
			}

		private:
			/// @brief Internal function to recursively process messages.
			///
			/// When it finds a full one, it calls through the function
			/// pointer to invoke the handler.
			uint8_t processMessagesImpl(uint8_t msgCount = 0) {
				if (_recv.checkBufferForMessage()) {
					const MessageIdType id = _recv.getCurrentMessageId();
					// Record this message as the last handled ID
					_lastMessageId = id;

					// Invoke the handler on this message.
					(*_invoker)(id, _functorPointer, _recv.getDataIterator());

					// Remove handled message
					_recv.popMessage();

					// Repeat until no more.
					return processMessagesImpl(msgCount + 1);
				}
				return msgCount;
			}


			/// @brief Static function template to invoke the handler on a
			/// message we already know is there.
			///
			/// Instantiated with knowledge of the message functor's type so
			/// it can safely cast it back from a void * - this is the only
			/// code that actually requires knowledge of the message functor.
			///
			/// Doesn't technically need to be a member, but it makes it easier
			/// because we don't have to repeat types as template parameters.
			template<typename MessageFunctorType>
			static void deserializeAndInvoke(MessageIdType msgID, void * functorPointer, buffer_const_iterator it) {
				typedef typename MessageCollection::envelope_type::serialization_policy serialization_policy;
				typedef typename MessageCollection::message_types message_types;
				detail::operations::deserializeAndInvoke<message_types, serialization_policy>(
				    msgID,
				    *static_cast<MessageFunctorType *>(functorPointer),
				    it
				);
			}

			/// @brief Typedef for a function pointer to the signature of deserializeAndInvoke -
			/// note that it does not depend on MessageFunctorType since it takes a void *
			/// and can safely cast that back inside.
			typedef void (*InvokerFnPtr)(MessageIdType, void *, buffer_const_iterator);

			/// @brief Internal receive buffer wrapper object, used by this class
			/// and by the envelope.
			receive_buffer_type _recv;

			/// @brief Pointer to the invoker function that knows the real,
			/// static type of _functorPointer
			InvokerFnPtr _invoker;

			/// @brief A pointer to the user-supplied handler functor, stored
			/// as void * to not require parameterization of this class,
			/// and passed to _invoker which knows what it really is.
			void * _functorPointer;
			boost::optional<MessageIdType> _lastMessageId;
	};
} // end of namespace transmission

#endif // INCLUDED_Receiver_h_GUID_9e1418a4_6874_426b_9113_cc5e57ee3fb5
