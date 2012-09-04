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
#ifndef INCLUDED_ControlCodes_h_GUID_8f8bf468_f143_47fb_be26_883227af00e3
#define INCLUDED_ControlCodes_h_GUID_8f8bf468_f143_47fb_be26_883227af00e3

// Internal Includes
// - none

// Library/third-party includes
#include <util/booststdint.h>

// Standard includes
// none

namespace transmission {
	namespace detail {
		namespace ControlCodes {
			using namespace stdint;
			/// @brief Start of Header
			static const uint8_t SOH = 0x01;
			/// @brief Start of Text
			static const uint8_t STX = 0x02;

			/// @brief End of Text
			static const uint8_t ETX = 0x03;
			/// @brief End of Transmission
			static const uint8_t EOT = 0x04;


			/// @brief Acknowledge
			static const uint8_t ACK = 0x06;
			/// @brief Negative Acknowledge
			static const uint8_t NAK = 0x15;
		} // end of namespace ControlCodes
	} // end of namespace detail
} // end of namespace transmission


#endif // INCLUDED_ControlCodes_h_GUID_8f8bf468_f143_47fb_be26_883227af00e3
