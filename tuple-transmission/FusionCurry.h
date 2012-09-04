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
#ifndef INCLUDED_FusionCurry_h_GUID_7928671d_ea7f_44f1_ac2c_f36047948b10
#define INCLUDED_FusionCurry_h_GUID_7928671d_ea7f_44f1_ac2c_f36047948b10

// Internal Includes
// - none

// Library/third-party includes
#include <boost/fusion/include/push_back.hpp>
#include <boost/fusion/include/list.hpp>
#include <boost/call_traits.hpp>

// Standard includes
// - none


namespace transmission {
	template<typename Sequence>
	struct FusionCurry;

	template<typename Sequence = boost::fusion::list<> >
	struct FusionCurry {
		typedef Sequence value_type;
		FusionCurry(value_type const& val = value_type())
			: value(val)
		{}
		value_type value;

		template<typename T>
		struct append_result {
			//typedef typename boost::call_traits<T>::param_type param_type;
			typedef T param_type;
			typedef typename boost::fusion::result_of::push_back<Sequence, param_type>::type fusion_result_type;
			typedef FusionCurry<fusion_result_type> result_type;
		};
		/*
		template<typename T>
		typename append_result<T>::result_type operator()(typename append_result<T>::param_type v) const {
			return append_result<T>::result_type(boost::fusion::push_back(value, v));
		}
		*/
		template<typename T>
		typename append_result<T>::result_type operator()(T v) const {
			return boost::fusion::push_back(value, v);
		}
	};

	template<typename T>
	inline FusionCurry<boost::fusion::list<T> > StartFusionCurry(T v) {
		return FusionCurry<boost::fusion::list<T> >(boost::fusion::list<T>(v));
	}

	struct CurryStarter {
		typedef boost::fusion::list<> empty_value_type;
		empty_value_type value;

		template<typename T>
		struct type_helper {
			//typedef typename boost::call_traits<T>::param_type param_type;
			typedef T param_type;

			typedef boost::fusion::list<param_type> fusion_result_type;
			typedef FusionCurry<fusion_result_type> result_type;
		};
		template<typename T>
		typename type_helper<T>::result_type operator()(typename type_helper<T>::param_type v) {
			return typename type_helper<T>::result_type(typename type_helper<T>::fusion_result_type(v));
		}

	};


} // end of namespace transmission

#endif // INCLUDED_FusionCurry_h_GUID_7928671d_ea7f_44f1_ac2c_f36047948b10
