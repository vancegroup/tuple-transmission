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
#include <tuple-transmission/Receive.h>

// Library/third-party includes
#include <boost/mpl/assert.hpp>

// Standard includes
#include <iostream>

using namespace boost::unit_test;

// {{ControlCodes::SOH, 1, ControlCodes::STX, 5, 10, 15, ControlCodes::ETX, ControlCodes::EOT}};
typedef transmission::ReceiveHandler<MyMessageCollection> MyReceiveHandler;

class TestReceiver : public transmission::Receive<TestReceiver, MyMessageCollection> {
	public:
		TestReceiver() {
			reset();
		}

		void reset() {
			first = 0;
			second = 0;
			third = 0;
		}

		/// Handles MessageB
		void operator()(/*MessageB const&,*/ uint8_t a, uint8_t b, uint8_t c) {
			first = a;
			second = b;
			third = c;
		}
		uint8_t first;
		uint8_t second;
		uint8_t third;
};



BOOST_AUTO_TEST_CASE(DefaultConstruction) {
	BOOST_REQUIRE_NO_THROW(TestReceiver());
	TestReceiver r;
	BOOST_CHECK_EQUAL(r.first, 0);
	BOOST_CHECK_EQUAL(r.second, 0);
	BOOST_CHECK_EQUAL(r.third, 0);
}

