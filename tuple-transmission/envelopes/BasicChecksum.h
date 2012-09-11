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
#ifndef INCLUDED_envelopes_BasicChecksum_h_GUID_532406a6_8426_4b80_9f3c_6c7b16b7a49e
#define INCLUDED_envelopes_BasicChecksum_h_GUID_532406a6_8426_4b80_9f3c_6c7b16b7a49e

// Internal Includes
#include "../detail/bases/EnvelopeBase.h"
#include "../detail/constants/ControlCodes.h"
#include "../detail/types/IntegralTypes.h"
#include "../transmitters/ChecksumComputer.h"
#include "../transmitters/TransmitterComposition.h"
#include "../serializers/BitwiseCopySerialization.h"

// Library/third-party includes
#include <boost/mpl/plus.hpp>
#include <boost/mpl/int.hpp>

// Standard includes
// - none

namespace transmission {
	namespace envelopes {
		struct BasicChecksum : EnvelopeBase<BasicChecksum, serializers::BitwiseCopy> {
			typedef boost::mpl::int_ <
			1 /* start of transmission */ +
			1 /* message ID */ +
			1 /* start of text */ +
			1 /* end of text */ +
			1 /* checksum */ +
			1 /* end of transmission */ > overhead_size;

			template<typename MessageContentsSize>
			struct Size : boost::mpl::plus <overhead_size, MessageContentsSize > {};

			typedef EnvelopeBase<BasicChecksum, serializers::BitwiseCopy> base;

			template<typename TransmitterType, typename MessageContentsType>
			static void sendMessage(TransmitterType & tx, MessageContentsType const & contents, MessageIdType msgId) {
				namespace ControlCodes = ::transmission::detail::constants::ControlCodes;
				typedef transmitters::TransmitterComposition<transmitters::ChecksumComputer, TransmitterType> ComposedTransmitter;

				transmitters::ChecksumComputer checksum;
				ComposedTransmitter txComposed(checksum, tx);

				txComposed.output(ControlCodes::SOH);
				txComposed.output(msgId);
				txComposed.output(ControlCodes::STX);
				base::bufferTuple(txComposed, contents);
				txComposed.output(ControlCodes::ETX);
				tx.output(checksum.checksum());
				tx.output(ControlCodes::EOT);
			}
		};
	} //end of namespace envelopes
}// end of namespace transmission

#endif // INCLUDED_envelopes_BasicChecksum_h_GUID_532406a6_8426_4b80_9f3c_6c7b16b7a49e
