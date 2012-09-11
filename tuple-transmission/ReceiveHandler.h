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
#ifndef INCLUDED_ReceiveHandler_h_GUID_e5115905_1c09_43a9_93b6_48c9f42aa951
#define INCLUDED_ReceiveHandler_h_GUID_e5115905_1c09_43a9_93b6_48c9f42aa951

// Internal Includes
#include "detail/ComputeReceiveBufferSize.h"
#include "detail/IsIdValid.h"
#include "detail/MessageLength.h"         // for getMessageLength
#include "MessageCollectionTypes.h"
#include <util/ReceiveBuffer.h>

// Library/third-party includes
#include <boost/optional.hpp>
#include <boost/assert.hpp>

// Standard includes
// - none

namespace transmission {

	template<typename Collection>
	class ReceiveHandler {
		private:
			typedef util::ReceiveBuffer< detail::ComputeReceiveBufferSize<Collection>::value > buffer_type;

		public:
			typedef Collection message_collection;
			typedef MessageCollectionTypes<Collection> types;

			typedef typename types::message_id_type message_id_type;
			typedef typename types::message_size_type message_size_type;
			typedef typename buffer_type::size_type buffer_size_type;
			typedef typename buffer_type::value_type buffer_value_type;
			typedef buffer_value_type & buffer_reference;
			typedef buffer_value_type const & buffer_const_reference;

			buffer_size_type bufferSize() const {
				return recv_buf.size();
			}

			bool bufferEmpty() const {
				return recv_buf.empty();
			}

			/// @brief Buffer front element access function - const
			buffer_const_reference bufferFront() const {
				return recv_buf.front();
			}

			/// @brief Buffer front element access function
			buffer_reference bufferFront() {
				return recv_buf.front();
			}


			/// @brief Wraps pop_front for contained buffer.
			buffer_value_type bufferPopFront(buffer_size_type count = 1) {
				return recv_buf.pop_front(count);
			}

			/// @brief Buffer const element access function
			buffer_const_reference buffer(buffer_size_type i) const {
				return recv_buf[i];
			}

			/// @brief Buffer element access function
			buffer_reference buffer(buffer_size_type i) {
				return recv_buf[i];
			}

			/// @name Message-related Methods
			/// @{
			/// @brief Callback function used by an envelope to indicate what message ID we may have.
			///
			/// The Receive Handler caches this value for message-related lookup functions, and
			/// for use when we actually have a full message.
			void setCurrentMessageId(message_id_type id) {
				if (detail::isIdValid<message_collection>(id)) {
					current_message_id = id;
				} else {
					current_message_id = boost::none_t();
				}
			}

			/// @brief Inquires if the last-set message ID is valid.
			///
			/// Must be preceded by a call to setCurrentMessageId()
			bool isCurrentMessageIdValid() const {
				if (current_message_id) {
					return true;
				} else {
					return false;
				}
			}

			/// @brief Gets current message ID
			///
			/// @note Behavior when no valid ID is set is undefined!
			message_id_type getCurrentMessageId() const {
				return *current_message_id;
			}

			/// @brief Looks up and returns the message length for the current message ID
			///
			/// Must be preceded by a call to setCurrentMessageId()
			message_size_type getMessageLength() const {
				BOOST_ASSERT(isCurrentMessageIdValid());
				return *::transmission::detail::getMessageLength<message_collection>(*current_message_id);
			}
			/// @}
		private:

			boost::optional<message_id_type> current_message_id;
			buffer_type recv_buf;
	};
} // end of namespace transmission

#endif // INCLUDED_MessageHandler_h_GUID_e5115905_1c09_43a9_93b6_48c9f42aa951
