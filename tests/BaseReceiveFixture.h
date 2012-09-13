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
#ifndef INCLUDED_BaseReceiveFixture_h_GUID_cf91e0b2_2f5c_47b8_8a08_1514cc459bb0
#define INCLUDED_BaseReceiveFixture_h_GUID_cf91e0b2_2f5c_47b8_8a08_1514cc459bb0

// Internal Includes
#include <tuple-transmission/transmitters/VectorBuffer.h>
#include <tuple-transmission/BoundMessageType.h>

// Library/third-party includes
// - none

// Standard includes
// - none

struct BaseReceiveFixture {
	transmission::transmitters::VectorBuffer<MyMessageCollection> buf;
	TestReceiver r;

	BaseReceiveFixture() {
		BOOST_REQUIRE(!r.gotEmptyMessage);
		BOOST_REQUIRE(!r.getLastMessageId());
		BOOST_REQUIRE_EQUAL(r.first, 0);
		BOOST_REQUIRE_EQUAL(r.second, 0);
		BOOST_REQUIRE_EQUAL(r.third, 0);
	}

	uint8_t receive() {
		return r.appendReceived(buf.begin(), buf.end());
	}

	template<typename MessageType>
	void checkLastMessage(MessageType const&) const {
		BOOST_REQUIRE_EQUAL(*r.getLastMessageId(), (typename BoundMessageType<MyMessageCollection, MessageType>::message_id()));
	}
};

#endif // INCLUDED_BaseReceiveFixture_h_GUID_cf91e0b2_2f5c_47b8_8a08_1514cc459bb0
