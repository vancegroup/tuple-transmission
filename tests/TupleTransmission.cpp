/**
	@author
	Ryan Pavlik ( <rpavlik@iastate.edu> http://academic.cleardefinition.com/ ),
	Iowa State University
	Virtual Reality Applications Center and
	Human-Computer Interaction Graduate Program
*/

#define BOOST_TEST_MODULE TupleTransmission

// Internal Includes
#include <tuple-transmission/MessageType.h>
#include <tuple-transmission/MessageCollection.h>
#include <tuple-transmission/Sizeof.h>
#include <tuple-transmission/EnvelopeBasic.h>
#include <util/booststdint.h>

// Library/third-party includes
#include <boost/mpl/vector.hpp>
#include <BoostTestTargetConfig.h>

// Standard includes
#include <string>
#include <sstream>


using namespace boost::unit_test;
using namespace stdint;

typedef boost::mpl::vector<int8_t, uint8_t, int16_t> MessageATypes;
struct MessageA : transmission::MessageTypeBase<MessageATypes> {};
struct MessageB : transmission::MessageTypeBase<boost::mpl::vector<uint8_t, uint8_t, uint8_t> > {};

typedef transmission::MessageCollection<
	boost::mpl::vector<
			MessageA
		>
	> MyMessageCollection;


BOOST_AUTO_TEST_CASE(SizeofRefactored) {
	using transmission::SizeofMessage;
	BOOST_CHECK_EQUAL( int(SizeofMessage<MessageATypes>::value) , int(SizeofMessage<MessageA>::value));
}

BOOST_AUTO_TEST_CASE(WholeMessageSize) {
	using transmission::SizeofMessage;
	BOOST_CHECK_EQUAL( int(MyMessageCollection::MessageSize<MessageA>::value), int(SizeofMessage<MessageA>::value) + 5 );
}

/*
BOOST_AUTO_TEST_CASE(ConstantVecRoundTrip) {

	Eigen::Vector3d deserialized;

	std::stringstream ss;
	{
		Eigen::Vector3d c(Eigen::Vector3d::Constant(1));
		boost::archive::text_oarchive outArchive(ss);
		outArchive << c;
	}
	std::cout << ss.str();
	{
		boost::archive::text_iarchive inArchive(ss);
		inArchive >> deserialized;
	}
	BOOST_CHECK_EQUAL(Eigen::Vector3d::Constant(1), deserialized);
}
*/
