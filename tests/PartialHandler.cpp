/**
	@author
	Ryan Pavlik ( <rpavlik@iastate.edu> http://academic.cleardefinition.com/ ),
	Iowa State University
	Virtual Reality Applications Center and
	Human-Computer Interaction Graduate Program
*/

#define BOOST_TEST_MODULE PartialHandler

#include <BoostTestTargetConfig.h>

// Internal Includes

#define USE_BASIC_ENVELOPE
#include "ProtocolForTest.h"
#include <tuple-transmission/PartialHandlerBase.h>

// Library/third-party includes
#include <boost/mpl/assert.hpp>

// Standard includes
#include <iostream>

using namespace boost::unit_test;

#include "DefinePartialHandler.h"


#include "HandlerCommon.h"

