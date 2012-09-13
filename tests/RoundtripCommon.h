/** @file
	@brief Header

	@date 2012

	@author
	Ryan Pavlik
	<rpavlik@iastate.edu> and <abiryan@ryand.net>
	http://academic.cleardefinition.com/
	Iowa State University Virtual Reality Applications Center
	Human-Computer Interaction Graduate Program
*/

//          Copyright Iowa State University 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#pragma once
#ifndef INCLUDED_RoundtripCommon_h_GUID_ca373e94_1a35_4fb7_b5c6_2777bc29b4be
#define INCLUDED_RoundtripCommon_h_GUID_ca373e94_1a35_4fb7_b5c6_2777bc29b4be

// Internal Includes
#include "ProtocolForTest.h"
#include "DefinePartialReceiver.h"
#include <tuple-transmission/transmitters/VectorBuffer.h>
#include <tuple-transmission/Send.h>

// Library/third-party includes
// - none

// Standard includes
// - none

using transmission::send;
using transmission::transmitters::VectorBuffer;



BOOST_AUTO_TEST_CASE(CompleteMessageRoundtrip) {
	VectorBuffer<MyMessageCollection> buf;
	send<MyMessageCollection, MessageB>(buf, 5, 10, 15);

	TestReceiver r;
	r.appendReceived(buf.begin(), buf.end());
	BOOST_CHECK_EQUAL(r.first, 5);
	BOOST_CHECK_EQUAL(r.second, 10);
	BOOST_CHECK_EQUAL(r.third, 15);
}

BOOST_AUTO_TEST_CASE(DifferentMessageSameSignatureRoundtrip) {
	VectorBuffer<MyMessageCollection> buf;
	send<MyMessageCollection, MessageD>(buf, 5, 10, 15);

	TestReceiver r;
	r.appendReceived(buf.begin(), buf.end());
	BOOST_CHECK_EQUAL(r.first, 0);
	BOOST_CHECK_EQUAL(r.second, 0);
	BOOST_CHECK_EQUAL(r.third, 0);
}

#endif // INCLUDED_RoundtripCommon_h_GUID_ca373e94_1a35_4fb7_b5c6_2777bc29b4be
