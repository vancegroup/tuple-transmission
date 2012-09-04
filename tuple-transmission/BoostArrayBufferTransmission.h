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
#ifndef INCLUDED_BoostArrayBufferTransmission_h_GUID_e7fb6660_2fbf_489d_9fbd_b4b77089b401
#define INCLUDED_BoostArrayBufferTransmission_h_GUID_e7fb6660_2fbf_489d_9fbd_b4b77089b401

// Internal Includes
#include "TransmissionBase.h"
#include <util/booststdint.h>

// Library/third-party includes
#include <boost/array.hpp>

// Standard includes
// - none


namespace transmission {
	template<size_t SIZE>
	class BoostArrayBuffer : public TransmissionBase<BoostArrayBuffer> {
		public:
			BoostArrayBuffer() : insert_idx(0) {}

			void write(stdint::uint8_t v) {
				buffer.at(insert_idx) = v;
				insert_idx++;
			}

			void write(stdint::uint8_t * data, size_t len) {
				assert(SIZE >= insert_idx + len);
				std::memcpy(&(buffer.at(insert_idx)), data, len);
				insert_idx += len;
			}

			typedef boost::array<stdint::uint8_t, SIZE> BufferType;
			BufferType buffer;

		private:
			size_t insert_idx;


	};
}

#endif // INCLUDED_BoostArrayBufferTransmission_h_GUID_e7fb6660_2fbf_489d_9fbd_b4b77089b401
