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
#include "IntegralTypes.h"

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

			template<typename TransmitterType>
			struct SendContext {
				SendContext(TransmitterType & transmit) : tx(transmit) {}
				TransmitterType & tx;

				template<typename T>
				void operator()(T & value) {
					stdint::uint8_t buf[sizeof(T)];
					std::memcpy(&(buf[0]), &value, sizeof(T));
					tx.output(buf, sizeof(T));
				}

				void operator()(uint8_t data) {
					tx.output(data);
				}
			};

			template<typename TransmitterType, typename MessageContentsType>
			static void sendMessage(TransmitterType & tx, MessageContentsType const & contents, MessageIdType msgId) {
				namespace ControlCodes = ::transmission::detail::ControlCodes;
				tx.output(ControlCodes::SOH);
				tx.output(msgId);
				tx.output(ControlCodes::STX);
				boost::fusion::for_each(contents, SendContext<TransmitterType>(tx));
				tx.output(ControlCodes::ETX);
				tx.output(ControlCodes::EOT);
			}
		};
	} //end of namespace envelopes
}// end of namespace transmission
#endif // INCLUDED_EnvelopeBasic_h_GUID_759f0310_b9bd_4bc3_aca7_0fb4238b31fd
