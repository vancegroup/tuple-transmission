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
#ifndef INCLUDED_MessageArity_h_GUID_f23d7d62_179c_498a_9fa7_2d40b375ef15
#define INCLUDED_MessageArity_h_GUID_f23d7d62_179c_498a_9fa7_2d40b375ef15

// Internal Includes
// - none

// Library/third-party includes
#include <boost/mpl/size.hpp>

// Standard includes
// - none


namespace transmission {
	namespace detail {
		namespace operations {
			/// @brief Retrieves the number of elements in a message.
			template<typename Message, typename = typename Message::message_type_tag>
			struct MessageArity : boost::mpl::size<typename Message::sequence_type>::type {};
		} // end of namespace operations
	} // end of namespace detail
} // end of namespace transmission


#endif // INCLUDED_MessageArity_h_GUID_f23d7d62_179c_498a_9fa7_2d40b375ef15
