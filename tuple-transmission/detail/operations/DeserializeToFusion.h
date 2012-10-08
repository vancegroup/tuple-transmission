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

namespace transmission {
	namespace detail {
		namespace operations {
			namespace impl {
				namespace fusion = boost::fusion;
				namespace mpl = boost::mpl;
				/*
								template<typename Iterator, typename Policy>
								struct DeserializeToFusionFunctor {
									DeserializeToFusionFunctor(Iterator & i) : it(i) {}

									Iterator & it;

									template<typename> struct result;
									template<typename F, typename State, typename Elt>
									struct result<F(State, Elt)> {
										typedef typename fusion::result_of::push_back<State, Elt>::type type;
									};

									template<typename State, typename Elt>
									typename fusion::result_of::push_back<State, Elt>::type operator()(State s, Elt const&) {
										//typedef typename fusion::deref<EltIter>::type T;
										typedef Elt T;
										return fusion::push_back(s, Policy::template unbuffer(boost::mpl::identity<T>(), it));
									}

								};
								*/
				template<typename Function, typename TypeEnd, typename Iterator, typename Policy>
				struct DeserializeToFusion {

					template<typename TypeIter>
					struct Algorithm {
						typedef typename mpl::next<TypeIter>::type next;
						typedef typename mpl::deref<TypeIter>::type T;
						typedef typename boost::is_same<next, TypeEnd>::type IsEnd;
						//typedef typename GetResult<TypeIter>::type result;

						template<typename State>
						static void recurse(State const& s, Function & f, Iterator & it, boost::true_type const&) {
							f(s);
						}
						template<typename State>
						static void recurse(State const& s, Function & f, Iterator & it, boost::false_type const&) {
							T v = Policy::template unbuffer(mpl::identity<T>(), it);
							Algorithm<next>::apply(fusion::push_back(s, v), f, it);
						}
						template<typename State>
						static void apply(State const& s, Function & f, Iterator & it) {
							recurse(s, f, it, IsEnd());
						}

					};
				};
				/*
				template<typename TypeEnd, typename Iterator, typename Policy>
				struct DeserializeToFusion {

					template<typename TypeIter>
					struct GetResult {
						typedef typename mpl::next<TypeIter>::type next;
						typedef typename mpl::deref<TypeIter>::type T;
						typedef typename boost::is_same<next, TypeEnd>::type IsLast;
						typedef typename boost::is_same<TypeIter, TypeEnd>::type IsEnd;
						typedef typename mpl::eval_if<
							IsEnd,
							mpl::identity<void>,
							mpl::eval_if<
								IsLast,
								mpl::identity<void>,
								GetResult<next> > >::type next_result;

						typedef typename mpl::eval_if<
							IsEnd,
							mpl::identity<void>,
							mpl::eval_if<
								IsLast,
								mpl::identity<fusion::single_view<T> >,
								fusion::result_of::push_front<next_result, T> > >::type type;
					};
					template<typename TypeIter>
					struct Algorithm {
						typedef typename mpl::next<TypeIter>::type next;
						typedef typename mpl::deref<TypeIter>::type T;
						typedef typename boost::is_same<next, TypeEnd>::type IsLast;
						typedef typename GetResult<TypeIter>::type result;

						static result recurse(Iterator & it, T v, boost::true_type const&) {
							return fusion::single_view<T>(v);
						}
						static result recurse(Iterator & it, T v, boost::false_type const&) {
							typedef typename GetResult<TypeIter>::next_result next_result;
							return fusion::push_front<next_result, T>(Algorithm<next>::apply(it), v);
						}
						static result apply(Iterator & it) {
							T v = Policy::template unbuffer(mpl::identity<T>(), it);
							return recurse(it, v, IsLast());
						}

					};
				};
				*/
				template<typename SerializationPolicy, typename Function, typename Iterator>
				struct DeserializeFunctorWrapper {
					public:
						DeserializeFunctorWrapper(Function & func, Iterator & iter) : f(func), it(iter) {}
						template<typename MessageType>
						struct InvokeWrapper {
							InvokeWrapper(Function & func) : f(func) {}
							Function & f;
							template<typename SequenceType>
							void operator()(SequenceType const& s) {
								//f(MessageType(), s);
								fusion::invoke_procedure<Function &>(f, fusion::push_front(s, MessageType()));
							}
						};
						template<typename MessageTypeWrapped>
						void operator()(MessageTypeWrapped const&) {
							typedef typename MessageTypeWrapped::type MessageType;
							typedef typename MessageType::sequence_type SequenceType;
							typedef typename mpl::begin<SequenceType>::type start;
							typedef typename mpl::deref<start>::type T;
							typedef typename mpl::end<SequenceType>::type end;
							typedef typename mpl::next<start>::type next;
							typedef DeserializeToFusion<InvokeWrapper<MessageType>, end, Iterator, SerializationPolicy> AlgContext;
							//AlgContext::template Algorithm<start>::apply(it);
							InvokeWrapper<MessageType> invoker(f);
							AlgContext::template Algorithm<next>::apply(fusion::single_view<T>(Policy::template unbuffer(mpl::identity<T>(), it), invoker, it);
							        /*
							        fusion::fold<SequenceType>(SequenceType(),
							                         fusion::list<MessageType>(MessageType()),
							                         deserializeFunctor);

							        f(MessageType(),
							            fusion::fold(fusion::as_vector(SequenceType()),
							                         fusion::list<MessageType>(MessageType()),
							                         deserializeFunctor)
							        );
							        */
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
