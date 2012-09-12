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
#ifndef INCLUDED_Receive_h_GUID_9e1418a4_6874_426b_9113_cc5e57ee3fb5
#define INCLUDED_Receive_h_GUID_9e1418a4_6874_426b_9113_cc5e57ee3fb5

// Internal Includes
#include "ReceiveHandler.h"

// Library/third-party includes
// - none

// Standard includes
// - none

namespace transmission {
	template<typename Derived, typename MessageCollection>
	class Receive {
		private:
			typedef ReceiveHandler<MessageCollection> receive_handler_type;
		public:
			typedef typename receive_handler_type::buffer_size_type buffer_size_type;

			buffer_size_type getBufferAvailableSpace() const {
				return _recv.bufferAvailableSpace();
			}

			template<typename InputIterator>
			void appendReceived(InputIterator input_begin, InputIterator input_end) {
				_recv.append(input_begin, input_end);
				if (_recv.checkBufferForMessage()) {

				}
			}

		private:
			receive_handler_type _recv;
			Derived & getDerived() {
				return *(static_cast<Derived*>(this));
			}
			Derived const & getDerived() const {
				return *(static_cast<Derived const *>(this));
			}
	};
} // end of namespace transmission

#endif // INCLUDED_Receive_h_GUID_9e1418a4_6874_426b_9113_cc5e57ee3fb5
