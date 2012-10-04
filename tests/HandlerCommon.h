

using transmission::BoundMessageType;

typedef transmission::Receiver<MyMessageCollection> TestReceiver;

inline void appendValidMessageCharacters(TestReceiver & recv, std::size_t n, std::size_t start = 0) {
	BOOST_TEST_MESSAGE("Inserting valid message elements [" << start << ", " << start + n - 1 << "]");
	BOOST_ASSERT(start + n <= ValidMessage.size());
	recv.appendReceived(ValidMessage.begin() + start, ValidMessage.begin() + start + n);
	recv.processMessages();
}

BOOST_AUTO_TEST_CASE(DefaultConstruction) {
	TestHandler h;
	BOOST_REQUIRE_NO_THROW(TestReceiver a(h));
	TestReceiver r(h);
	BOOST_CHECK_EQUAL(h.first, 0);
	BOOST_CHECK_EQUAL(h.second, 0);
	BOOST_CHECK_EQUAL(h.third, 0);
}

BOOST_AUTO_TEST_CASE(IncompleteMessages) {
	TestHandler h;
	TestReceiver r(h);
	for (unsigned long n = 1; n < ValidMessage.size(); ++n) {
		appendValidMessageCharacters(r, n);
		BOOST_CHECK_EQUAL(h.first, 0);
		BOOST_CHECK_EQUAL(h.second, 0);
		BOOST_CHECK_EQUAL(h.third, 0);
	}
}

BOOST_AUTO_TEST_CASE(CompleteMessage) {
	TestHandler h;
	TestReceiver r(h);
	appendValidMessageCharacters(r, ValidMessage.size());
	BOOST_CHECK_EQUAL(h.first, 5);
	BOOST_CHECK_EQUAL(h.second, 10);
	BOOST_CHECK_EQUAL(h.third, 15);
}

#if defined(USE_BASIC_ENVELOPE)
BOOST_AUTO_TEST_CASE(DifferentMessageSameSignature) {
#elif defined(USE_CHECKSUM_ENVELOPE)
BOOST_AUTO_TEST_CASE(ValidMessageButModifiedId) {
#endif
	/// This actually tests checksum failure on the ChecksumReceiver suite,
	/// since we're modifying a stock message rather than roundtripping.
	TestHandler h;
	TestReceiver r(h);
	typedef BoundMessageType<MyMessageCollection, MessageD> BoundMessageD;

	/// Change the ID to MessageD which has the same signature.
	ValidMessageBufferType buf = ValidMessage;
	buf[MessageIdIndex] = BoundMessageD::message_id();
	r.appendReceived(buf.begin(), buf.end());
	BOOST_CHECK_EQUAL(h.first, 0);
	BOOST_CHECK_EQUAL(h.second, 0);
	BOOST_CHECK_EQUAL(h.third, 0);
}

