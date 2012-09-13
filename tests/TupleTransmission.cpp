/**
	@author
	Ryan Pavlik ( <rpavlik@iastate.edu> http://academic.cleardefinition.com/ ),
	Iowa State University
	Virtual Reality Applications Center and
	Human-Computer Interaction Graduate Program
*/

#define BOOST_TEST_MODULE TupleTransmission

// Internal Includes

#define USE_BASIC_ENVELOPE
#include "ProtocolForTest.h"
#include <tuple-transmission/Send.h>
#include <tuple-transmission/transmitters/BoostArrayBuffer.h>
#include <tuple-transmission/transmitters/AutosizedBoostArrayBuffer.h>

#include "OutputArray.h"

// Library/third-party includes
#include <boost/fusion/include/make_vector.hpp>
#include <BoostTestTargetConfig.h>

// Standard includes
// - none

using namespace boost::unit_test;
using transmission::send;
using transmission::BoundMessageType;
using transmission::transmitters::BoostArrayBuffer;
using transmission::transmitters::AutosizedBoostArrayBuffer;

BOOST_AUTO_TEST_CASE(WholeMessageSerializeAutobuffer) {

	typedef BoundMessageType<MyMessageCollection, MessageB> BoundMessageB;
	typedef AutosizedBoostArrayBuffer<BoundMessageB> TransmitBufferType;

	TransmitBufferType buf;
	send<MyMessageCollection, MessageB>(buf, boost::fusion::make_vector(uint8_t(5), uint8_t(10), uint8_t(15)));
	boost::array<uint8_t, 8> expected = {{ControlCodes::SOH, 1, ControlCodes::STX, 5, 10, 15, ControlCodes::ETX, ControlCodes::EOT}};
	BOOST_CHECK_EQUAL((buf.buffer) , expected);
}

BOOST_AUTO_TEST_CASE(WholeMessageSerialize) {
	typedef BoostArrayBuffer<8> TransmitBufferType;

	TransmitBufferType buf;
	send<MyMessageCollection, MessageB>(buf, boost::fusion::make_vector(uint8_t(5), uint8_t(10), uint8_t(15)));
	boost::array<uint8_t, 8> expected = {{ControlCodes::SOH, 1, ControlCodes::STX, 5, 10, 15, ControlCodes::ETX, ControlCodes::EOT}};
	BOOST_CHECK_EQUAL((buf.buffer) , expected);
}

BOOST_AUTO_TEST_CASE(WholeMessageSendOverloads) {
	typedef BoostArrayBuffer<8> TransmitBufferType;

	TransmitBufferType buf;
	send<MyMessageCollection, MessageB>(buf, 5, 10, 15);
	boost::array<uint8_t, 8> expected = {{ControlCodes::SOH, 1, ControlCodes::STX, 5, 10, 15, ControlCodes::ETX, ControlCodes::EOT}};
	BOOST_CHECK_EQUAL((buf.buffer) , expected);
}
