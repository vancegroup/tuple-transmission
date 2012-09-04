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
#include "Envelopes_fwd.h"

// Library/third-party includes
// - none

// Standard includes
// - none


namespace transmission {

	template<typename MessageTypeSequence, typename EnvelopeType = envelopes::Basic>
	struct MessageCollection {
		typedef MessageCollection<MessageTypeSequence, EnvelopeType> message_collection_type;
		typedef EnvelopeType envelope_type;
		typedef MessageTypeSequence message_types;

		/*
				/// @brief Metafunction to access the full message size, including envelope - must include Sizeof.h
				template<typename MessageType>
				struct MessageSize {
					typedef typename AddContextToMessageType<message_collection_type, MessageType>::type MsgTCtx;
					enum {
						value = (SizeofMessage<MsgTCtx>::value)
					};
				};

				/// @brief Method to send a message - must include SendMessage.h
				template<typename MessageType, typename TXDerived, typename MessageContentType>
				void send(TransmissionBase<TXDerived> & xt, MessageContentType const & contents) {
					typedef typename AddContextToMessageType<message_collection_type, MessageType>::type MsgTCtx;
					MsgTCtx::sendMessage(xt, contents);
				}
		*/
	};

} // end of namespace transmission



#endif // INCLUDED_MessageCollection_h_GUID_81024018_afb3_496b_9041_7c5e4119d94d
