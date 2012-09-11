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
#ifndef INCLUDED_IsIdValid_h_GUID_78626b63_35d3_4fc6_8033_ef1119ae337f
#define INCLUDED_IsIdValid_h_GUID_78626b63_35d3_4fc6_8033_ef1119ae337f

// Internal Includes
#include "../MessageIdType.h"
#include "../MessageCount.h"

// Library/third-party includes
// - none

// Standard includes
// - none
namespace transmission {
	namespace detail {
		/// @brief Given a message collection, is this message ID valid?
		template<typename Collection>
		bool isIdValid(typename MinimalMessageIdType<Collection>::type id) {
			return id < MessageCount<Collection>();
		}
	}
} // end of namespace transmission
#endif // INCLUDED_IsIdValid_h_GUID_78626b63_35d3_4fc6_8033_ef1119ae337f
