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
#ifndef INCLUDED_ArduinoSerialReceiveHelper_h_GUID_c7d111da_699f_4aa9_b3a7_a962b5411c9a
#define INCLUDED_ArduinoSerialReceiveHelper_h_GUID_c7d111da_699f_4aa9_b3a7_a962b5411c9a

// Internal Includes
#include "../detail/types/IntegralTypes.h"

// Library/third-party includes
//#include <boost/utility/enable_if.hpp>
//#include <boost/type_traits/is_base_of.hpp>
#include <Stream.h>

// Standard includes
// - none


namespace transmission {
#if 0 
	template<typename T>
	struct isArduinoStreamWithAvailable : boost::false_type {};
	
	#define ARDUINO_STREAM_WITH_AVAILABLE(X) \
	class X; \
	template<> struct isArduinoStreamWithAvailable<X> : boost::true_type {};
	
	ARDUINO_STREAM_WITH_AVAILABLE(HardwareSerial)
	ARDUINO_STREAM_WITH_AVAILABLE(UDP)
	
	// library SD
	ARDUINO_STREAM_WITH_AVAILABLE(File)
	
	// library SoftwareSerial
	ARDUINO_STREAM_WITH_AVAILABLE(SoftwareSerial)
	
	// library Wire
	ARDUINO_STREAM_WITH_AVAILABLE(TwoWire)
	
	#undef ARDUINO_STREAM_WITH_AVAILABLE
	
	template<typename SourceType, typename ReceiverType>
	typename boost::enable_if<isArduinoStreamWithAvailable<SourceType>, uint8_t>::type
	receiveFrom(SourceType & s, ReceiverType & r) {
		return r.appendUsing(detail::ArduinoReceiveFunctor<SourceType>(s), s.available());
	}
	
#endif

	namespace detail {
		struct ArduinoReceiveFunctor {
			ArduinoReceiveFunctor(Stream & source) : s(source) {}
			uint8_t operator()() {
				uint8_t ret;
				s.readBytes(&ret, 1);
				return ret;
			}

			template<typename BufferIteratorType, typename BufferSizeType>
			BufferSizeType operator()(BufferIteratorType buf, BufferSizeType count) {
				return s.readBytes(buf, count);
			}

			Stream & s;
		};
	}

	template<typename ReceiverType>
	uint8_t receiveFrom(Stream & s, ReceiverType & r) {
		return r.appendUsing(detail::ArduinoReceiveFunctor(s), s.available());
	}


} // end of namespace transmission

#endif // INCLUDED_ArduinoSerialReceiveHelper_h_GUID_c7d111da_699f_4aa9_b3a7_a962b5411c9a
