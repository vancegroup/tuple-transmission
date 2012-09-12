/**
	@author
	Ryan Pavlik ( <rpavlik@iastate.edu> http://academic.cleardefinition.com/ ),
	Iowa State University
	Virtual Reality Applications Center and
	Human-Computer Interaction Graduate Program
*/

#define BOOST_TEST_MODULE Sizeof

// Internal Includes

#define USE_BASIC_ENVELOPE

#include "Protocol.h"
#include <tuple-transmission/detail/operations/Sizeof.h>
#include <tuple-transmission/BoundMessageType.h>
#include <util/booststdint.h>

// Library/third-party includes
#include <boost/mpl/vector.hpp>
#include <BoostTestTargetConfig.h>

// Standard includes
// - none

using namespace boost::unit_test;
using namespace stdint;
using transmission::detail::operations::Sizeof;
using transmission::BoundMessageType;

BOOST_AUTO_TEST_CASE(GeneralSizeof) {
	namespace mpl = boost::mpl;
	BOOST_CHECK_EQUAL((Sizeof<mpl::vector<int16_t, int16_t, int16_t> >()), 3 * 2);
	BOOST_CHECK_EQUAL((Sizeof<mpl::vector<uint16_t, uint16_t, uint16_t> >()), 3 * 2);
	BOOST_CHECK_EQUAL((Sizeof<mpl::vector<int8_t> >()), 1);
	BOOST_CHECK_EQUAL((Sizeof<mpl::vector<> >()), 0);
}

BOOST_AUTO_TEST_CASE(SizeofMessageVsTypelist) {
	BOOST_CHECK_EQUAL((Sizeof<MessageATypes>()) , (Sizeof<MessageA>()));
}

BOOST_AUTO_TEST_CASE(WholeMessageSize) {
	BOOST_CHECK_EQUAL((Sizeof<BoundMessageType<MyMessageCollection, MessageA> >()), (Sizeof<MessageA>() + 5));
}

