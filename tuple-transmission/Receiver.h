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
#include "Receiver_fwd.h"
#include "detail/types/EnvelopeReceiveBuffer.h"
#include "detail/types/MessageIdType.h"
#include "detail/operations/DeserializeAndInvoke.h"
#include "detail/bases/ReceiveAdapterBase_fwd.h"

// Library/third-party includes
#include <boost/optional.hpp>

// Standard includes
// - none

namespace transmission {

	/** @brief Wrapper class for functors that handle messages.

		Pass your functor class name as the first template argument,
		and your message collection as the second.

		You will need to write a void operator()(YourMessageType const&, [...] ) for each message
		type in the collection.  If you intend to ignore some messages,
		see transmission::PartialHandlerBase.
	*/
	template<typename MessageFunctor, typename MessageCollection>
	class Receiver {
		private:
			typedef detail::EnvelopeReceiveBuffer<MessageCollection> receive_buffer_type;
		public:
			typedef typename receive_buffer_type::buffer_size_type buffer_size_type;

			/// @brief Returns the number of bytes of available space in
			/// the buffer.
			buffer_size_type getBufferAvailableSpace() const {
				return _recv.bufferAvailableSpace();
			}

			/// @brief Function to append additional data received from your
			/// data source, for use if your source is accessible by iterators.
			template<typename InputIterator>
			void appendReceived(InputIterator input_begin, InputIterator input_end) {
				_recv.bufferAppend(input_begin, input_end);
			}

			/// @brief Function to retrieve additional data from your source,
			/// given a ReceiveAdapter for it.
			///
			/// Returns the number of bytes retrieved.
			template<typename Derived>
			buffer_size_type receiveFrom(detail::ReceiveAdapterBase<Derived> & r) {
				return _recv.bufferFromFunctorRef(r, r.getNumAvailable());
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
				typedef typename MessageCollection::envelope_type::serialization_policy serialization_policy;
				typedef typename MessageCollection::message_types message_types;
				uint8_t msgCount = 0;
				while (_recv.checkBufferForMessage()) {
					const MessageIdType id = _recv.getCurrentMessageId();
					// Record this message as the last handled ID
					_lastMessageId = id;

					// Invoke the handler on this message.
					detail::operations::deserializeAndInvoke<message_types, serialization_policy>(
					    _recv.getCurrentMessageId(),
					    getMessageHandler(),
					    _recv.getDataIterator()
					);

					// Remove handled message
					_recv.popMessage();

					// Increment count.
					msgCount++;
				}
				return msgCount;
			}

			MessageFunctor & getMessageHandler() {
				return _functor;
			}

			MessageFunctor const & getMessageHandler() const {
				return _functor;
			}

		private:

			/// @brief Internal receive buffer wrapper object, used by this class
			/// and by the envelope.
			receive_buffer_type _recv;

			MessageFunctor _functor;

			boost::optional<MessageIdType> _lastMessageId;
	};
} // end of namespace transmission

#endif // INCLUDED_Receiver_h_GUID_9e1418a4_6874_426b_9113_cc5e57ee3fb5
