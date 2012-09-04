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
#ifndef INCLUDED_BoostArrayBuffer_h_GUID_e7fb6660_2fbf_489d_9fbd_b4b77089b401
#define INCLUDED_BoostArrayBuffer_h_GUID_e7fb6660_2fbf_489d_9fbd_b4b77089b401

// Internal Includes
#include "TransmitterBase.h"
#include "Sizeof.h"

// Library/third-party includes
#include <boost/array.hpp>
#include <boost/mpl/int.hpp>

// Standard includes
#include <algorithm>


namespace transmission {
	template<int SIZE>
	class BoostArrayBuffer : public TransmitterBase<BoostArrayBuffer<SIZE> > {
		public:
			BoostArrayBuffer() : buffer(), it(buffer.begin()) {}

			void write(uint8_t v) {
				*it = v;
				++it;
			}

			void write(uint8_t * data, std::size_t len) {
				it = std::copy(data, data + len, it);
			}

			typedef boost::mpl::int_<SIZE> size;
			typedef boost::array<uint8_t, SIZE> BufferType;
			BufferType buffer;

		private:
			typename BufferType::iterator it;

	};

	template<typename TransmissionType>
	class BoostArrayBufferAutosized : public BoostArrayBuffer< Sizeof<TransmissionType>::value > {};
}

#endif // INCLUDED_BoostArrayBuffer_h_GUID_e7fb6660_2fbf_489d_9fbd_b4b77089b401
