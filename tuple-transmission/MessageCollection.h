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
#include "Sizeof.h"

// Library/third-party includes
// - none

// Standard includes
// - none


namespace transmission {
	namespace envelopes {
		struct Basic;
		struct BasicWithChecksum;
	} //end of namespace envelopes

	namespace detail {
		/// @brief Internal base class depending only on envelope type
		template<typename EnvelopeType>
		struct MessageCollectionEnvelopeBase {

		};
	}
	template<typename MessageTypeSequence, typename EnvelopeType = envelopes::Basic>
	struct MessageCollection {
		typedef MessageTypeSequence message_types;

		template<typename MessageType>
		struct MessageSize {
			enum {
				value = (EnvelopeType::template Size< SizeofMessage<MessageType>::value >::value)
			};
		};

	};
} // end of namespace transmission



#endif // INCLUDED_MessageCollection_h_GUID_81024018_afb3_496b_9041_7c5e4119d94d
