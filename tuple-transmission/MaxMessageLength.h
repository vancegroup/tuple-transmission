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
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/transform_view.hpp>
#include <boost/mpl/max_element.hpp>

// Standard includes
// - none


namespace transmission {
	namespace detail {
		template<typename Collection>
		struct MaxMessageLength_impl {
			typedef typename boost::mpl::lambda<Sizeof<Transmission<Collection, boost::mpl::_> > >::type MessageSizeTransform;
			typedef typename Collection::message_types message_types;
			typedef typename boost::mpl::transform_view<message_types, MessageSizeTransform>::type MessageSizeSequence;
			typedef	typename boost::mpl::deref<typename boost::mpl::max_element<MessageSizeSequence>::type>::type MaxSize;
		};
	} // end of namespace detail
	template<typename Collection>
	struct MaxMessageLength : detail::MaxMessageLength_impl<Collection>::MaxSize {};

} // end of namespace transmission
#endif // INCLUDED_MaxMessageLength_h_GUID_1839c18a_36e9_48ed_8cd8_02e3f34fce28
