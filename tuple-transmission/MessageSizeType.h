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
#ifndef INCLUDED_MessageSizeType_h_GUID_e46ad97b_2123_49bd_8b67_fc7ea9712e1c
#define INCLUDED_MessageSizeType_h_GUID_e46ad97b_2123_49bd_8b67_fc7ea9712e1c

// Internal Includes
#include "MaxMessageLength.h"

// Library/third-party includes
#include <boost/integer.hpp>

// Standard includes
// - none

namespace transmission {
	template<typename Collection>
	struct MessageSizeType {
		typedef typename boost::uint_value_t< MaxMessageLength<Collection>::value >::least type;
	};
} // end of namespace transmission

#endif // INCLUDED_MessageSizeType_h_GUID_e46ad97b_2123_49bd_8b67_fc7ea9712e1c
