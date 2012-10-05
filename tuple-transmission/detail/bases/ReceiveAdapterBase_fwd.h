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
#ifndef INCLUDED_ReceiveAdapterBase_fwd_h_GUID_beac541f_4654_4a4d_87e0_f231d9cc7826
#define INCLUDED_ReceiveAdapterBase_fwd_h_GUID_beac541f_4654_4a4d_87e0_f231d9cc7826

// Internal Includes
// - none

// Library/third-party includes
// - none

// Standard includes
// - none

namespace transmission {
	namespace detail {
		template<typename Derived>
		class ReceiveAdapterBase;

		template<typename Derived>
		class ReceiveAdapterWithoutAvailable;
	} //end of namespace detail
} // end of namespace transmission
#endif // INCLUDED_ReceiveAdapterBase_fwd_h_GUID_beac541f_4654_4a4d_87e0_f231d9cc7826
