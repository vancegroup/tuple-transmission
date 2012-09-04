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
#include "MessageIdType.h"
#include "TransmissionBase_fwd.h"

// Library/third-party includes
// - none

// Standard includes
// - none


namespace transmission {
	namespace envelopes {
		/// @brief Template base for envelopes: used to enforce requirements
		/// on envelope interfaces and provide for compile-time polymorphism.
		template<typename Derived>
		struct EnvelopeBase {
			typedef EnvelopeBase<Derived> base;
			typedef Derived derived;

			template<int MessageSize>
			struct Size {
				typedef typename derived::template Size<MessageSize> derived_result_type;
				enum {
					value = (derived_result_type::value)
				};
			};

			template<typename TXDerived, typename MessageContentsType>
			static void sendMessage(TransmissionBase<TXDerived> & xt, MessageContentsType const & contents, MessageIdType msgId) {
				derived::sendMessage(xt, contents, msgId);
			}
		};

		template<typename Envelope>
		struct GetEnvelopeBase : Envelope::base {};
	} //end of namespace envelopes

}// end of namespace transmission
#endif // INCLUDED_EnvelopeBase_h_GUID_aa476fba_c58f_42aa_b6bf_f5937201105b
