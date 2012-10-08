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
#ifndef INCLUDED_DeserializeDirectly_h_GUID_451f7225_28bc_4599_a348_b6d3d26e41ae
#define INCLUDED_DeserializeDirectly_h_GUID_451f7225_28bc_4599_a348_b6d3d26e41ae

// Internal Includes
#include "DeserializeOverloads_Generated.h"

// Library/third-party includes
// - none

// Standard includes
// - none

namespace transmission {
	namespace detail {
		namespace operations {
			namespace impl {


				template<typename SerializationPolicy, typename Function, typename Iterator>
				struct DeserializeFunctorWrapper {
					public:
						DeserializeFunctorWrapper(Function & func, Iterator & iter) : f(func), it(iter) {}

						template<typename MessageTypeWrapped>
						void operator()(MessageTypeWrapped const&) {
							namespace mpl = boost::mpl;
							generated::deserialize<typename MessageTypeWrapped::type, SerializationPolicy>(
							    f,
							    it/*,
							    mpl::identity< typename mpl::size<typename MessageTypeWrapped::type>::type >()*/
							);
						}
					private:
						Function & f;
						Iterator & it;
				};


			} // end of namespace impl
		} // end of namespace operations
	} // end of namespace detail
} // end of namespace transmission

#endif // INCLUDED_DeserializeDirectly_h_GUID_451f7225_28bc_4599_a348_b6d3d26e41ae
