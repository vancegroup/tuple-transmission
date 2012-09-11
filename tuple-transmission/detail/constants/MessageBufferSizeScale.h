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
#ifndef INCLUDED_MessageBufferSizeScale_h_GUID_b8da68a5_994a_481e_b030_1f76e9c34176
#define INCLUDED_MessageBufferSizeScale_h_GUID_b8da68a5_994a_481e_b030_1f76e9c34176

// Internal Includes
// - none

// Library/third-party includes
#include <boost/mpl/int.hpp>

// Standard includes
// - none


namespace transmission {
	namespace detail {
		namespace constants {
			typedef boost::mpl::int_<3> MessageBufferSizeScale;
		} // end of namespace constants
	} // end of namespace detail
} // end of namespace transmission


#endif // INCLUDED_MessageBufferSizeScale_h_GUID_b8da68a5_994a_481e_b030_1f76e9c34176
