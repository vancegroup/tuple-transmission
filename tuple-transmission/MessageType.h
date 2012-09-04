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
#ifndef INCLUDED_MessageType_h_GUID_eef26e08_32f9_4c37_9c5b_058b281c319a
#define INCLUDED_MessageType_h_GUID_eef26e08_32f9_4c37_9c5b_058b281c319a

// Internal Includes
// - none

// Library/third-party includes
// - none

// Standard includes
// - none


namespace transmission {

	/// @brief Base class for your message types: pass an MPL vector of field types
	template<typename MPLVector>
	struct MessageTypeBase : MPLVector {
		typedef MPLVector base;
	};
} // end of namespace transmission


#endif // INCLUDED_MessageType_h_GUID_eef26e08_32f9_4c37_9c5b_058b281c319a
