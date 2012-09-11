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
#ifndef INCLUDED_ComputeReceiveBufferSize_h_GUID_f572e46a_ae62_41f2_9046_fbd575dca2f0
#define INCLUDED_ComputeReceiveBufferSize_h_GUID_f572e46a_ae62_41f2_9046_fbd575dca2f0

// Internal Includes
#include "MaxMessageLength.h"

// Library/third-party includes
#include <boost/mpl/times.hpp>
#include <boost/mpl/int.hpp>

// Standard includes
// - none

namespace transmission {
	namespace detail {
		typedef boost::mpl::int_<3> MessageBufferSizeScale;

		template<typename Collection>
		struct ComputeReceiveBufferSize {
			typedef MaxMessageLength<Collection> MaxMessageLength;
			enum {
				value = (boost::mpl::times< MaxMessageLength, MessageBufferSizeScale>::value)
			};
		};
	} // end of namespace detail
} // end of namespace transmission

#endif // INCLUDED_ComputeReceiveBufferSize_h_GUID_f572e46a_ae62_41f2_9046_fbd575dca2f0
