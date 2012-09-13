local generateHelper = function(arity, MessageCollectionType, MessageType, message_sequence_type)
	-- SFINAE return type
	out(("inline typename enable_if< mpl::equal<mpl::int_<%d>, MessageArity<%s> >, void>::type"):format(arity, MessageType))

	-- Compute the argument list our function will take
	local arguments = {"transmitters::TransmitterBase<TransmitterDerived> & tx"}
	for i = 1, arity do
		table.insert(arguments, ("typename mpl::at_c<%s, %d>::type a%d"):format(message_sequence_type, i - 1, i))
	end

	out(("send(%s) {\n"):format(cat(arguments, ",\n" .. indent(0, 0) .. "     ")))

	out(1, ("::transmission::send<%s, %s>("):format(MessageCollectionType, MessageType))
	out(1, 1, "tx,")
	out(1, 1, "fusion::make_list(" .. genRange(arity, function(i) return ("a%d"):format(i) end) .. ")")
	out(1, ");")
	out("}\n")
end

return {
	outFile = "detail/operations/SendOverloads_Generated.h";
	baseIndent = 4;
	minArity = SendOverloadMinArity;
	maxArity = SendOverloadMaxArity;
	generate = function(arity)
		-- Version with two explicit template parameters
		out( "/// @brief Overload of transmission::send() taking a message collection and a message type as explicit")
		out(("/// template parameters, and taking a transmitter, plus values for %d message fields directly"):format(arity))
		out( "/// instead of a boost::fusion sequence containing the field values.")
		out( "template<typename MessageCollectionType, typename MessageType, typename TransmitterDerived>")
		generateHelper(arity,
			"MessageCollectionType",
			"MessageType",
			"typename MessageType::sequence_type")

		-- Version with just one explicit template parameter
		out( "/// @brief Overload of transmission::send() taking a BoundMessageType as the only explicit")
		out(("/// template parameter, and taking a transmitter, plus values for %d message fields directly"):format(arity))
		out( "/// instead of a boost::fusion sequence containing the field values.")
		out( "template<typename BoundMessage, typename TransmitterDerived>")
		generateHelper(arity,
			"typename BoundMessage::message_collection",
			"typename BoundMessage::message_type",
			"typename BoundMessage::message_type::sequence_type")
	end;

	prefix = [[
/** @file
	@brief Header AUTO-GENERATED by %s to avoid doing crazy preprocessor things

	DO NOT EDIT THIS FILE DIRECTLY - instead, edit the script that generates it.

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
#ifndef INCLUDED_SendOverloads_Generated_h_GUID_ceb4f589_526e_49d7_84c5_0b38f6d1fc42
#define INCLUDED_SendOverloads_Generated_h_GUID_ceb4f589_526e_49d7_84c5_0b38f6d1fc42

// Internal Includes
#include "../constants/ArityConfig.h"
#include "MessageArity.h"
#include "../bases/TransmitterBase_fwd.h"

// Library/third-party includes
#include <boost/fusion/include/make_list.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/utility/enable_if.hpp>

// Standard includes
// - none

namespace transmission {
	// Forward-declare the main send function that we'll invoke after making a fusion sequence
	template<typename Collection, typename Message, typename TransmitterDerived, typename MessageContentsType>
	void send(transmitters::TransmitterBase<TransmitterDerived> & tx, MessageContentsType const & contents);

	namespace detail {
		namespace operations {
			namespace generated {
				namespace mpl = boost::mpl;
				namespace fusion = boost::fusion;
				using boost::enable_if;
				typedef mpl::int_<]] .. tostring(SendOverloadMaxArity) .. [[> SendOverloadMaxArity;

]];

	suffix = [[
			} // end of namespace generated
		} // end of namespace operations
	} // end of namespace detail

	using detail::operations::generated::send;
} // end of namespace transmission
#endif // INCLUDED_SendOverloads_Generated_h_GUID_ceb4f589_526e_49d7_84c5_0b38f6d1fc42
]];
}
