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
#include "../constants/MessageBufferSizeScale.h"

// Library/third-party includes
#include <boost/mpl/times.hpp>

// Standard includes
// - none

namespace transmission {
	namespace detail {
		namespace operations {

			template<typename Collection>
			struct ComputeReceiveBufferSize {
				typedef MaxMessageLength<Collection> CollectionMaxMessageLength;
				enum {
					value = (boost::mpl::times< CollectionMaxMessageLength, constants::MessageBufferSizeScale>::value)
				};
			};

		} // end of namespace operations
	} // end of namespace detail
} // end of namespace transmission

#endif // INCLUDED_ComputeReceiveBufferSize_h_GUID_f572e46a_ae62_41f2_9046_fbd575dca2f0
