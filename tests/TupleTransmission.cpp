/**
	@author
	Ryan Pavlik ( <rpavlik@iastate.edu> http://academic.cleardefinition.com/ ),
	Iowa State University
	Virtual Reality Applications Center and
	Human-Computer Interaction Graduate Program
*/

#define BOOST_TEST_MODULE TupleTransmission

// Internal Includes
#include "Protocol.h"
#include <tuple-transmission/MessageType.h>
#include <tuple-transmission/MessageCollection.h>
#include <tuple-transmission/Sizeof.h>
#include <tuple-transmission/Transmission.h>
#include <tuple-transmission/EnvelopeBasic.h>

// Library/third-party includes
#include <BoostTestTargetConfig.h>

// Standard includes
// - none



using namespace boost::unit_test;



BOOST_AUTO_TEST_CASE(SizeofRefactored) {
	using transmission::Sizeof;
	BOOST_CHECK_EQUAL((Sizeof<MessageATypes>()) , (Sizeof<MessageA>()));
}

BOOST_AUTO_TEST_CASE(WholeMessageSize) {
	using transmission::Sizeof;
	using transmission::Transmission;
	BOOST_CHECK_EQUAL((Sizeof<Transmission<MyMessageCollection, MessageA> >()), (Sizeof<MessageA>() + 5));
}
/*
BOOST_AUTO_TEST_CASE(WholeMessageSerialize) {
	using transmission::SizeofMessage;
	typedef BoostArrayBuffer<MyMessageCollection::MessageSize<MessageB>::value> TransmitBufferType;
	TransmitBufferType buf;

	BOOST_CHECK_EQUAL( int(MyMessageCollection::MessageSize<MessageA>::value), int(SizeofMessage<MessageA>::value) + 5 );
}
*/
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
