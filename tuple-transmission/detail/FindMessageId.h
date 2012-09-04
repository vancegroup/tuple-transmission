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
#ifndef INCLUDED_FindMessageId_h_GUID_85ff7967_6f99_4669_91c8_2b6c63e12e00
#define INCLUDED_FindMessageId_h_GUID_85ff7967_6f99_4669_91c8_2b6c63e12e00

// Internal Includes
// - none

// Library/third-party includes
#include <boost/mpl/distance.hpp>
#include <boost/mpl/find.hpp>
#include <boost/mpl/int.hpp>

// Standard includes
// - none

namespace transmission {
	namespace detail {
		template<typename MessageCollection, typename MessageType>
		struct FindMessageId_helper {
			typedef typename MessageCollection::message_types message_types;
			typedef typename boost::mpl::begin<message_types>::type first;
			typedef typename boost::mpl::find<message_types, MessageType>::type position;
			enum {
				value = (boost::mpl::distance<first, position>::value)
			};
		};

		template<typename MessageCollection, typename MessageType>
		struct FindMessageId : boost::mpl::int_<FindMessageId_helper<MessageCollection, MessageType>::value>  {
		};
	} // end of namespace detail
} // end of namespace transmission

#endif // INCLUDED_FindMessageId_h_GUID_85ff7967_6f99_4669_91c8_2b6c63e12e00
