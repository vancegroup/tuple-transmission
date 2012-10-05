return {
	outFile = "detail/operations/DeserializeOverloads_Generated.h";
	baseIndent = 4;
	minArity = ReceiveMinArity;
	maxArity = ReceiveMaxArity;
	generate = function(arity)
		-- Start our function template declaration/inline definition
		out( "template<typename MessageType, typename Policy, typename Function, typename Iterator>")
		out( "inline void")

		-- Avoid unused argument warning for 0-arity messages
		local iteratorName = "it"
		if arity == 0 then iteratorName = "" end

		-- Write function name and parameters, including a SFINAE dummy
		-- that checks message arity.
		out(("deserialize(Function & f, Iterator & %s, typename enable_if< mpl::equal_to<mpl::int_<%d>, typename mpl::size<MessageType>::type>, void *>::type = NULL) {"):format(iteratorName, arity))

		if arity > 0 then
			-- Create typedefs for each of the types in the message
			for i = 1, arity do
				out(1, ("typedef typename mpl::at_c<MessageType, %d>::type T%d;"):format(i - 1, i) )
			end

			-- Unbuffer (in order!) those types into temporary variables
			-- Can't just unbuffer in function call because relative order
			-- of eval of function arguments is undefined!
			for i = 1, arity do
				out(1, ("T%d a%d = Policy::template unbuffer(mpl::identity<T%d>(), it);"):format(i, i, i) )
			end
		end

		-- Come up with the tuple's type args and constructor args for use below
		local tupleTemplateParams = {"MessageType const&"}
		local tupleConstructorArgs = {"MessageType()"}
		if arity > 0 then
			table.insert(tupleTemplateParams, genRange(arity, function(i) return ("T%d"):format(i) end))
			table.insert(tupleConstructorArgs, genRange(arity, function(i) return ("a%d"):format(i) end))
		end

		-- Start the call, specify the function passing by reference,
		-- and pass the function
		out(1, "fusion::invoke_procedure<Function &>(")
		out(1, 1, "f,")

		-- Generate the tuple argument with the args computed above
		out(1, 1, ("fusion::vector< %s >("):format(commaJoin(tupleTemplateParams)))
		out(1, 2, commaJoin(tupleConstructorArgs))
		out(1, 1, ")")

		-- Finish the call and the function
		out(1, ");")
		out("}\n")
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
#ifndef INCLUDED_DeserializeOverloads_Generated_h_GUID_77b2ed7c_5501_4195_8d2c_dac91b47cf13
#define INCLUDED_DeserializeOverloads_Generated_h_GUID_77b2ed7c_5501_4195_8d2c_dac91b47cf13

// Internal Includes
#include "../constants/ArityConfig.h"

// Library/third-party includes
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/functional/invocation/invoke_procedure.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/utility/enable_if.hpp>

// Standard includes
// - none

namespace transmission {
	namespace detail {
		namespace operations {
			namespace generated {
				namespace mpl = boost::mpl;
				namespace fusion = boost::fusion;
				using boost::enable_if;
				typedef mpl::int_<]] .. tostring(ReceiveMaxArity) .. [[> DeserializeMaxArity;
]];

	suffix = [[
			} // end of namespace generated
		} // end of namespace operations
	} // end of namespace detail
} // end of namespace transmission
#endif // INCLUDED_DeserializeOverloads_Generated_h_GUID_77b2ed7c_5501_4195_8d2c_dac91b47cf13
]];
}