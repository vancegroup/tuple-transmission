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
#ifndef INCLUDED_TransmitterComposition_h_GUID_d334eef0_f213_482b_b615_913f37df35bf
#define INCLUDED_TransmitterComposition_h_GUID_d334eef0_f213_482b_b615_913f37df35bf

// Internal Includes
#include "TransmitterBase.h"

// Library/third-party includes
// - none

// Standard includes
// - none


namespace transmission {
	/// @addtogroup Transmitters Transmitter Classes
	/// @brief These classes serve as the "output sink" when sending messages.
	///
	/// Some may actually be transmitters (serial ports, network sockets, etc)
	/// while others are more of simulated transmitters (buffers, checksum computers, etc.)
	///
	/// All inherit, using the Curiously-Recurring-Template-Pattern, from TransmitterBase.
	/// @{


	/// @brief A "transmitter" that combines two other transmitters.
	///
	/// For instance, you might use a buffer and a checksum computer.
	template<typename First, typename Second>
	class TransmitterComposition : public TransmitterBase< TransmitterComposition<First, Second> > {
		public:
			typedef TransmitterComposition<First, Second> type;
			typedef typename First::base first_type;
			typedef typename Second::base second_type;


			TransmitterComposition(first_type & tx1, second_type & tx2) : _tx1(tx1), _tx2(tx2) {}

			/// @brief Multi-byte filter method
			void write(uint8_t data[], std::size_t len) {
				_tx1.output(data, len);
				_tx2.output(data, len);
			}

			/// @brief Single byte filter method
			void write(uint8_t data) {
				_tx1.output(data);
				_tx2.output(data);
			}
		private:
			first_type & _tx1;
			second_type & _tx2;
	};
	/// @}
} // end of namespace transmission

#endif // INCLUDED_TransmitterComposition_h_GUID_d334eef0_f213_482b_b615_913f37df35bf
