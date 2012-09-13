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
#ifndef INCLUDED_RoundtripCommon_h_GUID_ca373e94_1a35_4fb7_b5c6_2777bc29b4be
#define INCLUDED_RoundtripCommon_h_GUID_ca373e94_1a35_4fb7_b5c6_2777bc29b4be

// Internal Includes
#include "ProtocolForTest.h"
#include "DefinePartialReceiver.h"
#include <tuple-transmission/transmitters/VectorBuffer.h>
#include <tuple-transmission/Send.h>
#include <tuple-transmission/BoundMessageType.h>
#include <tuple-transmission/detail/constants/ArityConfig.h>

// Library/third-party includes
#include <boost/fusion/include/make_list.hpp>

// Standard includes
// - none

using transmission::send;
using transmission::BoundMessageType;
using transmission::transmitters::VectorBuffer;
namespace fusion = boost::fusion;

/**** message B tests ****/

#define MESSAGE_B_MAKELIST fusion::make_list(uint8_t(5), uint8_t(10), uint8_t(15))
#define MESSAGE_B_INLINE 5, 10, 15

void checkMessageB(VectorBuffer<MyMessageCollection> & buf) {
	TestReceiver r;
	r.appendReceived(buf.begin(), buf.end());
	BOOST_CHECK_EQUAL(r.first, 5);
	BOOST_CHECK_EQUAL(r.second, 10);
	BOOST_CHECK_EQUAL(r.third, 15);
}

BOOST_AUTO_TEST_CASE(CompleteMessageRoundtrip) {
	VectorBuffer<MyMessageCollection> buf;
	send<MyMessageCollection, MessageB>(buf, MESSAGE_B_MAKELIST);

	checkMessageB(buf);
}

BOOST_AUTO_TEST_CASE(CompleteOverloadedMessageRoundtrip) {
	VectorBuffer<MyMessageCollection> buf;
	send<MyMessageCollection, MessageB>(buf, MESSAGE_B_INLINE);

	checkMessageB(buf);
}

BOOST_AUTO_TEST_CASE(BoundCompleteMessageRoundtrip) {
	VectorBuffer<MyMessageCollection> buf;
	typedef BoundMessageType<MyMessageCollection, MessageB> BoundMessage;
	send<BoundMessage>(buf, MESSAGE_B_MAKELIST);

	checkMessageB(buf);
}

BOOST_AUTO_TEST_CASE(BoundOverloadedCompleteMessageRoundtrip) {
	VectorBuffer<MyMessageCollection> buf;
	typedef BoundMessageType<MyMessageCollection, MessageB> BoundMessage;
	send<BoundMessage>(buf, MESSAGE_B_INLINE);

	checkMessageB(buf);
}

BOOST_AUTO_TEST_CASE(DifferentMessageSameSignatureRoundtrip) {
	VectorBuffer<MyMessageCollection> buf;
	send<MyMessageCollection, MessageD>(buf, MESSAGE_B_MAKELIST);

	TestReceiver r;
	r.appendReceived(buf.begin(), buf.end());
	BOOST_CHECK_EQUAL(r.first, 0);
	BOOST_CHECK_EQUAL(r.second, 0);
	BOOST_CHECK_EQUAL(r.third, 0);
}

#undef MESSAGE_B_MAKELIST
#undef MESSAGE_B_INLINE

/**** empty message tests ****/

void checkEmptyMessage(VectorBuffer<MyMessageCollection> & buf) {
	TestReceiver r;
	BOOST_REQUIRE(!r.gotEmptyMessage);
	r.appendReceived(buf.begin(), buf.end());
	BOOST_CHECK(r.gotEmptyMessage);
}

BOOST_AUTO_TEST_CASE(EmptyMessageRoundtrip) {
	VectorBuffer<MyMessageCollection> buf;
	send<MyMessageCollection, EmptyMessage>(buf);

	TestReceiver r;
	BOOST_REQUIRE(!r.gotEmptyMessage);
	r.appendReceived(buf.begin(), buf.end());
	BOOST_CHECK(r.gotEmptyMessage);
}

BOOST_AUTO_TEST_CASE(BoundEmptyMessageRoundtrip) {
	VectorBuffer<MyMessageCollection> buf;
	typedef BoundMessageType<MyMessageCollection, EmptyMessage> BoundMessage;
	send<BoundMessage>(buf, fusion::make_list());

	checkEmptyMessage(buf);
}

BOOST_AUTO_TEST_CASE(BoundOverloadedEmptyMessageRoundtrip) {
	VectorBuffer<MyMessageCollection> buf;
	typedef BoundMessageType<MyMessageCollection, EmptyMessage> BoundMessage;
	send<BoundMessage>(buf);

	checkEmptyMessage(buf);
}

/**** other tests ****/
BOOST_AUTO_TEST_CASE(SendMaxArityMessage) {
	VectorBuffer<MyMessageCollection> buf;
	typedef BoundMessageType<MyMessageCollection, EmptyMessage> BoundMessage;
	/// When test was written, max arity was 9
	send<MyMessageCollection, MaxArityMessage>(buf, 0, 0, 0, 0, 0, 0, 0, 0, 0);

	TestReceiver r;
	r.appendReceived(buf.begin(), buf.end());
	BOOST_CHECK(!r.gotEmptyMessage);
	BOOST_CHECK_EQUAL(r.first, 0);
	BOOST_CHECK_EQUAL(r.second, 0);
	BOOST_CHECK_EQUAL(r.third, 0);
}

#endif // INCLUDED_RoundtripCommon_h_GUID_ca373e94_1a35_4fb7_b5c6_2777bc29b4be
