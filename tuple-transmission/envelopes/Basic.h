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
#ifndef INCLUDED_envelopes_Basic_h_GUID_759f0310_b9bd_4bc3_aca7_0fb4238b31fd
#define INCLUDED_envelopes_Basic_h_GUID_759f0310_b9bd_4bc3_aca7_0fb4238b31fd

// Internal Includes
#include "../EnvelopeBase.h"
#include "../detail/ControlCodes.h"
#include "../IntegralTypes.h"

// Library/third-party includes
#include <boost/fusion/include/for_each.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/int.hpp>

// Standard includes
// - none

namespace transmission {
	namespace envelopes {
		struct Basic : EnvelopeBase<Basic> {
			typedef boost::mpl::int_ <
			1 /* start of transmission */ +
			1 /* message ID */ +
			1 /* start of text */ +
			1 /* end of text */ +
			1 /* end of transmission */ > overhead_size;

			template<typename MessageContentsSize>
			struct Size : boost::mpl::plus <overhead_size, MessageContentsSize > {};

			template<typename TransmitterType, typename MessageContentsType>
			static void sendMessage(TransmitterType & tx, MessageContentsType const & contents, MessageIdType msgId) {
				namespace ControlCodes = ::transmission::detail::ControlCodes;
				tx.output(ControlCodes::SOH);
				tx.output(msgId);
				tx.output(ControlCodes::STX);
				detail::SendContext<TransmitterType> functor(tx);
				boost::fusion::for_each(contents, functor);
				tx.output(ControlCodes::ETX);
				tx.output(ControlCodes::EOT);
			}
		};
	} //end of namespace envelopes
}// end of namespace transmission
#endif // INCLUDED_envelopes_Basic_h_GUID_759f0310_b9bd_4bc3_aca7_0fb4238b31fd
