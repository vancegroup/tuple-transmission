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
#ifndef INCLUDED_DeserializeToFusion_h_GUID_b17df18e_243c_49cf_ab9f_491cf3dc504f
#define INCLUDED_DeserializeToFusion_h_GUID_b17df18e_243c_49cf_ab9f_491cf3dc504f

// Internal Includes
#include "../constants/ArityConfig.h"

// Library/third-party includes
#include <boost/fusion/mpl.hpp>
#include <boost/fusion/include/push_back.hpp>
#include <boost/fusion/include/list.hpp>
#include <boost/fusion/include/fold.hpp>
#include <boost/fusion/include/deref.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/fusion/functional/invocation/invoke_procedure.hpp>
#include <boost/fusion/include/as_vector.hpp>
#include <boost/fusion/include/single_view.hpp>

// Standard includes
// - none


#ifndef BOOST_TEST_MESSAGE
#define BOOST_TEST_MESSAGE(X)
#endif

namespace transmission {
	namespace detail {
		namespace operations {
			namespace impl {
				namespace fusion = boost::fusion;
				namespace mpl = boost::mpl;

				/// Struct for all the stuff staying the same throughout the call.
				template<typename Function, typename TypeEnd, typename Iterator, typename Policy>
				struct DeserializationContext {
					DeserializationContext(Iterator & iter, Function & func) : it(iter), f(func) {}
					Iterator & it;
					Function & f;

					template<typename T>
					T unbuffer() {
						return Policy::unbuffer(mpl::identity<T>(), it);
					}
					typedef Policy policy;
					typedef TypeEnd end;
					typedef Function function;
				};

				/// Template struct for recursive calls.
				template<typename TypeIter, typename Context>
				struct Deserialize {
					typedef typename mpl::next<TypeIter>::type Next;
					typedef typename mpl::deref<TypeIter>::type T;
					template<typename State>
					static void apply(Context & c, State const& s) {
						T v = c.template unbuffer<T>();
						Deserialize<Next, Context>::apply(c, fusion::push_back(s, v));
					}
				};

				/// Partial specialization for when the end has arrived.
				template<typename Context>
				struct Deserialize<typename Context::end, Context> {
					template<typename State>
					static void apply(Context & c, State const& s) {
						c.f(s);
					}
				};

				/// entry point
				template<typename Sequence, typename Policy, typename Function, typename Iterator>
				void deserializeAndCall(Iterator & it, Function & f) {
					typedef typename mpl::begin<Sequence>::type begin;
					typedef typename mpl::end<Sequence>::type end;
					typedef DeserializationContext<Function, end, Iterator, Policy> Context;
					Context c(it, f);

					Deserialize<begin, Context>::apply(c, fusion::nil());
				}

				template<typename SerializationPolicy, typename Function, typename Iterator>
				struct DeserializeFunctorWrapper {
					public:

						typedef SerializationPolicy Policy;

						DeserializeFunctorWrapper(Function & func, Iterator & iter) : f(func), it(iter) {}
						template<typename MessageType>
						struct InvokeWrapper {
							InvokeWrapper(Function & func) : f(func) {}
							Function & f;
							template<typename SequenceType>
							void operator()(SequenceType const& s) {
								BOOST_TEST_MESSAGE("Inside the Invoke Wrapper with a sequence of size " << int(fusion::size(s)));
								f(MessageType(), s);
								//fusion::invoke_procedure<Function &>(f, fusion::push_front(s, MessageType()));
							}
						};
						template<typename MessageTypeWrapped>
						void operator()(MessageTypeWrapped const&) {
							typedef typename MessageTypeWrapped::type message_type;
							typedef typename message_type::sequence_type sequence_type;
							InvokeWrapper<message_type> invoker(f);

							deserializeAndCall<sequence_type, SerializationPolicy>(it, invoker);
						}
					private:
						Function & f;
						Iterator & it;
						//DeserializeToFusionFunctor<Iterator, SerializationPolicy> deserializeFunctor;
				};
			} // end namespace impl
		} // end of namespace operations
	} // end of namespace detail
} // end of namespace transmission

#endif // INCLUDED_DeserializeToFusion_h_GUID_b17df18e_243c_49cf_ab9f_491cf3dc504f
