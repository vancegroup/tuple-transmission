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
#ifndef INCLUDED_SerializedFieldSize_h_GUID_7698fa07_55a0_4afd_9847_61130a7839ab
#define INCLUDED_SerializedFieldSize_h_GUID_7698fa07_55a0_4afd_9847_61130a7839ab

// Internal Includes
// - none

// Library/third-party includes
#include <boost/mpl/sizeof.hpp>

// Standard includes
// - none

namespace transmission {
	namespace detail {
		namespace operations {
			template<typename T>
			struct SerializedFieldSize : boost::mpl::sizeof_<T> { };
		} // end of namespace operations
	} // end of namespace detail
} // end of namespace transmission

#endif // INCLUDED_SerializedFieldSize_h_GUID_7698fa07_55a0_4afd_9847_61130a7839ab
