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
#ifndef INCLUDED_BitwiseCopySerialization_h_GUID_4d50bc7f_c702_437a_a2df_f715f1cea845
#define INCLUDED_BitwiseCopySerialization_h_GUID_4d50bc7f_c702_437a_a2df_f715f1cea845

// Internal Includes
#include "../detail/bases/SerializerBase.h"

// Library/third-party includes
// - none

// Standard includes
#include <cstring> // for memcpy

namespace transmission {
	namespace serializers {
		struct BitwiseCopySerializer : detail::StatelessSerializer_tag {
			template<typename TransmitterType, typename T>
			void buffer(TransmitterType & tx, T & value) {
				uint8_t buf[sizeof(T)];
				std::memcpy(&(buf[0]), &value, sizeof(T));
				tx.output(buf, sizeof(T));
			}

			template<typename TransmitterType>
			static void buffer(TransmitterType & tx, uint8_t data) {
				tx.output(data);
			}
		};

		struct BitwiseCopyDeserializer {
			template<typename T>
			struct Unbuffer {
				template<typename IteratorType>
				T apply(IteratorType & it) {
					T ret;
					std::memcpy(it, &ret, sizeof(T));
					it += sizeof(T);
					return ret;
				}
			};
		};


		template<>
		struct BitwiseCopyDeserializer::Unbuffer<uint8_t> {
			template<typename IteratorType>
			uint8_t apply(IteratorType & it) {
				return *(it++);
			}
		};

		//typedef detail::SendContextWrapper<BitwiseCopy> BitwiseCopySendContext;

		typedef detail::SerializationPolicy<BitwiseCopySerializer, BitwiseCopyDeserializer> BitwiseCopy;
	} // end of namespace serializers
} // end of namespace transmission
#endif // INCLUDED_BitwiseCopySerialization_h_GUID_4d50bc7f_c702_437a_a2df_f715f1cea845
