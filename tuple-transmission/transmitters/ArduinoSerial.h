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
#ifndef INCLUDED_ArduinoSerialTransmitter_h_GUID_83d9f433_13ac_4b1d_88b1_8ef673dfd648
#define INCLUDED_ArduinoSerialTransmitter_h_GUID_83d9f433_13ac_4b1d_88b1_8ef673dfd648

// Internal Includes
#include "../detail/bases/TransmitterBase.h"

// Library/third-party includes
// - none

// Standard includes
// - none

#ifdef ARDUINO
namespace transmission {
	namespace transmitters {
		/// @addtogroup Transmitters Transmitter Classes
		class ArduinoSerial : public TransmitterBase<ArduinoSerial> {
			public:
				ArduinoSerial(Print & stream) : s(stream) {}

				void writeByte(uint8_t v) {
					s.write(v);
				}

				void write(uint8_t * data, std::size_t len) {
					s.write(data, len);
				}

			private:
				Stream & s;
		};
		/// @}
	} // end of namespace transmitters
} // end of namespace transmission

#endif

#endif // INCLUDED_ArduinoSerialTransmitter_h_GUID_83d9f433_13ac_4b1d_88b1_8ef673dfd648
