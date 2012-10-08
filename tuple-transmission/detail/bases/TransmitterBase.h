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
#ifndef INCLUDED_TransmitterBase_h_GUID_16d34310_de5f_41ae_b669_8c88adb4b1e0
#define INCLUDED_TransmitterBase_h_GUID_16d34310_de5f_41ae_b669_8c88adb4b1e0

// Internal Includes
#include "TransmitterBase_fwd.h"
#include "../types/IntegralTypes.h"

// Library/third-party includes
#include <boost/config.hpp> // for std::size_t

// Standard includes
// - none


namespace transmission {
	namespace transmitters {
		template<typename Derived>
		class TransmitterBase {
			public:
				typedef TransmitterBase<Derived> base;
				typedef Derived derived;
				/// @name External Interface
				/// @brief Output methods called by envelopes, or anyone else
				/// wanting to actually use a transmitter.
				///
				/// Do NOT define these in your own transmitter class.
				/// @{

				/// @brief Output a single byte.
				void output(uint8_t data) {
					impl().writeByte(data);
				}

				/// @brief Output multiple bytes.
				void output(uint8_t * data, std::size_t const len) {
					impl().write(data, len);
				}

				/// @brief Indicate the completion of a unit of transmission -
				/// for transmitters that perform internal buffering.
				void outputFinished() {
					impl().writeFinished();
				}

				/// @}

				/// @name Transmitter implementation methods
				/// @brief Defined by implementation classes, and used only internally.
				/// @{
				/// @brief Fallback multi-byte data method writing a byte at a time.
				///
				/// If you can do something more efficient, feel free to re-implement.
				void write(uint8_t * data, std::size_t const len) {
					for (std::size_t i = 0; i < len; ++i) {
						impl().writeByte(data[i]);
					}
				}

				/// @brief fallback if your transmitter doesn't care about outputFinished.
				void writeFinished() {
				}

				/// @brief Method you must define and override in your type: it all
				/// is for naught unless you do so. This is the single-byte implementation.
				void writeByte(uint8_t data);
				/// @}
			private:
				/// @brief Internal method to access a reference to the derived class
				Derived & impl() {
					return *static_cast<Derived *>(this);
				}

				/// @brief Internal method to access a const reference to the derived class
				Derived const & impl() const {
					return *static_cast<Derived const *>(this);
				}
		};
	} // end of namespace transmitters
} // end of namespace transmission

#endif // INCLUDED_TransmitterBase_h_GUID_16d34310_de5f_41ae_b669_8c88adb4b1e0
