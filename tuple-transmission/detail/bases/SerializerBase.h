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
#ifndef INCLUDED_SerializerBase_h_GUID_c34cd60a_eb2c_4fa4_b774_bfb021305cec
#define INCLUDED_SerializerBase_h_GUID_c34cd60a_eb2c_4fa4_b774_bfb021305cec

// Internal Includes
#include "../types/IntegralTypes.h"

// Library/third-party includes
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/config.hpp> // for std::size_t

// Standard includes
// - none

namespace transmission {
	namespace detail {

		/// @brief Base class for a serializer with stateless, static buffer() method(s)
		class StatelessSerializer_tag {};

		/// @brief Base class for a serializer that needs member
		/// variables, with buffer() member method(s)
		class StatefulSerializer_tag {};

		/// @brief Wrapper for serializer implementations to handle management
		/// of the transmitter reference.
		///
		/// This template specializes on whether or not the serializer
		/// must maintain state, based on inheritance from either
		/// StatelessSerializer_tag or StatefulSerializer_tag
		template<typename ImplementationType, typename = void>
		class SendContextWrapper;

		/// @brief Template specialization for stateless serializers
		template<typename ImplementationType>
		class SendContextWrapper<ImplementationType, typename boost::enable_if<typename boost::is_base_of<StatelessSerializer_tag, ImplementationType>::type >::type > {
				template<typename TransmitterType>
				class SendContext {
					public:
						SendContext(TransmitterType & transmit) : tx(transmit) {}
						template<typename T>
						void operator()(T & value) const {
							ImplementationType::buffer(tx, value);
						}
						void operator()(uint8_t value) const {
							ImplementationType::buffer(tx, value);
						}
					private:
						TransmitterType & tx;
				};
		};

		/// @brief Template specialization for stateful serializers
		template<typename ImplementationType>
		class SendContextWrapper<ImplementationType, typename boost::enable_if<typename boost::is_base_of<StatefulSerializer_tag, ImplementationType>::type >::type > {
				template<typename TransmitterType>
				class SendContext {
					public:
						SendContext(TransmitterType & transmit) : tx(transmit), impl() {}
						template<typename T>
						void operator()(T & value) const {
							impl.buffer(tx, value);
						}
						void operator()(uint8_t value) const {
							impl.buffer(tx, value);
						}
					private:
						TransmitterType & tx;
						ImplementationType impl;
				};
		};

	}

} // end of namespace transmission

#endif // INCLUDED_SerializerBase_h_GUID_c34cd60a_eb2c_4fa4_b774_bfb021305cec
