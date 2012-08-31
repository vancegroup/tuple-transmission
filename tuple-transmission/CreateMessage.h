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

#if !BOOST_PP_IS_ITERATING

#ifndef INCLUDED_CreateMessage_h_GUID_2ba271ba_4d39_405e_b6b0_740628a44562
#define INCLUDED_CreateMessage_h_GUID_2ba271ba_4d39_405e_b6b0_740628a44562

// Internal Includes
#include "FusionType.h"

// Library/third-party includes
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/mpl/at.hpp>

// Standard includes
// - none


namespace transmission {

#ifndef TUPLETRANSMISSION_MAX_EASY_ARITY
#define TUPLETRANSMISSION_MAX_EASY_ARITY 8
#endif

#define TYPED_ARG(z, N, DATA) typename boost::mpl::at_c<MPLTypeSequence, N>::type BOOST_PP_CAT(a, N)

#define BOOST_PP_ITERATION_PARAMS_1 (3, (1, TUPLETRANSMISSION_MAX_EASY_ARITY, "tuple-transmission/CreateMessage.h") )
#include BOOST_PP_ITERATE()

} // end of namespace transmission

#undef TYPED_ARG

#endif // INCLUDED_CreateMessage_h_GUID_2ba271ba_4d39_405e_b6b0_740628a44562

#else // OK we're iterating

#define ARITY BOOST_PP_ITERATION()

template<typename MPLTypeSequence>
inline typename FusionType<MPLTypeSequence>::type createMessage(BOOST_PP_ENUM(ARITY, TYPED_ARG, NULL)) {
	return typename FusionType<MPLTypeSequence>::type(BOOST_PP_ENUM_PARAMS(ARITY, a));
}

#undef ARITY
#endif
