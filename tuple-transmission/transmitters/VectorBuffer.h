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
#ifndef INCLUDED_VectorBuffer_h_GUID_57f1692b_dc67_4c88_894c_0ef3b8b91423
#define INCLUDED_VectorBuffer_h_GUID_57f1692b_dc67_4c88_894c_0ef3b8b91423

// Internal Includes
#include "../detail/bases/TransmitterBase.h"
#include "../detail/operations/MaxMessageLength.h"

// Library/third-party includes
// - none

// Standard includes
#include <vector>

namespace transmission {
	namespace transmitters {
		/// @addtogroup Transmitters Transmitter Classes
		/// @{

		/// @brief A "Transmitter" that collects the bytes to transmit in a std::vector
		/// that reserves enough space for the max message length.
		template<typename Collection>
		class VectorBuffer : public TransmitterBase<VectorBuffer<Collection> > {
			public:
				typedef detail::operations::MaxMessageLength<Collection> max_size;
				VectorBuffer() : buffer(max_size()) {}

				void write(uint8_t v) {
					buffer.push_back(v);
				}

				void write(uint8_t * data, std::size_t len) {
					std::copy(data, data + len, buffer.end());
				}

				typedef std::vector<uint8_t> BufferType;

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
		};

		/// @}
	} // end of namespace transmitters
} // end of namespace transmission
#endif // INCLUDED_VectorBuffer_h_GUID_57f1692b_dc67_4c88_894c_0ef3b8b91423
