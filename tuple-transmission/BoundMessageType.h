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
#include "detail/constants/ArityConfig.h"
#include "detail/types/MessageIdType.h"
#include "detail/operations/MessageArity.h"
#include "detail/operations/MessageCount.h"
#include <util/MPLFindIndex.h>

// Library/third-party includes
#include <boost/mpl/assert.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/greater.hpp>
#include <boost/mpl/not.hpp>

// Standard includes
// - none

namespace transmission {
	/// @brief A type representing a message type associated with a message collection.
	///
	/// This type is needed because a MessageType may be associated with multiple
	/// MessageCollections, and thus when used in different contexts, have different
	/// message identifiers, etc.
	///
	/// A number of compile-time assertions (checking for consistent state/usage
	/// of the library) happen here to keep the dependencies of the protocol
	/// definition headers MessageCollection.h and MessageType.h minimal.
	template<typename MessageCollection, typename MessageType>
	struct BoundMessageType {
		// Assert that this is indeed a message type
		BOOST_MPL_ASSERT((boost::mpl::equal< typename MessageType::message_type_tag, void>));

		// Assert that the collection includes this message type
		BOOST_MPL_ASSERT((boost::mpl::contains< typename MessageCollection::message_types, MessageType>));

		/// @brief self-typedef
		typedef BoundMessageType<MessageCollection, MessageType> type;

		/// @brief Message collection type
		typedef MessageCollection message_collection;

		/// @brief Message type
		typedef MessageType message_type;

		/// @brief Sequence of message types in the message collection
		typedef typename message_collection::message_types message_types;

		/// @brief Base envelope type specified by the message collection
		typedef typename message_collection::envelope_type::base envelope_type;

		/// @brief boost::mpl integral constant that uniquely identifies the
		/// message type within the context of this message collection
		typedef util::find_index<message_types, message_type> message_id;

		/// @brief The arity (number of elements/parameters) of the message type
		/// (as a boost::mpl integral constant)
		typedef detail::operations::MessageArity<MessageType> message_arity;

		// Assert that the library as configured can receive a message of this arity.
		BOOST_MPL_ASSERT((boost::mpl::equal<message_arity, boost::mpl::int_<detail::constants::ReceiveMaxArity> >));

		// Assert that the message collection was not defined with more messages
		// than permitted due to limits on the message ID type.
		BOOST_MPL_ASSERT((boost::mpl::not_<boost::mpl::greater< detail::operations::MessageCount<message_collection>, boost::mpl::int_<MaxMessageId> > >));
	};
} // end of namespace transmission

#endif // INCLUDED_BoundMessageType_h_GUID_fcc31d2e_6819_4b42_a365_0c7798060bad
