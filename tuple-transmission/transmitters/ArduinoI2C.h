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
#ifndef INCLUDED_ArduinoI2CTransmitter_h_GUID_a948b207_8b92_41e2_ac13_9020d01dc412
#define INCLUDED_ArduinoI2CTransmitter_h_GUID_a948b207_8b92_41e2_ac13_9020d01dc412

// Internal Includes
#include "../detail/bases/TransmitterBase.h"
#include "BoostArrayBuffer.h"

// Library/third-party includes
// - none

// Standard includes
// - none

#ifdef ARDUINO
namespace transmission {
	namespace transmitters {
		/// @addtogroup Transmitters Transmitter Classes

		/// @brief Arduino I2C transmitter - internally buffers because
		/// some uses of the I2C library in Arduino allow only a single
		/// write.
		class ArduinoI2C : public TransmitterBase<ArduinoI2C> {
			public:
				ArduinoSerial(TwoWire & stream) : s(stream) {}

				static const uint8_t BUFSIZE = 255;

				void writeByte(uint8_t v) {
					bufTx.output(v);
				}

				void write(uint8_t * data, std::size_t len) {
					bufTx.output(data, len);
				}

				void writeFinished() {
					s.write(bufTx.begin(), bufTx.end() - bufTx.begin());
					bufTx.reset();
				}

			private:
				BoostArrayBuffer<BUFSIZE> bufTx;
				TwoWire & s;
		};
		/// @}
	} // end of namespace transmitters
} // end of namespace transmission

#endif

#endif // INCLUDED_ArduinoI2CTransmitter_h_GUID_a948b207_8b92_41e2_ac13_9020d01dc412
