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
#ifndef INCLUDED_MessageCollectionTypes_h_GUID_e55e1d94_82c9_413c_9a95_ed7870c141a7
#define INCLUDED_MessageCollectionTypes_h_GUID_e55e1d94_82c9_413c_9a95_ed7870c141a7

// Internal Includes
#include "MessageIdType_fwd.h"
#include "MessageSizeType_fwd.h"

// Library/third-party includes
//#include <boost/optional/optional_fwd.hpp>

// Standard includes
// - none

namespace transmission {
	template<typename Collection>
	struct MessageCollectionTypes {
		typedef typename MinimalMessageIdType<Collection>::type message_id_type;
		typedef typename MessageSizeType<Collection>::type message_size_type;
		/// @todo remove following line
		// typedef typename boost::optional<message_size_type> message_size_result_type;
	};
} // end of namespace transmission

#endif // INCLUDED_MessageCollectionTypes_h_GUID_e55e1d94_82c9_413c_9a95_ed7870c141a7
