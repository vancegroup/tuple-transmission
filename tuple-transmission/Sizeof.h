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
#ifndef INCLUDED_Sizeof_h_GUID_3ceba20a_f94b_42e0_9db4_4dd04dedfc12
#define INCLUDED_Sizeof_h_GUID_3ceba20a_f94b_42e0_9db4_4dd04dedfc12

// Internal Includes
#include "Sizeof_fwd.h"
#include "TransmissionBase_fwd.h"

// Library/third-party includes
#include <boost/mpl/accumulate.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/sizeof.hpp>

// Standard includes
// - none

namespace transmission {

	/// @brief Metafunction to compute the size of a message given a typelist.
	template<typename MPLTypeSequence>
	struct Sizeof : boost::mpl::accumulate
			< MPLTypeSequence
			, boost::mpl::int_<0>
			, boost::mpl::plus<boost::mpl::_1, boost::mpl::sizeof_<boost::mpl::_2> >
			>::type {};

	namespace detail {
		template<typename EnvelopeType, typename MessageType>
		struct SizeofTransmission_Helper {
			typedef typename EnvelopeType::base envelope_type;
			typedef Sizeof<MessageType> inner_size;
			enum {
				value = (envelope_type::template Size< inner_size::value >::value)
			};
		};
	}
	// Template specialization for TransmissionType
	template<typename EnvelopeType, typename MessageID, typename MessageType>
	struct Sizeof< TransmissionBase<EnvelopeType, MessageID, MessageType> > : boost::mpl::int_<detail::SizeofTransmission_Helper<EnvelopeType, MessageType>::value> {};
} // end of namespace transmission

#endif // INCLUDED_Sizeof_h_GUID_3ceba20a_f94b_42e0_9db4_4dd04dedfc12
