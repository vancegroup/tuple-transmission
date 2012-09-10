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
#ifndef INCLUDED_MessageCount_h_GUID_f0cfe291_5791_490d_a738_9da0f5c5dda5
#define INCLUDED_MessageCount_h_GUID_f0cfe291_5791_490d_a738_9da0f5c5dda5

// Internal Includes
// - none

// Library/third-party includes
#include <boost/mpl/size.hpp>

// Standard includes
// - none

namespace transmission {
	/// @brief Retrieves the number of messages defined in a message collection
	template<typename Collection>
	struct MessageCount : boost::mpl::size<typename Collection::message_types>::type {};
} // end of namespace transmission

#endif // INCLUDED_MessageCount_h_GUID_f0cfe291_5791_490d_a738_9da0f5c5dda5
