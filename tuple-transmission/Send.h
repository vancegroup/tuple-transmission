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
#ifndef INCLUDED_SendMessage_h_GUID_9cbfc065_ea71_4097_8993_c4e0b0fb14c5
#define INCLUDED_SendMessage_h_GUID_9cbfc065_ea71_4097_8993_c4e0b0fb14c5

// Internal Includes
#include "detail/bases/TransmitterBase_fwd.h"
#include "detail/types/IntegralTypes.h"
#include "BoundMessageType.h"

// Library/third-party includes
#include <boost/mpl/equal.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/fusion/mpl.hpp>

// Standard includes
// - none

namespace transmission {

	/** @brief The main function to send a message.

		Takes two explicit template parameters: the MessageCollection and the MessageType.
		Then, pass your "transmitter" and a boost::fusion sequence containing values for the message.
	*/
	template<typename Collection, typename Message, typename TransmitterDerived, typename MessageContentsType>
	void send(transmitters::TransmitterBase<TransmitterDerived> & tx, MessageContentsType const & contents) {
		/// Check to be sure we got what we expected
		BOOST_MPL_ASSERT((boost::mpl::equal<Message, MessageContentsType>));

		typedef BoundMessageType<Collection, Message> bound_message;
		typedef typename bound_message::envelope_type envelope_type;
		envelope_type::sendMessage(tx, contents, static_cast<MessageIdType>(typename bound_message::message_id()));
	}
}// end of namespace transmission

#endif // INCLUDED_SendMessage_h_GUID_9cbfc065_ea71_4097_8993_c4e0b0fb14c5
