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
#include "../detail/bases/EnvelopeBase.h"
#include "../detail/constants/ControlCodes.h"
#include "../detail/types/IntegralTypes.h"
#include "../serializers/BitwiseCopySerialization.h"

// Library/third-party includes
#include <boost/mpl/plus.hpp>
#include <boost/mpl/int.hpp>

// Standard includes
// - none

#ifndef BOOST_TEST_MESSAGE
#define BOOST_TEST_MESSAGE(X)
#endif

namespace transmission {
	namespace envelopes {
		struct Basic : EnvelopeBase<Basic, serializers::BitwiseCopy> {
			typedef boost::mpl::int_ <
			1 /* start of transmission */ +
			1 /* message ID */ +
			1 /* start of text */ +
			1 /* end of text */ +
			1 /* end of transmission */ > overhead_size;

			typedef boost::mpl::int_<3> data_offset;

			typedef EnvelopeBase<Basic, serializers::BitwiseCopy> base;

			template<typename MessageContentsSize>
			struct Size : boost::mpl::plus <overhead_size, MessageContentsSize > {};

			template<typename TransmitterType, typename MessageContentsType>
			static void sendMessage(TransmitterType & tx, MessageContentsType const & contents, MessageIdType msgId) {
				namespace ControlCodes = ::transmission::detail::constants::ControlCodes;
				tx.output(ControlCodes::SOH);
				tx.output(msgId);
				tx.output(ControlCodes::STX);
				base::bufferTuple(tx, contents);
				tx.output(ControlCodes::ETX);
				tx.output(ControlCodes::EOT);
			}

			template<typename EnvelopeReceiveType>
			static bool checkBufferForMessage(EnvelopeReceiveType & recv) {
				namespace ControlCodes = ::transmission::detail::constants::ControlCodes;
				while (!recv.bufferEmpty()) {
					BOOST_TEST_MESSAGE("Buffer size: " << int(recv.bufferSize()));
					if (recv.bufferFront() != ControlCodes::SOH) {
						BOOST_TEST_MESSAGE("Popping front of buffer to find SOH.");
						recv.bufferPopFront();
					} else {
						break;
					}
				}

				if (recv.bufferSize() < 2) {
					// haven't seen message start and ID.
					BOOST_TEST_MESSAGE("Returning - haven't seen message start and ID.");
					return false;
				}

				BOOST_TEST_MESSAGE("Setting current message ID.");
				recv.setCurrentMessageId(recv.buffer(1));
				if (!recv.isCurrentMessageIdValid()) {
					/// False alarm: that's not a valid message ID.
					/// Pop off the start code and try again.
					BOOST_TEST_MESSAGE("Current message ID invalid.");
					return base::popAndRetry(recv);
				}
				if (recv.bufferSize() < 3) {
					// Can't have seen ControlCodes::STX
					BOOST_TEST_MESSAGE("Returning - waiting for third character STX, only have " << int(recv.bufferSize()));
					return false;
				}
				if (recv.buffer(2) != ControlCodes::STX) {
					/// Unexpected - this isn't the right start either.
					/// Pop off the start code and try again.
					BOOST_TEST_MESSAGE("Popping and retrying because the third element isn't STX.");
					return base::popAndRetry(recv);
				}

				typename EnvelopeReceiveType::message_size_type msgLength = recv.getMessageLength();
				if (recv.bufferSize() < msgLength) {
					/// Gotta wait some more.
					BOOST_TEST_MESSAGE("Returning - have to wait for " << int(msgLength) << " and only have " << int(recv.bufferSize()));
					return false;
				}

				if ((recv.buffer(msgLength - 2) != ControlCodes::ETX) || (recv.buffer(msgLength - 1) != ControlCodes::EOT)) {
					/// Message ending isn't right.
					/// Pop off the start code and try again.
					BOOST_TEST_MESSAGE("Message ending is wrong - pop and retry.");
					return base::popAndRetry(recv);
				}

				/// We passed the gauntlet!
				return true;
			}
		};
	} //end of namespace envelopes
}// end of namespace transmission
#endif // INCLUDED_envelopes_Basic_h_GUID_759f0310_b9bd_4bc3_aca7_0fb4238b31fd
