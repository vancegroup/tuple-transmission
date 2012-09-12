/**
	@author
	Ryan Pavlik ( <rpavlik@iastate.edu> http://academic.cleardefinition.com/ ),
	Iowa State University
	Virtual Reality Applications Center and
	Human-Computer Interaction Graduate Program
*/

#define BOOST_TEST_MODULE ReceiveHandler

#include <BoostTestTargetConfig.h>

// Internal Includes

#define USE_BASIC_ENVELOPE
#include "Protocol.h"
#include <tuple-transmission/ReceiveHandler.h>

// Library/third-party includes
#include <boost/mpl/assert.hpp>

// Standard includes
#include <iostream>

using namespace boost::unit_test;

// {{ControlCodes::SOH, 1, ControlCodes::STX, 5, 10, 15, ControlCodes::ETX, ControlCodes::EOT}};
typedef transmission::ReceiveHandler<MyMessageCollection> MyReceiveHandler;

inline void appendValidMessageCharacters(MyReceiveHandler & recv, std::size_t n, std::size_t start = 0) {
	BOOST_TEST_MESSAGE("Inserting valid message elements [" << start << ", " << start + n - 1 << "]");
	BOOST_ASSERT(start + n <= ValidMessage.size());
	recv.bufferAppend(ValidMessage.begin() + start, ValidMessage.begin() + start + n);
}

BOOST_AUTO_TEST_CASE(DefaultConstruction) {
	BOOST_REQUIRE_NO_THROW(transmission::ReceiveHandler<MyMessageCollection>());
	MyReceiveHandler r;
	BOOST_CHECK_EQUAL(r.bufferSize(), 0);
	BOOST_CHECK(r.bufferEmpty());
	BOOST_CHECK(!r.isCurrentMessageIdValid());
}

BOOST_AUTO_TEST_CASE(MessageMethods) {
	MyReceiveHandler r;
	BOOST_REQUIRE(!r.isCurrentMessageIdValid());

	BOOST_REQUIRE_NO_THROW(r.setCurrentMessageId(0));
	BOOST_REQUIRE(r.isCurrentMessageIdValid());
	BOOST_REQUIRE_EQUAL(r.getCurrentMessageId(), 0);

	BOOST_REQUIRE_NO_THROW(r.setCurrentMessageId(1));
	BOOST_REQUIRE(r.isCurrentMessageIdValid());
	BOOST_REQUIRE_EQUAL(r.getCurrentMessageId(), 1);

	BOOST_REQUIRE_NO_THROW(r.setCurrentMessageId(0));
	BOOST_REQUIRE(r.isCurrentMessageIdValid());
	BOOST_REQUIRE_EQUAL(r.getCurrentMessageId(), 0);

	BOOST_REQUIRE_NO_THROW(r.setCurrentMessageId(InvalidMessageId));
	BOOST_REQUIRE(!r.isCurrentMessageIdValid());
}

void runNefariousMessageTest(int round) {
	BOOST_TEST_CHECKPOINT("Starting round " << round);
	BOOST_TEST_MESSAGE("Starting round " << round);
	MyReceiveHandler r;
	BOOST_REQUIRE_EQUAL(r.bufferSize(), 0);

	BOOST_REQUIRE_NO_THROW(r.bufferAppend(0));
	BOOST_REQUIRE_EQUAL(r.bufferSize(), 1);
	if (round == 0) {
		BOOST_REQUIRE(!r.checkBufferForMessage());
		BOOST_REQUIRE_EQUAL(r.bufferSize(), 0);
		return;
	}

	appendValidMessageCharacters(r, 1);
	BOOST_REQUIRE_EQUAL(r.bufferSize(), 2);
	if (round == 1) {
		BOOST_REQUIRE(!r.checkBufferForMessage());
		BOOST_REQUIRE_EQUAL(r.bufferSize(), 1); // should keep the SOH around
		return;
	}

	BOOST_REQUIRE_NO_THROW(r.bufferAppend(20)); // out of range message ID
	BOOST_REQUIRE_EQUAL(r.bufferSize(), 3);
	if (round == 2) {
		BOOST_REQUIRE(!r.checkBufferForMessage());
		BOOST_REQUIRE_EQUAL(r.bufferSize(), 0); // should have realized this is now broken.
		return;
	}

	appendValidMessageCharacters(r, 1);
	BOOST_REQUIRE_EQUAL(r.bufferSize(), 4);
	if (round == 3) {
		BOOST_REQUIRE(!r.checkBufferForMessage());
		BOOST_REQUIRE_EQUAL(r.bufferSize(), 1); // should keep the second SOH around only
		return;
	}

	appendValidMessageCharacters(r, 1, 1); // ok, now a good msg id
	BOOST_REQUIRE_EQUAL(r.bufferSize(), 5);
	if (round == 4) {
		BOOST_REQUIRE(!r.checkBufferForMessage());
		BOOST_REQUIRE_EQUAL(r.bufferSize(), 2); // should keep the second SOH and message ID around
		return;
	}

	appendValidMessageCharacters(r, 1); // Not the right next character (want STX)
	BOOST_REQUIRE_EQUAL(r.bufferSize(), 6);
	if (round == 4) {
		BOOST_REQUIRE(!r.checkBufferForMessage());
		BOOST_REQUIRE_EQUAL(r.bufferSize(), 1); // The faulty character actually is a SOH
		return;
	}

	appendValidMessageCharacters(r, 2, 1); // put on the next two good characters
	BOOST_REQUIRE_EQUAL(r.bufferSize(), 8);
	if (round == 5) {
		BOOST_REQUIRE(!r.checkBufferForMessage());
		BOOST_REQUIRE_EQUAL(r.bufferSize(), 3); // Three good ones so far.
		return;
	}

	appendValidMessageCharacters(r, 3, 3); // Now have 6/8 good
	BOOST_REQUIRE_EQUAL(r.bufferSize(), 11);
	if (round == 6) {
		BOOST_REQUIRE(!r.checkBufferForMessage());
		BOOST_REQUIRE_EQUAL(r.bufferSize(), 6);
		return;
	}

	// Destroy the last message by putting SOH instead of expected known value,
	// and put 7/8 good instead
	appendValidMessageCharacters(r, 7);
	BOOST_REQUIRE_EQUAL(r.bufferSize(), 18);
	if (round == 7) {
		BOOST_REQUIRE(!r.checkBufferForMessage());
		BOOST_REQUIRE_EQUAL(r.bufferSize(), 7);
		return;
	}

	// Destroy the last message by putting SOH instead of expected known value,
	// and put a full good instead
	appendValidMessageCharacters(r, 8);
	BOOST_REQUIRE_EQUAL(r.bufferSize(), 26);
	if (round == 8) {
		BOOST_REQUIRE(r.checkBufferForMessage());
		BOOST_REQUIRE_EQUAL(r.bufferSize(), 8);
		BOOST_REQUIRE_EQUAL(r.getCurrentMessageId(), ValidMessageId);
		BOOST_REQUIRE_EQUAL(r.getMessageLength(), ValidMessageLength);
		return;
	}

	// round == 9
	// Make sure it leaves stuff after the message alone.
	BOOST_REQUIRE_NO_THROW(r.bufferAppend(0));
	BOOST_REQUIRE(r.checkBufferForMessage());
	BOOST_REQUIRE_EQUAL(r.bufferSize(), 9);
	BOOST_REQUIRE(r.isCurrentMessageIdValid());
	BOOST_REQUIRE_EQUAL(r.getCurrentMessageId(), ValidMessageId);
	BOOST_REQUIRE_EQUAL(r.getMessageLength(), ValidMessageLength);
}

BOOST_AUTO_TEST_CASE(CorruptOrMistakenMessage_round0) {
	runNefariousMessageTest(0);
}

BOOST_AUTO_TEST_CASE(CorruptOrMistakenMessage_round1) {
	runNefariousMessageTest(1);
}

BOOST_AUTO_TEST_CASE(CorruptOrMistakenMessage_round2) {
	runNefariousMessageTest(2);
}

BOOST_AUTO_TEST_CASE(CorruptOrMistakenMessage_round3) {
	runNefariousMessageTest(3);
}

BOOST_AUTO_TEST_CASE(CorruptOrMistakenMessage_round4) {
	runNefariousMessageTest(4);
}

BOOST_AUTO_TEST_CASE(CorruptOrMistakenMessage_round5) {
	runNefariousMessageTest(5);
}

BOOST_AUTO_TEST_CASE(CorruptOrMistakenMessage_round6) {
	runNefariousMessageTest(6);
}

BOOST_AUTO_TEST_CASE(CorruptOrMistakenMessage_round7) {
	runNefariousMessageTest(7);
}

BOOST_AUTO_TEST_CASE(CorruptOrMistakenMessage_round8) {
	runNefariousMessageTest(8);
}

BOOST_AUTO_TEST_CASE(CorruptOrMistakenMessage_round9) {
	runNefariousMessageTest(9);
}

