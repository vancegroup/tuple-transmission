/**
	@author
	Ryan Pavlik ( <rpavlik@iastate.edu> http://academic.cleardefinition.com/ ),
	Iowa State University
	Virtual Reality Applications Center and
	Human-Computer Interaction Graduate Program
*/

#define BOOST_TEST_MODULE MessageLength

// Internal Includes

#define USE_BASIC_ENVELOPE
#include "Protocol.h"
#include <tuple-transmission/detail/MessageLength.h>
#include <tuple-transmission/detail/MaxMessageLength.h>

// Library/third-party includes
#include <boost/mpl/assert.hpp>
#include <boost/mpl/int.hpp>
#include <BoostTestTargetConfig.h>

// Standard includes
// - none

using namespace boost::unit_test;

using transmission::detail::MaxMessageLength;
using transmission::detail::MessageLength;
using transmission::detail::getMessageLength;
using transmission::MessageSizeType;
using transmission::MinimalMessageIdType;
using boost::mpl::int_;
using boost::is_same;

BOOST_AUTO_TEST_CASE(TypeSelection) {
	BOOST_MPL_ASSERT((is_same<MessageSizeType<MyMessageCollection>::type, uint8_t>));
	BOOST_MPL_ASSERT((is_same<MinimalMessageIdType<MyMessageCollection>::type, uint8_t>));
}

BOOST_AUTO_TEST_CASE(AccurateMaxMessageLength) {
	BOOST_CHECK_EQUAL(MaxMessageLength<MyMessageCollection>(), 9);
}

BOOST_AUTO_TEST_CASE(ValidMessageLengths) {
	BOOST_CHECK_EQUAL(getMessageLength<MyMessageCollection>(0), 9);
	BOOST_CHECK_EQUAL(getMessageLength<MyMessageCollection>(1), 8);
}

BOOST_AUTO_TEST_CASE(ValidMessageLengthsMatchCompileTime) {
	BOOST_CHECK_EQUAL(getMessageLength<MyMessageCollection>(0), (MessageLength<MyMessageCollection, int_<0> >()));
	BOOST_CHECK_EQUAL(getMessageLength<MyMessageCollection>(1), (MessageLength<MyMessageCollection, int_<1> >()));
}

BOOST_AUTO_TEST_CASE(InvalidMessageLength) {
	BOOST_CHECK(!getMessageLength<MyMessageCollection>(2));
}

