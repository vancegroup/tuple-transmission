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
#ifndef INCLUDED_MessageIdType_h_GUID_5d3f6687_240b_49f7_b325_52c417787cad
#define INCLUDED_MessageIdType_h_GUID_5d3f6687_240b_49f7_b325_52c417787cad

// Internal Includes
#include <util/booststdint.h>

// Library/third-party includes
// - none

// Standard includes
// - none

namespace transmission {
	typedef stdint::uint8_t MessageIdType;
	enum {
		MaxMessageId = 255
	};
} // end of namespace transmission

#endif // INCLUDED_MessageIdType_h_GUID_5d3f6687_240b_49f7_b325_52c417787cad
