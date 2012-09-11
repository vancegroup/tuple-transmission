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
#ifndef INCLUDED_EnvelopeBase_h_GUID_aa476fba_c58f_42aa_b6bf_f5937201105b
#define INCLUDED_EnvelopeBase_h_GUID_aa476fba_c58f_42aa_b6bf_f5937201105b

// Internal Includes
#include "EnvelopeBase_fwd.h"
#include "../types/IntegralTypes.h"
#include <util/BoostAssertMsg.h>

// Library/third-party includes
// - none

// Standard includes
// - none

#ifndef BOOST_TEST_MESSAGE
#define BOOST_TEST_MESSAGE(X)
#endif

namespace transmission {
	namespace detail {
		template<typename TransmitterType>
		struct SendContext;
	} // end of namespace detail

	namespace envelopes {
		/// @brief Template base for envelopes: used to enforce requirements
		/// on envelope interfaces and provide for compile-time polymorphism.
		template<typename Derived, typename SerializationPolicy>
		struct EnvelopeBase {
			typedef EnvelopeBase<Derived, SerializationPolicy> base;
			typedef Derived derived;

			typedef SerializationPolicy serialization_policy;

			template<typename MessageSize>
			struct Size : derived::template Size<MessageSize> {};

			template<typename TransmitterType, typename Tuple>
			static void bufferTuple(TransmitterType & tx, Tuple const & contents) {
				typedef typename derived::serialization_policy policy;
				policy::bufferTuple(tx, contents);
			}

			template<typename T, typename Iterator>
			static T unbuffer(Iterator & it) {
				typedef typename derived::serialization_policy policy;
				policy::template unbuffer<T>(it);
			}

			template<typename TransmitterType, typename MessageContentsType>
			static void sendMessage(TransmitterType & tx, MessageContentsType const & contents, MessageIdType msgId) {
				derived::sendMessage(tx, contents, msgId);
			}

			template<typename ReceiveHandlerType>
			static bool checkBufferForMessage(ReceiveHandlerType & recv) {
				BOOST_TEST_MESSAGE("Envelope checking buffer " << &recv << " for message.");
				return derived::checkBufferForMessage(recv);
			}

			template<typename ReceiveHandlerType>
			static bool popAndRetry(ReceiveHandlerType & recv) {
				BOOST_TEST_MESSAGE("Envelope popAndRetry.");
				BOOST_ASSERT_MSG(!recv.bufferEmpty(), "Error in envelope code: asking to pop and retry when buffer is empty");
				if (recv.bufferEmpty()) {
					return false;
				}
				recv.bufferPopFront();
				return checkBufferForMessage(recv);
			}
		};

	} //end of namespace envelopes

}// end of namespace transmission
#endif // INCLUDED_EnvelopeBase_h_GUID_aa476fba_c58f_42aa_b6bf_f5937201105b
