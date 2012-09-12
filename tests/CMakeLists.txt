add_boost_test(BasicChecksum
	SOURCES
	BasicChecksum.cpp
	TESTS
	WholeMessageSerialize)

add_boost_test(Sizeof
	SOURCES
	Sizeof.cpp
	TESTS
	SizeofRefactored
	SizeofMessageVsTypelist
	WholeMessageSize
	WholeMessageSizeDirectConstruction)

add_boost_test(TupleTransmission
	SOURCES
	TupleTransmission.cpp
	TESTS
	WholeMessageSerialize
	WholeMessageSerializeAutotransmission)

add_boost_test(MessageLength
	SOURCES
	MessageLength.cpp
	TESTS
	TypeSelection
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

add_boost_test(Receive
	SOURCES
	Receive.cpp)

add_subdirectory(cleanbuild)
