/**
	@author
	Ryan Pavlik ( <rpavlik@iastate.edu> http://academic.cleardefinition.com/ ),
	Iowa State University
	Virtual Reality Applications Center and
	Human-Computer Interaction Graduate Program
*/

#define BOOST_TEST_MODULE TupleTransmission

// Internal Includes
#include "Protocol.h"
#include <tuple-transmission/Send.h>
#include <tuple-transmission/Transmission.h>
#include <tuple-transmission/EnvelopeBasic.h>
#include <tuple-transmission/BoostArrayBuffer.h>
#include <tuple-transmission/detail/ControlCodes.h>

#include "OutputArray.h"

// Library/third-party includes
#include <boost/fusion/include/make_vector.hpp>
#include <BoostTestTargetConfig.h>

// Standard includes
// - none

using namespace boost::unit_test;

BOOST_AUTO_TEST_CASE(WholeMessageSerialize) {
	using transmission::send;
	using transmission::Transmission;
	using transmission::BoostArrayBufferAutosized;

	namespace ControlCodes = transmission::detail::ControlCodes;

	typedef Transmission<MyMessageCollection, MessageB> TransmissionB;
	typedef BoostArrayBufferAutosized<TransmissionB> TransmitBufferType;

	TransmitBufferType buf;
	send<TransmissionB>(buf, boost::fusion::make_vector(uint8_t(5), uint8_t(10), uint8_t(15)));
	boost::array<uint8_t, 8> expected = {{ControlCodes::SOH, 1, ControlCodes::STX, 5, 10, 15, ControlCodes::ETX, ControlCodes::EOT}};
	BOOST_CHECK_EQUAL((buf.buffer) , expected);
}
