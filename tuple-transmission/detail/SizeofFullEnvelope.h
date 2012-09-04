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
#ifndef INCLUDED_SizeofFullEnvelope_h_GUID_259bde6d_5143_4117_908e_5b0c402e6e4d
#define INCLUDED_SizeofFullEnvelope_h_GUID_259bde6d_5143_4117_908e_5b0c402e6e4d

// Internal Includes
#include "../Sizeof.h"

// Library/third-party includes
// - none

// Standard includes
// - none

namespace transmission {
	namespace detail {

		template<typename Envelope, typename MessageType>
		struct SizeofFullEnvelope {
			enum {
				value = (Envelope::Size< Sizeof<MessageType>::value >::value)
			};
		};

	} //end of namespace detail
}// end of namespace transmission

#endif // INCLUDED_SizeofFullEnvelope_h_GUID_259bde6d_5143_4117_908e_5b0c402e6e4d
