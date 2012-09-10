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
	WholeMessageSerialize)

add_boost_test(MessageLength
	SOURCES
	MessageLength.cpp
	TESTS
	TypeSelection
	AccurateMaxMessageLength
	ValidMessageLengths
	ValidMessageLengthsMatchCompileTime
	InvalidMessageLength)

add_subdirectory(cleanbuild)
