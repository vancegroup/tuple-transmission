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
#ifndef INCLUDED_EnvelopeBasic_h_GUID_759f0310_b9bd_4bc3_aca7_0fb4238b31fd
#define INCLUDED_EnvelopeBasic_h_GUID_759f0310_b9bd_4bc3_aca7_0fb4238b31fd

// Internal Includes
#include "EnvelopeBase.h"
#include "TransmissionBase.h"
#include "detail/ControlCodes.h"
#include <util/booststdint.h>

// Library/third-party includes
#include <boost/fusion/include/for_each.hpp>

// Standard includes
#include <cstring> // for std::memcpy

namespace transmission {
	namespace envelopes {
		struct Basic : EnvelopeBase<Basic> {
			template<int MessageContentsSize>
			struct Size {
				enum {
					value = 1 /* start of transmission */ +
					1 /* message ID */ +
					1 /* start of text */ +
					MessageContentsSize +
					1 /* end of text */ +
					1 /* end of transmission */
				};
			};

			template<typename TXDerived>
			struct SendContext {
				SendContext(TransmissionBase<TXDerived> & transmit) : xt(transmit) {}
				TransmissionBase<TXDerived> & xt;

				template<typename T>
				void operator()(T & value) {
					stdint::uint8_t buf[sizeof(T)];
					std::memcpy(&(buf[0]), &value, sizeof(T));
					xt.output(buf, sizeof(T));
				}

				void operator()(stdint::uint8_t data) {
					xt.output(data);
				}
			};

			template<typename TXDerived, typename MessageContentsType>
			static void sendMessage(TransmissionBase<TXDerived> & xt, MessageIdType msgId, MessageContentsType const & contents) {
				namespace ControlCodes = ::transmission::detail::ControlCodes;
				xt.output(ControlCodes::SOH);
				xt.output(msgId);
				xt.output(ControlCodes::STX);
				boost::fusion::for_each(contents, SendContext<TXDerived>(xt));
				xt.output(ControlCodes::ETX);
				xt.output(ControlCodes::EOT);
			}
		};
	} //end of namespace envelopes
}// end of namespace transmission
#endif // INCLUDED_EnvelopeBasic_h_GUID_759f0310_b9bd_4bc3_aca7_0fb4238b31fd
