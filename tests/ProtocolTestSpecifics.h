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
#ifndef INCLUDED_ProtocolTestSpecifics_h_GUID_83d8e28e_4096_4735_9504_46e6b81a2f6d
#define INCLUDED_ProtocolTestSpecifics_h_GUID_83d8e28e_4096_4735_9504_46e6b81a2f6d

// Internal Includes
#include <tuple-transmission/detail/constants/ControlCodes.h>

// Library/third-party includes
#include <boost/array.hpp>

// Standard includes
// - none


namespace ControlCodes = ::transmission::detail::constants::ControlCodes;

static const int InvalidMessageId = 20;
static const int ValidMessageId = 1;
static const size_t MessageIdIndex = 1;

#if defined(USE_BASIC_ENVELOPE)
static const int ValidMessageLength = 8;

#elif defined(USE_CHECKSUM_ENVELOPE)
static const int ValidMessageLength = 9;
#endif

typedef boost::array<uint8_t, ValidMessageLength> ValidMessageBufferType;


#if defined(USE_BASIC_ENVELOPE)
static const ValidMessageBufferType ValidMessage = {{ControlCodes::SOH, 1, ControlCodes::STX, 5, 10, 15, ControlCodes::ETX, ControlCodes::EOT}};

#elif defined(USE_CHECKSUM_ENVELOPE)
static const ValidMessageBufferType ValidMessage = {{ControlCodes::SOH, 1, ControlCodes::STX, 5, 10, 15, ControlCodes::ETX, 0x25, ControlCodes::EOT}};
#endif

#endif // INCLUDED_ProtocolTestSpecifics_h_GUID_83d8e28e_4096_4735_9504_46e6b81a2f6d
