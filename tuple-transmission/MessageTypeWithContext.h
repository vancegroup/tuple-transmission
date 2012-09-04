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
#ifndef INCLUDED_MessageTypeWithContext_h_GUID_1e9d05a8_141d_4197_9b93_f4afa0d5925c
#define INCLUDED_MessageTypeWithContext_h_GUID_1e9d05a8_141d_4197_9b93_f4afa0d5925c

// Internal Includes
#include "Sizeof_fwd.h"
#include "TransmissionBase_fwd.h"
#include "EnvelopeBase.h"
#include "MessageIdType.h"

// Library/third-party includes
#include <boost/mpl/equal.hpp>
#include <boost/static_assert.hpp>

// Standard includes
// - none


namespace transmission {
	namespace detail {
		template<typename MessageType, typename Envelope, typename MessageContentsType, typename TXDerived>
		inline void passMessageToEnvelopeToSend(TransmissionBase<TXDerived> & xt, MessageContentsType const & contents, MessageIdType msgId) {
			BOOST_STATIC_ASSERT_MSG((boost::mpl::equal<MessageType, MessageContentsType>::value), "Message data provided does not match the types declared for the message type!");
			::transmission::envelopes::GetEnvelopeBase<Envelope>::sendMessage(xt, contents, msgId);
		}
	} // end of namespace detail

	template<typename EnvelopeType, int MessageID, typename MessageType>
	struct MessageTypeWithContext {
		typedef EnvelopeType envelope;
		typedef MessageType message_type;
		enum {
			msg_id = MessageID
		};
		template<typename MessageContentsType, typename TXDerived>
		static void sendMessage(TransmissionBase<TXDerived> & xt, MessageContentsType const & contents) {
			detail::passMessageToEnvelopeToSend<MessageType, EnvelopeType, MessageContentsType, TXDerived>(xt, contents, static_cast<MessageIdType>(msg_id));
		}
	};


} // end of namespace transmission

#endif // INCLUDED_MessageTypeWithContext_h_GUID_1e9d05a8_141d_4197_9b93_f4afa0d5925c
