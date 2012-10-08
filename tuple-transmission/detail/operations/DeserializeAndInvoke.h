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
#ifndef INCLUDED_DeserializeAndInvoke_h_GUID_252a9b27_ba20_4cd5_84ba_a399a673ed92
#define INCLUDED_DeserializeAndInvoke_h_GUID_252a9b27_ba20_4cd5_84ba_a399a673ed92

// Internal Includes
#include "../types/MessageIdType.h"
#include "DeserializeToFusion.h"
#include <util/MPLApplyAt.h>

// Library/third-party includes
// - none

// Standard includes
// - none

namespace transmission {
	namespace detail {
		namespace operations {
			/// @brief Turns the runtime id number into the corresponding message type (type sequence)
			/// and calls the deserializer on it, passing along a functor.
			template<typename MessageTypes, typename SerializationPolicy, typename Function, typename Iterator>
			inline void deserializeAndInvoke(MessageIdType id, Function & f, Iterator const & it) {
				Iterator modifyable_iter = it;
				typedef impl::DeserializeFunctorWrapper<SerializationPolicy, Function, Iterator> WrapperType;
				WrapperType fWrapper(f, modifyable_iter);
				util::apply_at<MessageTypes>(id, fWrapper);
			}
		} // end of namespace operations
	} // end of namespace detail
} // end of namespace transmission
#endif // INCLUDED_DeserializeAndInvoke_h_GUID_252a9b27_ba20_4cd5_84ba_a399a673ed92
