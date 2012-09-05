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
#ifndef INCLUDED_OutputArray_h_GUID_c515cfa1_361e_4165_8030_f3530d5da217
#define INCLUDED_OutputArray_h_GUID_c515cfa1_361e_4165_8030_f3530d5da217

// Internal Includes
// - none

// Library/third-party includes
#include <boost/array.hpp>
#include <boost/io/ios_state.hpp>

// Standard includes
#include <ostream>

namespace boost {
	template<typename T, size_t N>
	::std::ostream & operator<<(::std::ostream & s, array<T, N> const& val) {
		io::ios_flags_saver ifs( s );
		for (size_t i = 0; i < N; ++i) {
			s << " <" << ::std::hex << ::std::showbase << static_cast<unsigned>(val[i]) << "> ";
		}
		return s;
	}
}

#endif // INCLUDED_OutputArray_h_GUID_c515cfa1_361e_4165_8030_f3530d5da217
