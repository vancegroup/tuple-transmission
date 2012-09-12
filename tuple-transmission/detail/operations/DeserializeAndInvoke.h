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
#ifndef INCLUDED_DeserializeAndInvoke_h_GUID_252a9b27_ba20_4cd5_84ba_a399a673ed92
#define INCLUDED_DeserializeAndInvoke_h_GUID_252a9b27_ba20_4cd5_84ba_a399a673ed92

// Internal Includes
// - none

// Library/third-party includes
// - none

// Standard includes
// - none

namespace transmission {
	namespace detail {
		namespace operations {
			template<typename SerializationPolicy, typename MessageType, typename Function, typename Iterator>
			void deserializeAndInvoke(Function & f, Iterator & it) {
			
			}
		} // end of namespace operations
	} // end of namespace detail
} // end of namespace transmission
#endif // INCLUDED_DeserializeAndInvoke_h_GUID_252a9b27_ba20_4cd5_84ba_a399a673ed92
