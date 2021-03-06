/**
	@author
	Ryan Pavlik ( <rpavlik@iastate.edu> http://academic.cleardefinition.com/ ),
	Iowa State University
	Virtual Reality Applications Center and
	Human-Computer Interaction Graduate Program
*/

#define BOOST_TEST_MODULE ChecksumReceiver

#include <BoostTestTargetConfig.h>

// Internal Includes

#define USE_CHECKSUM_ENVELOPE
#include "ProtocolForTest.h"
#include <tuple-transmission/PartialHandlerBase.h>

// Library/third-party includes
#include <boost/mpl/assert.hpp>

// Standard includes
#include <iostream>

using namespace boost::unit_test;

class TestHandler : public transmission::PartialHandlerBase<TestHandler> {
	public:
		using transmission::PartialHandlerBase<TestHandler>::operator();

		TestHandler() {
			reset();
		}

		void reset() {
			first = 0;
			second = 0;
			third = 0;
		}

		/// Handles MessageB
		void operator()(MessageB const&, uint8_t a, uint8_t b, uint8_t c) {
			first = a;
			second = b;
			third = c;
		}

		uint8_t first;
		uint8_t second;
		uint8_t third;
};



#include "HandlerCommon.h"

