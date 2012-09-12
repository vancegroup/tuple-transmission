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
#include "DeserializeOverloads_Generated.h"
#include "../types/IntegralTypes.h"

// Library/third-party includes
// - none

// Standard includes
// - none

namespace transmission {
	namespace detail {
		namespace operations {
			/*
				namespace impl {
					template<typename SerializationPolicy, typename MessageType, typename Function, typename Iterator>
					struct DeserializeFunctorWrapper {
						public:
							DeserializeFunctorWrapper(Function & func, Iterator & iter) : f(func), it(iter) {}

							template<typename MessageSize>
							void operator()(MessageSize const& m) {
								generated::deserialize<SerializationPolicy, MessageType>(f, it, m);
							}
						private:
							Function & f;
							Iterator & it;
					}


				} // end of namespace impl
				*/
			template<typename SerializationPolicy, typename MessageType, typename Function, typename Iterator>
			void deserializeAndInvoke(Function & f, Iterator & it) {
//				typedef impl::DeserializeFunctorWrapper<SerializationPolicy, MessageType, Function, Iterator> WrapperType;
//				WrapperType fWrapper(f, it);

				generated::deserialize<MessageType, SerializationPolicy>(f, it);
//				runtime_int_to_type_impl< uint8_t, generated::DeserializeMaxArity, WrapperType &>::apply(
			}
		} // end of namespace operations
	} // end of namespace detail
} // end of namespace transmission
#endif // INCLUDED_DeserializeAndInvoke_h_GUID_252a9b27_ba20_4cd5_84ba_a399a673ed92
