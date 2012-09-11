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
#ifndef INCLUDED_MessageLength_h_GUID_0215a2a9_3a73_4021_bfb6_e4a0e8f20dda
#define INCLUDED_MessageLength_h_GUID_0215a2a9_3a73_4021_bfb6_e4a0e8f20dda

// Internal Includes
#include "../types/MessageSizeType.h"
#include "../types/MessageIdType.h"
#include "MessageCount.h"
#include "IsIdValid.h"
#include "../../Transmission.h"
#include <util/MPLApplyAt.h>

// Library/third-party includes
#include <boost/mpl/at.hpp>

// Standard includes
// - none


namespace transmission {
	namespace detail {
		namespace operations {
			namespace impl {
				template<typename Collection>
				struct GetSizeof {
					typedef typename MessageSizeType<Collection>::type SizeType;
					GetSizeof(SizeType & s) : ret(s) {}

					template<typename T>
					void operator()(T const&) {
						ret = Sizeof< Transmission<Collection, typename T::type> >();
					}

					SizeType & ret;
				};
			} // end of namespace impl

			/// @brief Compile-time lookup of message length by ID
			template<typename Collection, typename MessageId>
			struct MessageLength : Sizeof < Transmission < Collection, typename boost::mpl::at<typename Collection::message_types, MessageId>::type > > {};

			/// @brief Runtime lookup of message length by ID
			///
			/// @note Behavior if id is not valid is undefined - see isIdValid()
			template<typename Collection>
			typename MessageSizeType<Collection>::type getMessageLength(typename MinimalMessageIdType<Collection>::type id) {
				if (!isIdValid<Collection>(id)) {
					return typename MessageSizeType<Collection>::type();
				}
				typename MessageSizeType<Collection>::type retval;
				util::apply_at<typename Collection::message_types>(id, impl::GetSizeof<Collection>(retval));
				return retval;
			};

		} // end of namespace operations
	} // end of namespace detail
} // end of namespace transmission


#endif // INCLUDED_MessageLength_h_GUID_0215a2a9_3a73_4021_bfb6_e4a0e8f20dda
