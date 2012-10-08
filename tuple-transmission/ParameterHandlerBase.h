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
#ifndef INCLUDED_ParameterHandlerBase_h_GUID_79f0cb9d_69d6_4cbc_be36_a30344064e9d
#define INCLUDED_ParameterHandlerBase_h_GUID_79f0cb9d_69d6_4cbc_be36_a30344064e9d

// Internal Includes
#include "detail/constants/ArityConfig.h"
#include "Receiver.h"

// Library/third-party includes
#include <boost/fusion/include/push_front.hpp>
#include <boost/fusion/functional/invocation/invoke_procedure.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/fusion/include/is_sequence.hpp>

// Standard includes
// - none

#ifndef BOOST_TEST_MESSAGE
#define BOOST_TEST_MESSAGE(X)
#endif

namespace transmission {

	/** @brief Base class for use in creating functors for transmission::Receiver
		that accept message contents as separate parameters to the function call,
		rather than as a tuple.
	*/
	template<typename Derived>
	class ParameterHandlerBase  {
		public:
			template<typename M, typename Sequence>
			void operator()(M const &,
			                Sequence const& s,
			                typename M::message_type_tag * = NULL,
			                typename boost::enable_if<boost::fusion::traits::is_sequence<Sequence> >::type * = NULL) {
				BOOST_TEST_MESSAGE("Invoking - sequence contains " << boost::fusion::size(s) << " elements");
				boost::fusion::invoke_procedure<Derived &>(getDerived(), boost::fusion::push_front(s, M()));
			}
		private:
			Derived & getDerived() {
				return *(static_cast<Derived *>(this));
			}
	};
} // end of namespace transmission

#endif // INCLUDED_ParameterHandlerBase_h_GUID_79f0cb9d_69d6_4cbc_be36_a30344064e9d
