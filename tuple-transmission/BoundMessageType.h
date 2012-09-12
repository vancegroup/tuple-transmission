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
#ifndef INCLUDED_BoundMessageType_h_GUID_fcc31d2e_6819_4b42_a365_0c7798060bad
#define INCLUDED_BoundMessageType_h_GUID_fcc31d2e_6819_4b42_a365_0c7798060bad

// Internal Includes
#include "BoundMessageType_fwd.h"
#include <util/MPLFindIndex.h>

// Library/third-party includes
#include <boost/mpl/assert.hpp>

// Standard includes
// - none

namespace transmission {
	/// @brief A type representing a message type associated with a message collection.
	///
	/// This type is needed because a MessageType may be associated with multiple
	/// MessageCollections, and thus when used in different contexts, have different
	/// message identifiers, etc.
	template<typename MessageCollection, typename MessageType>
	struct BoundMessageType {
		BOOST_MPL_ASSERT((boost::mpl::contains< typename MessageCollection::message_types, MessageType>));

		typedef BoundMessageType<MessageCollection, MessageType> type;
		typedef MessageCollection message_collection;
		typedef typename MessageCollection::message_types message_types;
		typedef typename MessageCollection::envelope_type::base envelope_type;
		typedef MessageType message_type;
		typedef util::find_index<typename MessageCollection::message_types, MessageType> message_id;
	};
} // end of namespace transmission

#endif // INCLUDED_BoundMessageType_h_GUID_fcc31d2e_6819_4b42_a365_0c7798060bad
