/**
	@author
	Ryan Pavlik ( <rpavlik@iastate.edu> http://academic.cleardefinition.com/ ),
	Iowa State University
	Virtual Reality Applications Center and
	Human-Computer Interaction Graduate Program
*/

#define BOOST_TEST_MODULE Receive

#include <BoostTestTargetConfig.h>

// Internal Includes

#define USE_BASIC_ENVELOPE
#include "Protocol.h"
#include <tuple-transmission/Receiver.h>

// Library/third-party includes
#include <boost/mpl/assert.hpp>

// Standard includes
#include <iostream>

using namespace boost::unit_test;

class TestReceiver : public transmission::Receiver<TestReceiver, MyMessageCollection> {
	public:
		TestReceiver() {
			reset();
		}

		void reset() {
			first = 0;
			second = 0;
			third = 0;
		}

		void operator()(int8_t, uint8_t, int16_t) {}
		/// Handles MessageB
		void operator()(/*MessageB const&,*/ uint8_t a, uint8_t b, uint8_t c) {
			first = a;
			second = b;
			third = c;
		}
		void operator()(float, float, float) {}
		uint8_t first;
		uint8_t second;
		uint8_t third;
};


void appendValidMessageCharacters(TestReceiver & recv, std::size_t n, std::size_t start = 0) {
	BOOST_TEST_MESSAGE("Inserting valid message elements [" << start << ", " << start + n - 1 << "]");
	BOOST_ASSERT(start + n <= ValidMessage.size());
	recv.appendReceived(ValidMessage.begin() + start, ValidMessage.begin() + start + n);
}

BOOST_AUTO_TEST_CASE(DefaultConstruction) {
	BOOST_REQUIRE_NO_THROW(TestReceiver());
	TestReceiver r;
	BOOST_CHECK_EQUAL(r.first, 0);
	BOOST_CHECK_EQUAL(r.second, 0);
	BOOST_CHECK_EQUAL(r.third, 0);
}

BOOST_AUTO_TEST_CASE(IncompleteMessages) {
	TestReceiver r;
	for (unsigned long n = 1; n < ValidMessage.size(); ++n) {
		appendValidMessageCharacters(r, n);
		BOOST_CHECK_EQUAL(r.first, 0);
		BOOST_CHECK_EQUAL(r.second, 0);
		BOOST_CHECK_EQUAL(r.third, 0);
	}
}

BOOST_AUTO_TEST_CASE(CompleteMessage) {
	TestReceiver r;
	appendValidMessageCharacters(r, ValidMessage.size());
	BOOST_CHECK_EQUAL(r.first, 5);
	BOOST_CHECK_EQUAL(r.second, 10);
	BOOST_CHECK_EQUAL(r.third, 15);
}

