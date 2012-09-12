/**
	@author
	Ryan Pavlik ( <rpavlik@iastate.edu> http://academic.cleardefinition.com/ ),
	Iowa State University
	Virtual Reality Applications Center and
	Human-Computer Interaction Graduate Program
*/

#define BOOST_TEST_MODULE Receiver

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

using transmission::MessageTag;
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

		void operator()(MessageTag<MessageA> const&, int8_t, uint8_t, int16_t) {}
		/// Handles MessageB
		void operator()(MessageTag<MessageB> const&, uint8_t a, uint8_t b, uint8_t c) {
			first = a;
			second = b;
			third = c;
		}
		void operator()(MessageTag<MessageC> const&, float, float, float) {}
		uint8_t first;
		uint8_t second;
		uint8_t third;
};

#include "ReceiverCommon.h"

