/**
	@author
	Ryan Pavlik ( <rpavlik@iastate.edu> http://academic.cleardefinition.com/ ),
	Iowa State University
	Virtual Reality Applications Center and
	Human-Computer Interaction Graduate Program
*/

#define BOOST_TEST_MODULE Sizeof

// Internal Includes

#define TEST_ENVELOPE_TYPE ::transmission::envelopes::Basic

#include "Protocol.h"
#include <tuple-transmission/envelopes/Basic.h>
#include <tuple-transmission/Transmission.h>
#include <tuple-transmission/Sizeof.h>
#include <util/booststdint.h>

// Library/third-party includes
#include <boost/mpl/vector.hpp>
#include <BoostTestTargetConfig.h>

// Standard includes
// - none

using namespace boost::unit_test;
using namespace stdint;

BOOST_AUTO_TEST_CASE(SizeofRefactored) {
	using transmission::Sizeof;
	namespace mpl = boost::mpl;
	BOOST_CHECK_EQUAL((Sizeof<mpl::vector<int16_t, int16_t, int16_t> >()), 3 * 2);
	BOOST_CHECK_EQUAL((Sizeof<mpl::vector<uint16_t, uint16_t, uint16_t> >()), 3 * 2);
	BOOST_CHECK_EQUAL((Sizeof<mpl::vector<int8_t> >()), 1);
	BOOST_CHECK_EQUAL((Sizeof<mpl::vector<> >()), 0);
}

BOOST_AUTO_TEST_CASE(SizeofMessageVsTypelist) {
	using transmission::Sizeof;
	BOOST_CHECK_EQUAL((Sizeof<MessageATypes>()) , (Sizeof<MessageA>()));
}

BOOST_AUTO_TEST_CASE(WholeMessageSize) {
	using transmission::Sizeof;
	using transmission::Transmission;
	BOOST_CHECK_EQUAL((Sizeof<Transmission<MyMessageCollection, MessageA> >()), (Sizeof<MessageA>() + 5));
}

BOOST_AUTO_TEST_CASE(WholeMessageSizeDirectConstruction) {
	using transmission::Sizeof;
	using transmission::TransmissionBase;
	BOOST_CHECK_EQUAL((Sizeof<TransmissionBase<transmission::envelopes::Basic, boost::mpl::int_<0>, MessageA> >()), (Sizeof<MessageA>() + 5));
}

