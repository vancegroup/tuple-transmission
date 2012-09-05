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
#include <util/booststdint.h>

// Library/third-party includes
#include <boost/mpl/vector.hpp>

// Standard includes
// - none

#ifndef TEST_ENVELOPE_TYPE
#error "Must define fully qualified TEST_ENVELOPE_TYPE"
#endif
using namespace stdint;

typedef boost::mpl::vector<int8_t, uint8_t, int16_t> MessageATypes;
struct MessageA : transmission::MessageTypeBase<MessageATypes> {};
struct MessageB : transmission::MessageTypeBase<boost::mpl::vector<uint8_t, uint8_t, uint8_t> > {};

typedef transmission::MessageCollection <
	boost::mpl::vector
		< MessageA
		, MessageB
		>
	, TEST_ENVELOPE_TYPE
	> MyMessageCollection;

#endif // INCLUDED_Protocol_h_GUID_475a3770_64a8_4158_a7eb_0bafac1edcb9
