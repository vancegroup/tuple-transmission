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
#ifndef INCLUDED_TransmissionBase_h_GUID_16d34310_de5f_41ae_b669_8c88adb4b1e0
#define INCLUDED_TransmissionBase_h_GUID_16d34310_de5f_41ae_b669_8c88adb4b1e0

// Internal Includes
#include <util/booststdint.h>

// Library/third-party includes
// - none

// Standard includes
// - none


namespace transmission {
	template<typename Derived>
	class TransmissionBase {
		public:
			/// @name External Interface
			/// @brief Output methods called by envelopes.
			/// @{
			void output(stdint::uint8_t data) {
				impl().write(data);
			}

			void output(stdint::uint8_t data[], size_t len) {
				impl().write(data, len);
			}

			/// @}

			/// @brief Fallback multi-byte data method writing a byte at a time.
			///
			/// If you can do something more efficient, feel free to re-implement.
			void write(stdint::uint8_t data[], size_t len) {
				for (size_t i = 0; i < len; ++len) {
					impl().write(data[i]);
				}
			}

			/// @brief Method you must override in your transmission type
			void write(stdint::uint8_t data);
		private:
			Derived & impl() {
				return *static_cast<Derived *>(this);
			}

			Derived const & impl() const {
				return *static_cast<Derived const *>(this);
			}
	};

} // end of namespace transmission

#endif // INCLUDED_TransmissionBase_h_GUID_16d34310_de5f_41ae_b669_8c88adb4b1e0
