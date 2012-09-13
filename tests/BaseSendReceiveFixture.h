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
#ifndef INCLUDED_BaseSendReceiveFixture_h_GUID_9e8699a9_739b_4eab_8a89_272701321510
#define INCLUDED_BaseSendReceiveFixture_h_GUID_9e8699a9_739b_4eab_8a89_272701321510

// Internal Includes
#include "BaseReceiveFixture.h"
#include <tuple-transmission/transmitters/VectorBuffer.h>
#include <tuple-transmission/detail/operations/Sizeof.h>

// Library/third-party includes
// - none

// Standard includes
// - none

struct BaseSendReceiveFixture : BaseReceiveFixture {
	transmission::transmitters::VectorBuffer<MyMessageCollection> buf;

	BaseSendReceiveFixture() {
		BOOST_REQUIRE(buf.buffer.empty());
	}

	uint8_t receive() {
		return r.appendReceived(buf.begin(), buf.end());
	}


	template<typename MessageType>
	void checkLastMessage(MessageType const&) const {
		BOOST_REQUIRE_EQUAL(*r.getLastMessageId(), (typename BoundMessageType<MyMessageCollection, MessageType>::message_id()));
	}

	template<typename MessageType>
	void checkBufferLength(MessageType const&) const {
		using transmission::detail::operations::Sizeof;
		BOOST_REQUIRE_EQUAL(buf.buffer.size(), (Sizeof<BoundMessageType<MyMessageCollection, MessageType> >()));
	}
};

#endif // INCLUDED_BaseSendReceiveFixture_h_GUID_9e8699a9_739b_4eab_8a89_272701321510
