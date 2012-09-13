return {
	outFile = "detail/constants/ArityConfig.h";
	baseIndent = 0;
	-- Setting min and max arity to 0 to have just one call into the generate function.
	minArity = 0;
	maxArity = 0;
	generate = function()
		-- Fusion definitions - must be before including any fusion header!
		out(("#define FUSION_MAX_LIST_SIZE %d"):format(SendOverloadMaxArity))
		out(("#define BOOST_FUSION_INVOKE_PROCEDURE_MAX_ARITY %d"):format(ReceiveMaxArity))

		-- An enum recording the receive max arity as used to generate headers
		out("namespace transmission {")
		out(1, "namespace detail {")
		out(2, "namespace constants {")
		out(3, "enum {")
		out(4, ("ReceiveMaxArity = %d"):format(ReceiveMaxArity))
		out(3, "};")
		out(2, "} // end of namespace constants")
		out(1, "} // end of namespace detail")
		out("} // end of namespace transmission")
	end;

	prefix = [[
/** @file
	@brief Config header with Fusion limit defines - Must be included before any
	Fusion header!

	Header AUTO-GENERATED by %s to ensure consistency

	DO NOT EDIT THIS FILE DIRECTLY - instead, edit the script that generates it.
	In this case, this file mostly exists to get constants used when generating
	_any_ file into one file to configure support libraries, so the generation
	script shared by all generated files contains the typically-interesting
	values.

	Note that only by editing and re-running the generating script can you
	change these limits, since some files are pre-generated instead of
	using BOOST_PP_...

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
#ifndef INCLUDED_FusionConfig_h_GUID_e185dc4f_3d12_4f22_ae37_ee131be6d12a
#define INCLUDED_FusionConfig_h_GUID_e185dc4f_3d12_4f22_ae37_ee131be6d12a

// Internal Includes
// - none

// Library/third-party includes
// - none

// Standard includes
// - none


]];

	suffix = [[

#endif // INCLUDED_FusionConfig_h_GUID_e185dc4f_3d12_4f22_ae37_ee131be6d12a
]];
}
