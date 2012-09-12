return {
	outFile = "detail/operations/DeserializeOverloads_Generated.h";

	generateOverload = function(arity)
		out( "template<typename Sequence, typename Policy, typename Function, typename Iterator>")
		out(("typename enable_if<is_same<typename mpl::size<Sequence>::type, mpl::int_<%d> >, void>::type"):format(arity))
		out(("deserialize(Function & f, Iterator & it, mpl::int_<%d> &) {"):format(arity) )
		for i = 1, arity do
			out(1, ("typedef typename mpl::at_c<Sequence, %d>::type T%d;"):format(i, i) )
		end
		for i = 1, arity do
			out(1, ("T%d a%d = Policy::template unbuffer<T%d>(it);"):format(i, i, i) )
		end

		out(1, "fusion::invoke_function_object<Function &>(")
		out(1, 1, "f,")
		-- Generate the tuple argument
		out(1, 1, "fusion::vector< " .. genRange(arity, function(i) return ("T%d"):format(i) end, ", ") .. ">(")
		out(1, 2, genRange(arity, function(i) return ("a%d"):format(i) end, ", "))
		out(1, 1, ")")
		-- Finish the call and the function
		out(1, ");")
		out("}")
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
// - none

// Library/third-party includes
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/functional/invocation/invoke_function_object.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/int.hpp>
#include <boost/type_traits/is_same.hpp>
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
				using boost::is_same;
]];

	suffix = [[
			} // end of namespace generated
		} // end of namespace operations
	} // end of namespace detail
} // end of namespace transmission
#endif // INCLUDED_DeserializeOverloads_Generated_h_GUID_77b2ed7c_5501_4195_8d2c_dac91b47cf13
]];

	baseIndent = 4;

	maxArity = 10;
}
