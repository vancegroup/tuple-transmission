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
#ifndef INCLUDED_Transmission_h_GUID_fcc31d2e_6819_4b42_a365_0c7798060bad
#define INCLUDED_Transmission_h_GUID_fcc31d2e_6819_4b42_a365_0c7798060bad

// Internal Includes
#include "detail/FindMessageId.h"
#include "TransmissionBase.h"

// Library/third-party includes
// - none

// Standard includes
// - none

namespace transmission {
	template<typename MessageCollection, typename MessageType>
	struct Transmission : TransmissionBase<typename MessageCollection::envelope_type, detail::FindMessageId<MessageCollection, MessageType>, MessageType> {};
} // end of namespace transmission

#endif // INCLUDED_Transmission_h_GUID_fcc31d2e_6819_4b42_a365_0c7798060bad
