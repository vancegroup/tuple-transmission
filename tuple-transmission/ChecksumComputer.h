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
#ifndef INCLUDED_ChecksumComputer_h_GUID_80d37814_ff4e_4f0d_af5e_5829daff7df6
#define INCLUDED_ChecksumComputer_h_GUID_80d37814_ff4e_4f0d_af5e_5829daff7df6

// Internal Includes
#include "TransmitterBase.h"
#include "IntegralTypes.h"

// Library/third-party includes
// - none

// Standard includes
// - none

namespace transmission {
	class ChecksumComputer : public TransmitterBase<ChecksumComputer> {
		public:
			ChecksumComputer() : _ck(0) {
				_ck = 0;
			}
			void write(uint8_t v) {
				_ck += v;
			}
			uint8_t checksum() const {
				return _ck;
			}
		private:
			uint8_t  _ck;
	};
} // end of namespace transmission
#endif // INCLUDED_ChecksumComputer_h_GUID_80d37814_ff4e_4f0d_af5e_5829daff7df6