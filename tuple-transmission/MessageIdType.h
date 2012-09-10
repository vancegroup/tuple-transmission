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
#include "MessageCount.h"

// Library/third-party includes
#include <boost/integer.hpp>

// Standard includes
// - none

namespace transmission {
	template<typename Collection>
	struct MinimalMessageIdType {
		typedef typename boost::uint_value_t<MessageCount<Collection>::value>::least type;
	};
} // end of namespace transmission

#endif // INCLUDED_MessageIdType_h_GUID_5d3f6687_240b_49f7_b325_52c417787cad
