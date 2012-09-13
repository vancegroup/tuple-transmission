/** @file
	@brief Header AUTO-GENERATED by variadicGenerate.lua on input SendOverloads.gen.lua to avoid doing crazy preprocessor things

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
#include "../bases/TransmitterBase_fwd.h"

// Library/third-party includes
#include <boost/fusion/include/make_list.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/utility/enable_if.hpp>

// Standard includes
// - none

namespace transmission {
	template<typename Collection, typename Message, typename TransmitterDerived, typename MessageContentsType>
	void send(transmitters::TransmitterBase<TransmitterDerived> & tx, MessageContentsType const & contents);
	namespace detail {
		namespace operations {
			namespace generated {
				namespace mpl = boost::mpl;
				namespace fusion = boost::fusion;
				using boost::enable_if;
				typedef mpl::int_<9> SendOverloadMaxArity;

				template<typename Collection, typename Message, typename TransmitterDerived>
				inline typename enable_if< mpl::equal_to<mpl::int_<1>, typename mpl::size<Message>::type>, void>::type
				send(transmitters::TransmitterBase<TransmitterDerived> & tx, typename mpl::at_c<Message, 0>::type a1) {
					::transmission::send<Collection, Message>(
					    tx,
					    fusion::make_list(
					        a1
					    )
					);
				}
				template<typename Collection, typename Message, typename TransmitterDerived>
				inline typename enable_if< mpl::equal_to<mpl::int_<2>, typename mpl::size<Message>::type>, void>::type
				send(transmitters::TransmitterBase<TransmitterDerived> & tx, typename mpl::at_c<Message, 0>::type a1, typename mpl::at_c<Message, 1>::type a2) {
					::transmission::send<Collection, Message>(
					    tx,
					    fusion::make_list(
					        a1, a2
					    )
					);
				}
				template<typename Collection, typename Message, typename TransmitterDerived>
				inline typename enable_if< mpl::equal_to<mpl::int_<3>, typename mpl::size<Message>::type>, void>::type
				send(transmitters::TransmitterBase<TransmitterDerived> & tx, typename mpl::at_c<Message, 0>::type a1, typename mpl::at_c<Message, 1>::type a2, typename mpl::at_c<Message, 2>::type a3) {
					::transmission::send<Collection, Message>(
					    tx,
					    fusion::make_list(
					        a1, a2, a3
					    )
					);
				}
				template<typename Collection, typename Message, typename TransmitterDerived>
				inline typename enable_if< mpl::equal_to<mpl::int_<4>, typename mpl::size<Message>::type>, void>::type
				send(transmitters::TransmitterBase<TransmitterDerived> & tx, typename mpl::at_c<Message, 0>::type a1, typename mpl::at_c<Message, 1>::type a2, typename mpl::at_c<Message, 2>::type a3, typename mpl::at_c<Message, 3>::type a4) {
					::transmission::send<Collection, Message>(
					    tx,
					    fusion::make_list(
					        a1, a2, a3, a4
					    )
					);
				}
				template<typename Collection, typename Message, typename TransmitterDerived>
				inline typename enable_if< mpl::equal_to<mpl::int_<5>, typename mpl::size<Message>::type>, void>::type
				send(transmitters::TransmitterBase<TransmitterDerived> & tx, typename mpl::at_c<Message, 0>::type a1, typename mpl::at_c<Message, 1>::type a2, typename mpl::at_c<Message, 2>::type a3, typename mpl::at_c<Message, 3>::type a4, typename mpl::at_c<Message, 4>::type a5) {
					::transmission::send<Collection, Message>(
					    tx,
					    fusion::make_list(
					        a1, a2, a3, a4, a5
					    )
					);
				}
				template<typename Collection, typename Message, typename TransmitterDerived>
				inline typename enable_if< mpl::equal_to<mpl::int_<6>, typename mpl::size<Message>::type>, void>::type
				send(transmitters::TransmitterBase<TransmitterDerived> & tx, typename mpl::at_c<Message, 0>::type a1, typename mpl::at_c<Message, 1>::type a2, typename mpl::at_c<Message, 2>::type a3, typename mpl::at_c<Message, 3>::type a4, typename mpl::at_c<Message, 4>::type a5, typename mpl::at_c<Message, 5>::type a6) {
					::transmission::send<Collection, Message>(
					    tx,
					    fusion::make_list(
					        a1, a2, a3, a4, a5, a6
					    )
					);
				}
				template<typename Collection, typename Message, typename TransmitterDerived>
				inline typename enable_if< mpl::equal_to<mpl::int_<7>, typename mpl::size<Message>::type>, void>::type
				send(transmitters::TransmitterBase<TransmitterDerived> & tx, typename mpl::at_c<Message, 0>::type a1, typename mpl::at_c<Message, 1>::type a2, typename mpl::at_c<Message, 2>::type a3, typename mpl::at_c<Message, 3>::type a4, typename mpl::at_c<Message, 4>::type a5, typename mpl::at_c<Message, 5>::type a6, typename mpl::at_c<Message, 6>::type a7) {
					::transmission::send<Collection, Message>(
					    tx,
					    fusion::make_list(
					        a1, a2, a3, a4, a5, a6, a7
					    )
					);
				}
				template<typename Collection, typename Message, typename TransmitterDerived>
				inline typename enable_if< mpl::equal_to<mpl::int_<8>, typename mpl::size<Message>::type>, void>::type
				send(transmitters::TransmitterBase<TransmitterDerived> & tx, typename mpl::at_c<Message, 0>::type a1, typename mpl::at_c<Message, 1>::type a2, typename mpl::at_c<Message, 2>::type a3, typename mpl::at_c<Message, 3>::type a4, typename mpl::at_c<Message, 4>::type a5, typename mpl::at_c<Message, 5>::type a6, typename mpl::at_c<Message, 6>::type a7, typename mpl::at_c<Message, 7>::type a8) {
					::transmission::send<Collection, Message>(
					    tx,
					    fusion::make_list(
					        a1, a2, a3, a4, a5, a6, a7, a8
					    )
					);
				}
				template<typename Collection, typename Message, typename TransmitterDerived>
				inline typename enable_if< mpl::equal_to<mpl::int_<9>, typename mpl::size<Message>::type>, void>::type
				send(transmitters::TransmitterBase<TransmitterDerived> & tx, typename mpl::at_c<Message, 0>::type a1, typename mpl::at_c<Message, 1>::type a2, typename mpl::at_c<Message, 2>::type a3, typename mpl::at_c<Message, 3>::type a4, typename mpl::at_c<Message, 4>::type a5, typename mpl::at_c<Message, 5>::type a6, typename mpl::at_c<Message, 6>::type a7, typename mpl::at_c<Message, 7>::type a8, typename mpl::at_c<Message, 8>::type a9) {
					::transmission::send<Collection, Message>(
					    tx,
					    fusion::make_list(
					        a1, a2, a3, a4, a5, a6, a7, a8, a9
					    )
					);
				}
			} // end of namespace generated
		} // end of namespace operations
	} // end of namespace detail

	using detail::operations::generated::send;
} // end of namespace transmission
#endif // INCLUDED_SendOverloads_Generated_h_GUID_ceb4f589_526e_49d7_84c5_0b38f6d1fc42

