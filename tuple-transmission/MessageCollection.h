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
#ifndef INCLUDED_MessageCollection_h_GUID_81024018_afb3_496b_9041_7c5e4119d94d
#define INCLUDED_MessageCollection_h_GUID_81024018_afb3_496b_9041_7c5e4119d94d

// Internal Includes
// - none

// Library/third-party includes
// - none

// Standard includes
// - none


namespace transmission {
	/// @addtogroup ProtocolDefs Protocol Definition Types
	/// @brief Types you'll use in the protocol header you create and use
	/// on all communicating systems.
	/// @{

	/** @brief Template combining a sequence of MessageType types as well
		as an Envelope type.

		In your protocol header, you'll want something like
		typedef MessageCollection<mpl::vector<MessageA, MessageB>, envelopes::Basic> ComputerToDeviceMessages.
		where MessageA and MessageB are your message types inheriting from MessageType.

		@sa MessageType
	*/
	template<typename MessageTypeSequence, typename EnvelopeType>
	struct MessageCollection {
		typedef MessageCollection<MessageTypeSequence, EnvelopeType> message_collection_type;
		typedef MessageCollection<MessageTypeSequence, EnvelopeType> type;
		typedef EnvelopeType envelope_type;
		typedef MessageTypeSequence message_types;
	};
	/// @}
} // end of namespace transmission



#endif // INCLUDED_MessageCollection_h_GUID_81024018_afb3_496b_9041_7c5e4119d94d
