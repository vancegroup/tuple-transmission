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
#ifndef INCLUDED_MaxMessageLength_h_GUID_1839c18a_36e9_48ed_8cd8_02e3f34fce28
#define INCLUDED_MaxMessageLength_h_GUID_1839c18a_36e9_48ed_8cd8_02e3f34fce28

// Internal Includes
#include "Sizeof.h"

// Library/third-party includes
#include <boost/mpl/less.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/max_element.hpp>

// Standard includes
// - none


namespace transmission {
	namespace detail {
		namespace operations {

			namespace impl {
				template<typename Collection>
				struct TotalMessageSizeLess {
					template<typename A, typename B>
					struct apply : boost::mpl::less< Sizeof<Transmission<Collection, A> >, Sizeof<Transmission<Collection, B> > > {};
				};
			} // end of namespace impl

			template<typename Collection>
			struct MaxMessage : boost::mpl::deref< typename boost::mpl::max_element<typename Collection::message_types, impl::TotalMessageSizeLess<Collection> >::type > {};

			template<typename Collection>
			struct MaxMessageLength : Sizeof< Transmission<Collection, typename MaxMessage<Collection>::type > > {};
		} // end of namespace operations
	} // end of namespace detail
} // end of namespace transmission
#endif // INCLUDED_MaxMessageLength_h_GUID_1839c18a_36e9_48ed_8cd8_02e3f34fce28
