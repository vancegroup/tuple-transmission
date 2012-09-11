/**
	@author
	Ryan Pavlik ( <rpavlik@iastate.edu> http://academic.cleardefinition.com/ ),
	Iowa State University
	Virtual Reality Applications Center and
	Human-Computer Interaction Graduate Program
*/

#define BOOST_TEST_MODULE ReceiveHandler

// Internal Includes

#define USE_BASIC_ENVELOPE
#include "Protocol.h"
#include <tuple-transmission/ReceiveHandler.h>

// Library/third-party includes
#include <boost/mpl/assert.hpp>
#include <BoostTestTargetConfig.h>

// Standard includes
#include <iostream>

using namespace boost::unit_test;


BOOST_AUTO_TEST_CASE(DefaultConstruction) {
	BOOST_CHECK_NO_THROW(transmission::ReceiveHandler<MyMessageCollection>());
	transmission::ReceiveHandler<MyMessageCollection> r;
	BOOST_CHECK_EQUAL(r.bufferSize(), 0);
	BOOST_CHECK(r.bufferEmpty());
	BOOST_CHECK(!r.isCurrentMessageIdValid());
}

BOOST_AUTO_TEST_CASE(MessageMethods) {
	transmission::ReceiveHandler<MyMessageCollection> r;
	BOOST_CHECK(!r.isCurrentMessageIdValid());

	BOOST_CHECK_NO_THROW(r.setCurrentMessageId(0));
	BOOST_CHECK(r.isCurrentMessageIdValid());
	BOOST_CHECK_EQUAL(r.getCurrentMessageId(), 0);

	BOOST_CHECK_NO_THROW(r.setCurrentMessageId(1));
	BOOST_CHECK(r.isCurrentMessageIdValid());
	BOOST_CHECK_EQUAL(r.getCurrentMessageId(), 1);

	BOOST_CHECK_NO_THROW(r.setCurrentMessageId(0));
	BOOST_CHECK(r.isCurrentMessageIdValid());
	BOOST_CHECK_EQUAL(r.getCurrentMessageId(), 0);

	BOOST_CHECK_NO_THROW(r.setCurrentMessageId(2));
	BOOST_CHECK(!r.isCurrentMessageIdValid());
}

