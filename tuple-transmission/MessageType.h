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
#ifndef INCLUDED_MessageType_h_GUID_eef26e08_32f9_4c37_9c5b_058b281c319a
#define INCLUDED_MessageType_h_GUID_eef26e08_32f9_4c37_9c5b_058b281c319a

// Internal Includes
// - none

// Library/third-party includes
// - none

// Standard includes
// - none


namespace transmission {
	/// @addtogroup ProtocolDefs Protocol Definition Types
	/// @{

	/** @brief Base class for your message types: pass an MPL vector of field types.

		To define a distinct message type, define an (empty) struct inheriting
		from this template with your desired field types in your protocol header.
		For example,

		struct MessageA : MessageTypeBase<mpl::vector<uint8_t, uint8_t, int16_t> > {};

		Such messages can be named in 0 or more MessageCollection types, which
		takes care of uniquely identifying them (by their position in the list
		of message types for that collection).

		@sa MessageCollection
	*/
	template<typename MPLVector>
	struct MessageTypeBase : MPLVector {
		typedef MPLVector base;
		typedef void message_type_tag;
	};

	/// @}
} // end of namespace transmission


#endif // INCLUDED_MessageType_h_GUID_eef26e08_32f9_4c37_9c5b_058b281c319a
