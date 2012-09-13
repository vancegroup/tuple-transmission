
using transmission::BoundMessageType;
using transmission::transmitters::VectorBuffer;

#include <tuple-transmission/transmitters/VectorBuffer.h>

inline void appendValidMessageCharacters(TestReceiver & recv, std::size_t n, std::size_t start = 0) {
	BOOST_TEST_MESSAGE("Inserting valid message elements [" << start << ", " << start + n - 1 << "]");
	BOOST_ASSERT(start + n <= ValidMessage.size());
	recv.appendReceived(ValidMessage.begin() + start, ValidMessage.begin() + start + n);
}

BOOST_AUTO_TEST_CASE(DefaultConstruction) {
	BOOST_REQUIRE_NO_THROW(TestReceiver());
	TestReceiver r;
	BOOST_CHECK_EQUAL(r.first, 0);
	BOOST_CHECK_EQUAL(r.second, 0);
	BOOST_CHECK_EQUAL(r.third, 0);
}

BOOST_AUTO_TEST_CASE(IncompleteMessages) {
	TestReceiver r;
	for (unsigned long n = 1; n < ValidMessage.size(); ++n) {
		appendValidMessageCharacters(r, n);
		BOOST_CHECK_EQUAL(r.first, 0);
		BOOST_CHECK_EQUAL(r.second, 0);
		BOOST_CHECK_EQUAL(r.third, 0);
	}
}

BOOST_AUTO_TEST_CASE(CompleteMessage) {
	TestReceiver r;
	appendValidMessageCharacters(r, ValidMessage.size());
	BOOST_CHECK_EQUAL(r.first, 5);
	BOOST_CHECK_EQUAL(r.second, 10);
	BOOST_CHECK_EQUAL(r.third, 15);
}

BOOST_AUTO_TEST_CASE(CompleteMessageRoundtrip) {
	VectorBuffer<MyMessageCollection> buf;
	send<MyMessageCollection, MessageB>(buf, 5, 10, 15);

	TestReceiver r;
	r.appendReceived(buf.begin(), buf.end());
	BOOST_CHECK_EQUAL(r.first, 5);
	BOOST_CHECK_EQUAL(r.second, 10);
	BOOST_CHECK_EQUAL(r.third, 15);
}

BOOST_AUTO_TEST_CASE(DifferentMessageSameSignature) {
	/// This actually tests checksum failure on the ChecksumReceiver suite,
	/// since we're modifying a stock message rather than roundtripping.
	TestReceiver r;
	typedef BoundMessageType<MyMessageCollection, MessageD> BoundMessageD;

	/// Change the ID to MessageD which has the same signature.
	ValidMessageBufferType buf = ValidMessage;
	buf[MessageIdIndex] = BoundMessageD::message_id();
	r.appendReceived(buf.begin(), buf.end());
	BOOST_CHECK_EQUAL(r.first, 0);
	BOOST_CHECK_EQUAL(r.second, 0);
	BOOST_CHECK_EQUAL(r.third, 0);
}

BOOST_AUTO_TEST_CASE(DifferentMessageSameSignatureRoundtrip) {
	VectorBuffer<MyMessageCollection> buf;
	send<MyMessageCollection, MessageD>(buf, 5, 10, 15);

	TestReceiver r;
	r.appendReceived(buf.begin(), buf.end());
	BOOST_CHECK_EQUAL(r.first, 0);
	BOOST_CHECK_EQUAL(r.second, 0);
	BOOST_CHECK_EQUAL(r.third, 0);
}
