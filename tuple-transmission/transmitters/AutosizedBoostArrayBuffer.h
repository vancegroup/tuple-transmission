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
#ifndef INCLUDED_AutosizedBoostArrayBuffer_h_GUID_fee1f069_68fd_455a_b3a7_932d8b8a00f9
#define INCLUDED_AutosizedBoostArrayBuffer_h_GUID_fee1f069_68fd_455a_b3a7_932d8b8a00f9

// Internal Includes
#include "BoostArrayBuffer.h"
#include "../detail/operations/Sizeof.h"
#include "../detail/operations/MaxMessageLength.h"

// Library/third-party includes
// - none

// Standard includes
// - none


namespace transmission {
	namespace transmitters {
		/// @addtogroup Transmitters Transmitter Classes
		/// @{

		/// @brief A version of BoostArrayBuffer that automatically computes
		/// the precise size needed for a single bound message type.
		template<typename BoundMessage>
		class AutosizedBoostArrayBuffer : public BoostArrayBuffer< detail::operations::Sizeof<BoundMessage>::value > {};

		/// @brief A version of BoostArrayBuffer that automatically computes
		/// the size needed for the largest message in a message collection.
		template<typename Collection>
		class CollectionAutosizedBoostArrayBuffer : public BoostArrayBuffer< detail::operations::MaxMessageLength<Collection>::value > {

		};
		/// @}
	} // end of namespace transmitters
} // end of namespace transmission

#endif // INCLUDED_AutosizedBoostArrayBuffer_h_GUID_fee1f069_68fd_455a_b3a7_932d8b8a00f9
