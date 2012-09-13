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
#include "../detail/bases/TransmitterBase.h"

// Library/third-party includes
#include <boost/array.hpp>
#include <boost/mpl/int.hpp>

// Standard includes
#include <algorithm>


namespace transmission {
	namespace transmitters {
		/// @addtogroup Transmitters Transmitter Classes
		/// @{

		/// @brief A "Transmitter" that collects the bytes to transmit in a boost::array.
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

				typedef typename BufferType::value_type value_type;
				typedef typename BufferType::iterator iterator;
				typedef typename BufferType::const_iterator const_iterator;

				iterator begin() {
					return buffer.begin();
				}
				const_iterator begin() const {
					return buffer.begin();
				}
				iterator end() {
					return buffer.end();
				}
				const_iterator end() const {
					return buffer.end();
				}

				BufferType buffer;

			private:
				typename BufferType::iterator it;

		};

		/// @}
	} // end of namespace transmitters
} // end of namespace transmission

#endif // INCLUDED_BoostArrayBuffer_h_GUID_e7fb6660_2fbf_489d_9fbd_b4b77089b401
