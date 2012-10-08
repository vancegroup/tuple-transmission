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
#ifndef INCLUDED_ReceiveAdapterBase_h_GUID_34fbc703_624a_4041_b94f_b4edd021263f
#define INCLUDED_ReceiveAdapterBase_h_GUID_34fbc703_624a_4041_b94f_b4edd021263f

// Internal Includes
#include "../types/IntegralTypes.h"

// Library/third-party includes
// - none

// Standard includes
#include <limits>

namespace transmission {
	namespace detail {
		/// @brief CRTP base for Receive Adapters.
		///
		/// Receive adapters must include:
		/// - A method called getNumAvailable (if this data isn't available,
		///    derive from ReceiveAdapterWithoutAvailable instead)
		/// - A method called receiveIntoBuffer that takes an iterator and uint8_t
		///    bytes, and buffers no more than that starting at the iterator,\
		///    returning the total number of bytes buffered.
		template<typename Derived>
		class ReceiveAdapterBase {
			public:
				/// @brief Returns the number of available bytes.
				///
				/// Implementation that forwards on to derived class if
				/// it actually can report the number of available bytes.
				uint8_t getNumAvailable() {
					return getDerived().getNumAvailable();
				}

				/// @brief Function call operator for buffering, that forwards
				/// to derived class's receiveIntoBuffer method.
				template<typename IteratorType>
				uint8_t operator()(IteratorType it, uint8_t maxBytes) {
					return getDerived().receiveIntoBuffer(it, maxBytes);
				}
			private:
				Derived & getDerived() {
					return *static_cast<Derived *>(this);
				}

				Derived const & getDerived() const {
					return *static_cast<Derived const *>(this);
				}
		};

		template<typename Derived>
		class ReceiveAdapterWithoutAvailable : public ReceiveAdapterBase<Derived> {
			public:
				uint8_t getNumAvailable() {
					return std::numeric_limits<uint8_t>::max();
				}
		};
	} //end of namespace detail
} // end of namespace transmission

#endif // INCLUDED_ReceiveAdapterBase_h_GUID_34fbc703_624a_4041_b94f_b4edd021263f
