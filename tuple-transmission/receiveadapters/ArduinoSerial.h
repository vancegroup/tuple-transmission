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
#ifndef INCLUDED_ArduinoSerial_h_GUID_2c1ad135_82b0_4de2_a5a4_1aff33bc1558
#define INCLUDED_ArduinoSerial_h_GUID_2c1ad135_82b0_4de2_a5a4_1aff33bc1558

// Internal Includes
#include "../detail/types/IntegralTypes.h"
#include "../detail/bases/ReceiveAdapterBase.h"

// Library/third-party includes
// - none

// Standard includes
#include <cmath>
#include <limits>

#ifdef ARDUINO

namespace transmission {

	class ArduinoSerialReceiveAdapter : public detail::ReceiveAdapter<ArduinoSerialReceiveAdapter> {
		public:
			ArduinoSerialReceiveAdapter(Stream & source) : s(source) {}

			uint8_t getNumAvailable() {
				return static_cast<uint8_t>(std::min<int>(std::numeric_limits<uint8_t>::max(), s.available()));
			}

			template<typename BufferIteratorType>
			uint8_t receiveIntoBuffer(BufferIteratorType it, uint8_t count) {
				return s.readBytes(it, count);
			}
		private:
			Stream & s;

	};

} // end of namespace transmission

#endif

#endif // INCLUDED_ArduinoSerial_h_GUID_2c1ad135_82b0_4de2_a5a4_1aff33bc1558
