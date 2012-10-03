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
#ifndef INCLUDED_DefinePartialHandler_h_GUID_e4266113_e5b3_4580_a2ed_76cfda433768
#define INCLUDED_DefinePartialHandler_h_GUID_e4266113_e5b3_4580_a2ed_76cfda433768

// Internal Includes
#include <tuple-transmission/PartialHandlerBase.h>

// Library/third-party includes
// - none

// Standard includes
// - none

class TestHandler : public transmission::PartialHandlerBase {
	public:
		using transmission::PartialHandlerBase::operator();

		TestHandler() {
			reset();
		}

		void reset() {
			first = 0;
			second = 0;
			third = 0;
			gotEmptyMessage = false;
		}

		/// Handles MessageB
		void operator()(MessageB const&, uint8_t a, uint8_t b, uint8_t c) {
			first = a;
			second = b;
			third = c;
		}

		void operator()(EmptyMessage const&) {
			gotEmptyMessage = true;
		}

		uint8_t first;
		uint8_t second;
		uint8_t third;

		bool gotEmptyMessage;
};

#endif // INCLUDED_DefinePartialHandler_h_GUID_e4266113_e5b3_4580_a2ed_76cfda433768
