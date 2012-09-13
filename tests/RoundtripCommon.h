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

#include "BaseSendReceiveFixture.h"

/**** message B tests ****/

#define THREE_NUMBERS_INLINE 5, 10, 15

struct MessageBFixture : BaseSendReceiveFixture {
	~MessageBFixture() {
		checkBufferLength(MessageB());
		/// Must have received a message
		BOOST_REQUIRE_EQUAL(receive(), 1);
		checkLastMessage(MessageB());
		BOOST_CHECK(!r.gotEmptyMessage);
		BOOST_CHECK_EQUAL(r.first, 5);
		BOOST_CHECK_EQUAL(r.second, 10);
		BOOST_CHECK_EQUAL(r.third, 15);
	}
};


BOOST_AUTO_TEST_CASE(MessageB_Roundtrip) {
	MessageBFixture f;
	send<MyMessageCollection, MessageB>(f.buf, fusion::make_list(uint8_t(5), uint8_t(10), uint8_t(15)));
}

BOOST_AUTO_TEST_CASE(MessageB_RoundtripBound) {
	MessageBFixture f;
	typedef BoundMessageType<MyMessageCollection, MessageB> BoundMessage;
	send<BoundMessage>(f.buf, fusion::make_list(uint8_t(5), uint8_t(10), uint8_t(15)));
}

BOOST_AUTO_TEST_CASE(MessageB_RoundtripOverloaded) {
	MessageBFixture f;
	send<MyMessageCollection, MessageB>(f.buf, THREE_NUMBERS_INLINE);
}

BOOST_AUTO_TEST_CASE(MessageB_RoundtripOverloadedBound) {
	MessageBFixture f;
	typedef BoundMessageType<MyMessageCollection, MessageB> BoundMessage;
	send<BoundMessage>(f.buf, THREE_NUMBERS_INLINE);
}


/**** empty message tests ****/

struct EmptyMessageFixture : BaseSendReceiveFixture {
	~EmptyMessageFixture() {
		checkBufferLength(EmptyMessage());
		/// Must have received a message
		BOOST_REQUIRE_EQUAL(receive(), 1);
		checkLastMessage(EmptyMessage());
		BOOST_CHECK(r.gotEmptyMessage);
		BOOST_CHECK_EQUAL(r.first, 0);
		BOOST_CHECK_EQUAL(r.second, 0);
		BOOST_CHECK_EQUAL(r.third, 0);
	}
};

BOOST_AUTO_TEST_CASE(EmptyMessage_Roundtrip) {
	EmptyMessageFixture f;
	send<MyMessageCollection, EmptyMessage>(f.buf, fusion::make_list());
}

BOOST_AUTO_TEST_CASE(EmptyMessage_RoundtripBound) {
	EmptyMessageFixture f;
	typedef BoundMessageType<MyMessageCollection, EmptyMessage> BoundMessage;
	send<BoundMessage>(f.buf, fusion::make_list());
}

BOOST_AUTO_TEST_CASE(EmptyMessage_RoundtripOverloaded) {
	EmptyMessageFixture f;
	send<MyMessageCollection, EmptyMessage>(f.buf);
}

BOOST_AUTO_TEST_CASE(EmptyMessage_RoundtripOverloadedBound) {
	EmptyMessageFixture f;
	typedef BoundMessageType<MyMessageCollection, EmptyMessage> BoundMessage;
	send<BoundMessage>(f.buf);
}

/**** tests of other message types - so they shouldn't change our receiver's state ****/

template<typename MessageType>
struct OtherMessageFixture : BaseSendReceiveFixture {
	~OtherMessageFixture() {
		checkBufferLength(MessageType());
		/// Must have received a message
		BOOST_REQUIRE_EQUAL(receive(), 1);
		checkLastMessage(MessageType());
		BOOST_CHECK(!r.gotEmptyMessage);
		BOOST_CHECK_EQUAL(r.first, 0);
		BOOST_CHECK_EQUAL(r.second, 0);
		BOOST_CHECK_EQUAL(r.third, 0);
	}
};

BOOST_AUTO_TEST_CASE(MessageA_SendRecv) {
	OtherMessageFixture<MessageA> f;
	send<MyMessageCollection, MessageA>(f.buf, fusion::make_list(int8_t(5), uint8_t(5), int16_t(5)));
}

BOOST_AUTO_TEST_CASE(MessageA_SendRecvBound) {
	OtherMessageFixture<MessageA> f;
	typedef BoundMessageType<MyMessageCollection, MessageA> BoundMessage;
	send<BoundMessage>(f.buf, fusion::make_list(int8_t(5), uint8_t(5), int16_t(5)));
}

BOOST_AUTO_TEST_CASE(MessageA_SendRecvOverloaded) {
	OtherMessageFixture<MessageA> f;
	send<MyMessageCollection, MessageA>(f.buf, THREE_NUMBERS_INLINE);
}

BOOST_AUTO_TEST_CASE(MessageA_SendRecvOverloadedBound) {
	OtherMessageFixture<MessageA> f;
	typedef BoundMessageType<MyMessageCollection, MessageA> BoundMessage;
	send<BoundMessage>(f.buf, THREE_NUMBERS_INLINE);
}

BOOST_AUTO_TEST_CASE(MessageC_SendRecv) {
	OtherMessageFixture<MessageC> f;
	send<MyMessageCollection, MessageC>(f.buf, fusion::make_list(5.0f, 5.0f, 5.0f));
}

BOOST_AUTO_TEST_CASE(MessageC_SendRecvBound) {
	OtherMessageFixture<MessageC> f;
	typedef BoundMessageType<MyMessageCollection, MessageC> BoundMessage;
	send<BoundMessage>(f.buf, fusion::make_list(5.0f, 5.0f, 5.0f));
}

BOOST_AUTO_TEST_CASE(MessageC_SendRecvOverloaded) {
	OtherMessageFixture<MessageC> f;
	send<MyMessageCollection, MessageC>(f.buf, THREE_NUMBERS_INLINE);
}

BOOST_AUTO_TEST_CASE(MessageC_SendRecvOverloadedBound) {
	OtherMessageFixture<MessageC> f;
	typedef BoundMessageType<MyMessageCollection, MessageC> BoundMessage;
	send<BoundMessage>(f.buf, THREE_NUMBERS_INLINE);
}


BOOST_AUTO_TEST_CASE(MessageD_SendRecv) {
	OtherMessageFixture<MessageD> f;
	send<MyMessageCollection, MessageD>(f.buf, fusion::make_list(uint8_t(5), uint8_t(10), uint8_t(15)));
}

BOOST_AUTO_TEST_CASE(MessageD_SendRecvBound) {
	OtherMessageFixture<MessageD> f;
	typedef BoundMessageType<MyMessageCollection, MessageD> BoundMessage;
	send<BoundMessage>(f.buf, fusion::make_list(uint8_t(5), uint8_t(10), uint8_t(15)));
}

BOOST_AUTO_TEST_CASE(MessageD_SendRecvOverloaded) {
	OtherMessageFixture<MessageD> f;
	send<MyMessageCollection, MessageD>(f.buf, THREE_NUMBERS_INLINE);
}

BOOST_AUTO_TEST_CASE(MessageD_SendRecvOverloadedBound) {
	OtherMessageFixture<MessageD> f;
	typedef BoundMessageType<MyMessageCollection, MessageD> BoundMessage;
	send<BoundMessage>(f.buf, THREE_NUMBERS_INLINE);
}

#undef THREE_NUMBERS_INLINE

/// When tests were written, max arity was 9
BOOST_AUTO_TEST_CASE(MaxArityMessage_SendRecv) {
	OtherMessageFixture<MaxArityMessage> f;
	send<MyMessageCollection, MaxArityMessage>(f.buf,
	        fusion::make_list(uint8_t(0),
	                          uint8_t(0),
	                          uint8_t(0),
	                          uint8_t(0),
	                          uint8_t(0),
	                          uint8_t(0),
	                          uint8_t(0),
	                          uint8_t(0),
	                          uint8_t(0)));
}

BOOST_AUTO_TEST_CASE(MaxArityMessage_SendRecvBound) {
	OtherMessageFixture<MaxArityMessage> f;
	typedef BoundMessageType<MyMessageCollection, MaxArityMessage> BoundMessage;
	send<BoundMessage>(f.buf,
	                   fusion::make_list(uint8_t(0),
	                                     uint8_t(0),
	                                     uint8_t(0),
	                                     uint8_t(0),
	                                     uint8_t(0),
	                                     uint8_t(0),
	                                     uint8_t(0),
	                                     uint8_t(0),
	                                     uint8_t(0)));
}

BOOST_AUTO_TEST_CASE(MaxArityMessage_SendRecvOverloaded) {
	OtherMessageFixture<MaxArityMessage> f;
	send<MyMessageCollection, MaxArityMessage>(f.buf, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}

BOOST_AUTO_TEST_CASE(MaxArityMessage_SendRecvOverloadedBound) {
	OtherMessageFixture<MaxArityMessage> f;
	typedef BoundMessageType<MyMessageCollection, MaxArityMessage> BoundMessage;
	send<BoundMessage>(f.buf, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}


#endif // INCLUDED_RoundtripCommon_h_GUID_ca373e94_1a35_4fb7_b5c6_2777bc29b4be
