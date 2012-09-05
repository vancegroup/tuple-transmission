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
#ifndef INCLUDED_SendMessage_h_GUID_9cbfc065_ea71_4097_8993_c4e0b0fb14c5
#define INCLUDED_SendMessage_h_GUID_9cbfc065_ea71_4097_8993_c4e0b0fb14c5

// Internal Includes
#include "MessageCollection.h"
#include "TransmitterBase.h"
#include "EnvelopeBase.h"
#include "IntegralTypes.h"
//#include "Transmission.h" // @todo Not strictly required for this file, but for its common usage.

// Library/third-party includes
#include <boost/mpl/equal.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/fusion/mpl.hpp>

// Standard includes
// - none

namespace transmission {

	namespace detail {
		template<typename TransmitterType>
		struct SendContext {
			SendContext(TransmitterType & transmit) : tx(transmit) {}
			TransmitterType & tx;

			template<typename T>
			void operator()(T & value) const {
				uint8_t buf[sizeof(T)];
				std::memcpy(&(buf[0]), &value, sizeof(T));
				tx.output(buf, sizeof(T));
			}

			void operator()(uint8_t data) const {
				tx.output(data);
			}
		};
	} // end of namespace detail

	template<typename TransmissionType, typename TransmitterDerived, typename MessageContentsType>
	void send(TransmitterBase<TransmitterDerived> & tx, MessageContentsType const & contents) {
		typedef MessageContentsType message_contents_type;
		typedef typename TransmissionType::message_type message_type;
		BOOST_MPL_ASSERT((boost::mpl::equal<message_type, message_contents_type>));

		typedef typename TransmitterBase<TransmitterDerived>::base transmitter_type;
		typedef typename TransmissionType::envelope_type::base envelope_type;
		typedef typename TransmissionType::message_id message_id;
		envelope_type::sendMessage(tx, contents, static_cast<MessageIdType>(message_id()));

	}
}// end of namespace transmission

#endif // INCLUDED_SendMessage_h_GUID_9cbfc065_ea71_4097_8993_c4e0b0fb14c5
