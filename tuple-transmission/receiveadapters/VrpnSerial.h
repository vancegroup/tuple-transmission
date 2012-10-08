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
#ifndef INCLUDED_VrpnSerial_h_GUID_99c80318_810b_4b76_a6ee_abeb7c444fbd
#define INCLUDED_VrpnSerial_h_GUID_99c80318_810b_4b76_a6ee_abeb7c444fbd

// Internal Includes
#include "../detail/types/IntegralTypes.h"
#include "../detail/bases/ReceiveAdapterBase.h"

// Library/third-party includes
// - none

// Standard includes
// - none


namespace transmission {

	class VrpnSerialReceiveAdapter : public detail::ReceiveAdapterWithoutAvailable<VrpnSerialReceiveAdapter> {
		public:
			VrpnSerialReceiveAdapter(vrpn_SerialPort & source) : s(source) {}

			template<typename BufferIteratorType>
			uint8_t receiveIntoBuffer(BufferIteratorType it, uint8_t count) {
				return s.readBytes(it, count);
			}
		private:
			vrpn_SerialPort & s;

	};

} // end of namespace transmission

#endif // INCLUDED_VrpnSerial_h_GUID_99c80318_810b_4b76_a6ee_abeb7c444fbd
