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
#include <iterator>

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
				VectorBuffer() : buffer(max_size()), _it(buffer.begin()) {}

				void writeByte(uint8_t v) {
					*_it = v;
					_it++;
				}

				void write(uint8_t * data, std::size_t len) {
					_it = std::copy(data, data + len, _it);
				}

				typedef std::vector<uint8_t> BufferType;

				typedef typename BufferType::value_type value_type;
				typedef typename BufferType::iterator iterator;
				typedef typename BufferType::const_iterator const_iterator;
				typedef typename BufferType::size_type size_type;

				iterator begin() {
					return buffer.begin();
				}
				const_iterator begin() const {
					return buffer.begin();
				}
				iterator end() {
					return _it;
				}

				const_iterator end() const {
					return _it;
				}

				size_type size() const {
					return _it - begin();
				}

				bool empty() const {
					return begin() == _it;
				}

			private:
				BufferType buffer;
				iterator _it;
		};

		/// @}
	} // end of namespace transmitters
} // end of namespace transmission
#endif // INCLUDED_VectorBuffer_h_GUID_57f1692b_dc67_4c88_894c_0ef3b8b91423
