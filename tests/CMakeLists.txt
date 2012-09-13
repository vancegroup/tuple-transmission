add_boost_test(BasicChecksum
	SOURCES
	BasicChecksum.cpp
	TESTS
	WholeMessageSerialize)

add_boost_test(Sizeof
	SOURCES
	Sizeof.cpp
	TESTS
	GeneralSizeof
	SizeofMessageVsTypelist
	WholeMessageSize)

add_boost_test(TupleTransmission
	SOURCES
	TupleTransmission.cpp
	TESTS
	WholeMessageSerializeAutobuffer
	WholeMessageSerialize
	WholeMessageSendOverloads)

add_boost_test(MessageLength
	SOURCES
	MessageLength.cpp
	TESTS
	AccurateMaxMessageLength
	ValidMessageLengths
	ValidMessageLengthsMatchCompileTime
	InvalidMessageLength)

add_boost_test(ReceiveHandler
	SOURCES
	ReceiveHandler.cpp
	TESTS
	DefaultConstruction
	MessageMethods
	CorruptOrMistakenMessage_round0
	CorruptOrMistakenMessage_round1
	CorruptOrMistakenMessage_round2
	CorruptOrMistakenMessage_round3
	CorruptOrMistakenMessage_round4
	CorruptOrMistakenMessage_round5
	CorruptOrMistakenMessage_round6
	CorruptOrMistakenMessage_round7
	CorruptOrMistakenMessage_round8
	CorruptOrMistakenMessage_round9)


set(COMMON_RECEIVER_TESTS
	DefaultConstruction
	IncompleteMessages
	CompleteMessage
	CompleteMessageRoundtrip
	DifferentMessageSameSignature
	DifferentMessageSameSignatureRoundtrip)

add_boost_test(Receiver
	SOURCES
	Receiver.cpp
	TESTS
	${COMMON_RECEIVER_TESTS})

add_boost_test(PartialReceiver
	SOURCES
	PartialReceiver.cpp
	TESTS
	${COMMON_RECEIVER_TESTS})

add_boost_test(ChecksumReceiver
	SOURCES
	ChecksumReceiver.cpp
	TESTS
	${COMMON_RECEIVER_TESTS})

add_subdirectory(cleanbuild)
