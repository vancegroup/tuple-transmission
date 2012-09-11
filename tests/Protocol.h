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
#ifndef INCLUDED_Protocol_h_GUID_475a3770_64a8_4158_a7eb_0bafac1edcb9
#define INCLUDED_Protocol_h_GUID_475a3770_64a8_4158_a7eb_0bafac1edcb9

// Internal Includes
#include <tuple-transmission/MessageType.h>
#include <tuple-transmission/MessageCollection.h>
#include <tuple-transmission/detail/ControlCodes.h>
#include <util/booststdint.h>

// Library/third-party includes
#include <boost/mpl/vector.hpp>
#include <boost/array.hpp>

// Standard includes
// - none

#if defined(USE_BASIC_ENVELOPE)
#define TEST_ENVELOPE_TYPE ::transmission::envelopes::Basic
#include <tuple-transmission/envelopes/Basic.h>

#elif defined(USE_CHECKSUM_ENVELOPE)
#define TEST_ENVELOPE_TYPE ::transmission::envelopes::BasicChecksum
#include <tuple-transmission/envelopes/BasicChecksum.h>

#else
#error "Must define one of the envelope types for the testing protocol header."
#endif
using namespace stdint;

typedef boost::mpl::vector<int8_t, uint8_t, int16_t> MessageATypes;
struct MessageA : transmission::MessageTypeBase<MessageATypes> {};
struct MessageB : transmission::MessageTypeBase<boost::mpl::vector<uint8_t, uint8_t, uint8_t> > {};
struct MessageC : transmission::MessageTypeBase<boost::mpl::vector<float, float, float> > {};

typedef transmission::MessageCollection <
	boost::mpl::vector
		< MessageA
		, MessageB
		, MessageC
		>
	, TEST_ENVELOPE_TYPE
	> MyMessageCollection;

static const int InvalidMessageId = 20;

#ifdef USE_BASIC_ENVELOPE
static const int ValidMessageId = 1;
static const int ValidMessageLength = 8;
static const boost::array<uint8_t, ValidMessageLength> ValidMessage = {{::transmission::detail::ControlCodes::SOH, 1, ::transmission::detail::ControlCodes::STX, 5, 10, 15, ::transmission::detail::ControlCodes::ETX, ::transmission::detail::ControlCodes::EOT}};
#endif // USE_BASIC_ENVELOPE

#endif // INCLUDED_Protocol_h_GUID_475a3770_64a8_4158_a7eb_0bafac1edcb9
