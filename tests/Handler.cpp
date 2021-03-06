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
#include "ProtocolForTest.h"
#include <tuple-transmission/Receiver.h>
#include <tuple-transmission/ParameterHandlerBase.h>

// Library/third-party includes
#include <boost/mpl/assert.hpp>

// Standard includes
#include <iostream>

using namespace boost::unit_test;

class TestHandler : public transmission::ParameterHandlerBase<TestHandler> {
	public:
		using transmission::ParameterHandlerBase<TestHandler>::operator();
		TestHandler() {
			reset();
		}

		void reset() {
			first = 0;
			second = 0;
			third = 0;
		}

		void operator()(MessageA const&, int8_t, uint8_t, int16_t) {}
		/// Handles MessageB
		void operator()(MessageB const&, uint8_t a, uint8_t b, uint8_t c) {
			first = a;
			second = b;
			third = c;
			gotEmptyMessage = false;
		}
		void operator()(MessageC const&, float, float, float) {}

		void operator()(MessageD const&, uint8_t, uint8_t, uint8_t) {}

		void operator()(EmptyMessage const&) {
			gotEmptyMessage = true;
		}

		void operator()(MaxArityMessage const&, ...) {}

		uint8_t first;
		uint8_t second;
		uint8_t third;
		bool gotEmptyMessage;
};

#include "HandlerCommon.h"

