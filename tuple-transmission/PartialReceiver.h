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
#ifndef INCLUDED_PartialReceiver_h_GUID_314b3576_c339_42e9_ac75_cccb9b7f0bfe
#define INCLUDED_PartialReceiver_h_GUID_314b3576_c339_42e9_ac75_cccb9b7f0bfe

// Internal Includes
#include "Receiver.h"

// Library/third-party includes
#include <boost/preprocessor/repetition/enum_params.hpp>

// Standard includes
// - none

namespace transmission {

	/** @brief Variant of transmission::Receiver that provides default handlers
		for all message types.

		Works the same as Receiver, except you don't have to provide all
		the handlers, and you must include a line like the following in the
		class (here, "MyReceiver") to explicitly use the provided defaults:

		using transmission::PartialReceiver<MyReceiver, MyMessageCollection>::operator();
	*/
	template<typename Derived, typename MessageCollection>
	class PartialReceiver : public Receiver<Derived, MessageCollection> {
		public:
			template <typename M, BOOST_PP_ENUM_PARAMS(1, typename T) >
			void operator()(M const&, BOOST_PP_ENUM_PARAMS(1, T)) {}

			template <typename M, BOOST_PP_ENUM_PARAMS(2, typename T) >
			void operator()(M const&, BOOST_PP_ENUM_PARAMS(2, T)) {}

			template <typename M, BOOST_PP_ENUM_PARAMS(3, typename T) >
			void operator()(M const&, BOOST_PP_ENUM_PARAMS(3, T)) {}

			template <typename M, BOOST_PP_ENUM_PARAMS(4, typename T) >
			void operator()(M const&, BOOST_PP_ENUM_PARAMS(4, T)) {}

			template <typename M, BOOST_PP_ENUM_PARAMS(5, typename T) >
			void operator()(M const&, BOOST_PP_ENUM_PARAMS(5, T)) {}

			template <typename M, BOOST_PP_ENUM_PARAMS(6, typename T) >
			void operator()(M const&, BOOST_PP_ENUM_PARAMS(6, T)) {}

			template <typename M, BOOST_PP_ENUM_PARAMS(7, typename T) >
			void operator()(M const&, BOOST_PP_ENUM_PARAMS(7, T)) {}

			template <typename M, BOOST_PP_ENUM_PARAMS(8, typename T) >
			void operator()(M const&, BOOST_PP_ENUM_PARAMS(8, T)) {}

			template <typename M, BOOST_PP_ENUM_PARAMS(9, typename T) >
			void operator()(M const&, BOOST_PP_ENUM_PARAMS(9, T)) {}
	};
} // end of namespace transmission

#endif // INCLUDED_PartialReceiver_h_GUID_314b3576_c339_42e9_ac75_cccb9b7f0bfe
