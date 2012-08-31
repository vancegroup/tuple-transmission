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
#ifndef INCLUDED_FusionType_h_GUID_8b324a0b_f761_4b4b_acef_ae8504cfa201
#define INCLUDED_FusionType_h_GUID_8b324a0b_f761_4b4b_acef_ae8504cfa201

// Internal Includes
// - none

// Library/third-party includes
#include <boost/fusion/mpl.hpp> // mpl to fusion link
#include <boost/fusion/include/as_vector.hpp>

// Standard includes
// - none


namespace transmission {
	/// @brief A metafunction (really, just a wrapper) to convert a typelist type
	/// to the corresponding Fusion (vector-style) tuple type.
	template<typename MPLTypeSequence>
	struct FusionType {
		typedef typename boost::fusion::result_of::as_vector<MPLTypeSequence>::type type;
	};
} // end of namespace transmission

#endif // INCLUDED_FusionType_h_GUID_8b324a0b_f761_4b4b_acef_ae8504cfa201
