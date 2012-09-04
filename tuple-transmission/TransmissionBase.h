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
#ifndef INCLUDED_TransmissionBase_h_GUID_83718704_20bd_4134_b7bd_01987db8f10a
#define INCLUDED_TransmissionBase_h_GUID_83718704_20bd_4134_b7bd_01987db8f10a

// Internal Includes
#include "TransmissionBase_fwd.h"

// Library/third-party includes
// - none

// Standard includes
// - none

namespace transmission {
	template<typename EnvelopeType, typename MessageID, typename MessageType>
	struct TransmissionBase {
		typedef TransmissionBase<EnvelopeType, MessageID, MessageType> transmission_type;
		typedef EnvelopeType envelope_type;
		typedef MessageType message_type;
		typedef EnvelopeType message_id;
		enum {
			msg_id_c = MessageID::value
		};
	};
} // end of namespace transmission

#endif // INCLUDED_TransmissionBase_h_GUID_83718704_20bd_4134_b7bd_01987db8f10a
