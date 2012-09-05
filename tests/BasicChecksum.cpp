/**
	@author
	Ryan Pavlik ( <rpavlik@iastate.edu> http://academic.cleardefinition.com/ ),
	Iowa State University
	Virtual Reality Applications Center and
	Human-Computer Interaction Graduate Program
*/

#define BOOST_TEST_MODULE TupleTransmission

// Internal Includes
#define TEST_ENVELOPE_TYPE ::transmission::envelopes::BasicChecksum
#include "Protocol.h"
#include <tuple-transmission/envelopes/BasicChecksum.h>
#include <tuple-transmission/Send.h>
#include <tuple-transmission/Transmission.h>
#include <tuple-transmission/BoostArrayBuffer.h>
#include <tuple-transmission/detail/ControlCodes.h>

#include "OutputArray.h"

// Library/third-party includes
#include <boost/io/ios_state.hpp>
#include <boost/fusion/include/make_vector.hpp>
#include <BoostTestTargetConfig.h>

// Standard includes
#include <iostream>

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
	typedef boost::array<uint8_t, 9> rawbuftype;
	rawbuftype expected = {{ControlCodes::SOH, 1, ControlCodes::STX, 5, 10, 15, ControlCodes::ETX, 0, 0}};
	uint8_t checksum = 0;
	{

		boost::io::ios_flags_saver ifs(std::cout);
		for (rawbuftype::const_iterator it = expected.begin(), e = expected.end(); it != e; ++it) {
			checksum += *it;
			std::cout << std::hex << std::showbase << static_cast<unsigned>(*it) << " (current checksum: " << static_cast<unsigned>(checksum) << ")" << std::endl;
		}
	}
	*(expected.end() - 2) = checksum;
	*(expected.end() - 1) = ControlCodes::EOT;
	BOOST_CHECK_EQUAL((buf.buffer) , expected);
}
