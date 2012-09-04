/**
	@author
	Ryan Pavlik ( <rpavlik@iastate.edu> http://academic.cleardefinition.com/ ),
	Iowa State University
	Virtual Reality Applications Center and
	Human-Computer Interaction Graduate Program
*/

#define BOOST_TEST_MODULE FusionCurry

// Internal Includes
#include <tuple-transmission/FusionCurry.h>
#include <util/booststdint.h>

// Library/third-party includes
#include <BoostTestTargetConfig.h>

// Standard includes


using namespace boost::unit_test;


BOOST_AUTO_TEST_CASE(Explicit) {
	{ transmission::FusionCurry<> a; }
	//BOOST_CHECK_EQUAL(transmission::CurryStarter()(int(5))(int(10))(int(15)), (boost::fusion::list<int, int, int>(5, 10, 15)) );
	BOOST_CHECK(transmission::FusionCurry<>()(int(5))(int(10))(int(15)) == (boost::fusion::list<int, int, int>(5, 10, 15)) );
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
