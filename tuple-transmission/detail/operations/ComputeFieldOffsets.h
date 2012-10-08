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
#ifndef INCLUDED_ComputeFieldOffsets_h_GUID_e8baaf49_1e59_4b14_84ae_8155d41ef57e
#define INCLUDED_ComputeFieldOffsets_h_GUID_e8baaf49_1e59_4b14_84ae_8155d41ef57e

// Internal Includes
#include "SerializedFieldSize.h"

// Library/third-party includes
#include <boost/mpl/transform.hpp>
#include <boost/mpl/transform_view.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/advance.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/range_c.hpp>

// Standard includes
// - none

namespace transmission {
	namespace detail {
		namespace operations {
			namespace impl {
				namespace mpl = boost::mpl;
				template<typename Start, typename End, typename Initial>
				struct SumRange {
					typedef typename mpl::iterator_range<Start, End>::type Seq;
					typedef typename mpl::fold<Seq, Initial, mpl::plus<mpl::_1, mpl::_2> >::type type;
				};
				template<typename MessageType, typename EnvelopeType>
				struct ComputeFieldOffsetsImpl {
					typedef typename MessageType::sequence_type sequence_type;

					typedef typename mpl::transform<sequence_type, SerializedFieldSize<mpl::_1> >::type field_sizes;
					typedef typename EnvelopeType::data_offset initial_offset;
					typedef typename mpl::begin<field_sizes>::type SizesStart;

					typedef typename mpl::size<sequence_type>::type field_count;
					typedef typename mpl::range_c<uint8_t, 0, field_count::value >::type index_range;

					template<typename Position>
					struct Offset {
						typedef typename mpl::advance<SizesStart, Position >::type iter;
						typedef typename SumRange<SizesStart, iter, initial_offset>::type type;
					};
					typedef typename mpl::transform_view<index_range, Offset<mpl::_1> >::type type;
				};
			}// end of namespace impl

			template<typename MessageType, typename EnvelopeType>
			struct ComputeFieldOffsets : impl::ComputeFieldOffsetsImpl<MessageType, EnvelopeType>::type { };
		} // end of namespace operations
	} // end of namespace detail
} // end of namespace transmission

#endif // INCLUDED_ComputeFieldOffsets_h_GUID_e8baaf49_1e59_4b14_84ae_8155d41ef57e
