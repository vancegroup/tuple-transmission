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
#ifndef INCLUDED_EnvelopeReceiveBuffer_h_GUID_e5115905_1c09_43a9_93b6_48c9f42aa951
#define INCLUDED_EnvelopeReceiveBuffer_h_GUID_e5115905_1c09_43a9_93b6_48c9f42aa951

// Internal Includes
#include "../operations/ComputeReceiveBufferSize.h"
#include "../operations/IsIdValid.h"
#include "../operations/MessageLength.h"         // for getMessageLength
#include "MessageSizeType.h"
#include "MessageIdType.h"
#include <util/ReceiveBuffer.h>

// Library/third-party includes
#include <boost/optional.hpp>
#include <boost/assert.hpp>

// Standard includes
// - none

namespace transmission {

	namespace detail {
		/// @brief Class holding a receive buffer, and providing methods needed
		/// by Envelope types and Receiver, but that should be internal from the
		/// user's point of view.
		template<typename Collection>
		class EnvelopeReceiveBuffer {
			private:
				typedef util::ReceiveBuffer< detail::operations::ComputeReceiveBufferSize<Collection>::value > buffer_type;

			public:
				typedef EnvelopeReceiveBuffer<Collection> type;
				typedef Collection message_collection;

				typedef typename MessageSizeType<Collection>::type message_size_type;
				typedef typename buffer_type::size_type buffer_size_type;
				typedef typename buffer_type::value_type buffer_value_type;
				typedef typename buffer_type::iterator buffer_iterator;
				typedef typename buffer_type::const_iterator buffer_const_iterator;
				typedef buffer_value_type & buffer_reference;
				typedef buffer_value_type const & buffer_const_reference;

				/// @name Buffer Methods for Data Source Use
				/// @brief These methods interact with the internal buffer
				/// in ways primarily useful for putting data from platform-specific
				/// APIs into the buffer.
				/// @{

				/// @brief Returns the available (unused) number of spaces for
				/// elements left in the buffer.
				///
				/// The buffer may be of a fixed size, so over-filling it would
				/// be bad.
				buffer_size_type bufferAvailableSpace() const {
					return recv_buf.max_size() - recv_buf.size();
				}

				/// @brief Append the data in the half-open iterator range [input_begin, input_end)
				template<typename InputIterator>
				void bufferAppend(InputIterator input_begin, InputIterator input_end) {
					recv_buf.push_back(input_begin, input_end);
				}

				/// @brief Append a single element of data
				///
				/// @note Almost certainly less efficient for multiple
				/// elements than the overload taking an iterator range!
				void bufferAppend(buffer_const_reference element) {
					recv_buf.push_back(element);
				}

				/// @brief Request processing by the envelope to determine if
				/// the buffer contains a complete and valid message, returning
				/// the results.
				bool checkBufferForMessage() {
					typedef typename message_collection::envelope_type::base envelope_type;
					return envelope_type::template checkBufferForMessage<type>(*this);
				}

				/// @brief Returns an iterator to the start of the data portion of
				/// the buffer.
				buffer_const_iterator getDataIterator() const {
					return recv_buf.begin() + typename Collection::envelope_type::data_offset();
				}

				/// @brief Given that there is a full message in the buffer, pop it
				/// (such as for after processing is complete)
				void popMessage() {
					BOOST_ASSERT_MSG(checkBufferForMessage(), "Must have a message before we can pop it!");
					bufferPopFront(getMessageLength());
					current_message_id = boost::none_t();
				}

				/// @}


				/// @name Buffer Methods for Envelope Use
				/// @brief These methods interact with the internal buffer
				/// in ways that are primarily useful to envelope types.
				/// @{
				/// @brief How many elements are in the buffer?
				buffer_size_type bufferSize() const {
					return recv_buf.size();
				}

				/// @brief Is the buffer empty?
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

				void bufferEnsureSpace(buffer_size_type n) const {
					recv_buf.ensure_space(n);
				}

				template<typename Functor>
				buffer_size_type bufferFromFunctorRef(Functor & f, buffer_size_type n) {
					return recv_buf.bufferFromExternalFunctorRef(f, n);
				}
				/// @}

				/// @name Message-related Methods
				/// @{
				/// @brief Callback function used by an envelope to indicate what message ID we may have.
				///
				/// The Receive Handler caches this value for message-related lookup functions, and
				/// for use when we actually have a full message.
				void setCurrentMessageId(MessageIdType id) {
					if (detail::operations::isIdValid<message_collection>(id)) {
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
				MessageIdType getCurrentMessageId() const {
					return *current_message_id;
				}

				/// @brief Looks up and returns the message length for the current message ID
				///
				/// Must be preceded by a call to setCurrentMessageId()
				message_size_type getMessageLength() const {
					BOOST_ASSERT(isCurrentMessageIdValid());
					return ::transmission::detail::operations::getMessageLength<message_collection>(*current_message_id);
				}
				/// @}
			private:

				boost::optional<MessageIdType> current_message_id;
				buffer_type recv_buf;
		};
	} // end of namespace detail
} // end of namespace transmission

#endif // INCLUDED_EnvelopeReceiveBuffer_h_GUID_e5115905_1c09_43a9_93b6_48c9f42aa951
