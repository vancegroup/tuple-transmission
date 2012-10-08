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
	WholeMessageSendOverloads
	ComputeFieldOffsets)

add_boost_test(MessageLength
	SOURCES
	MessageLength.cpp
	TESTS
	AccurateMaxMessageLength
	ValidMessageLengths
	ValidMessageLengthsMatchCompileTime
	InvalidMessageLength)

add_boost_test(EnvelopeReceiveBuffer
	SOURCES
	EnvelopeReceiveBuffer.cpp
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


set(COMMON_HANDLER_TESTS
	DefaultConstruction
	IncompleteMessages
	CompleteMessage)

add_boost_test(Handler
	SOURCES
	Handler.cpp
	TESTS
	DifferentMessageSameSignature
	${COMMON_HANDLER_TESTS})

add_boost_test(PartialHandler
	SOURCES
	PartialHandler.cpp
	TESTS
	DifferentMessageSameSignature
	${COMMON_HANDLER_TESTS})

add_boost_test(ChecksumHandler
	SOURCES
	ChecksumHandler.cpp
	TESTS
	ValidMessageButModifiedId
	${COMMON_HANDLER_TESTS})

set(COMMON_ROUNDTRIP_TESTS
	MessageB_Roundtrip
	MessageB_RoundtripBound
	MessageB_RoundtripOverloaded
	MessageB_RoundtripOverloadedBound
	EmptyMessage_Roundtrip
	EmptyMessage_RoundtripBound
	EmptyMessage_RoundtripOverloaded
	EmptyMessage_RoundtripOverloadedBound
	MessageA_SendRecv
	MessageA_SendRecvBound
	MessageA_SendRecvOverloaded
	MessageA_SendRecvOverloadedBound
	MessageC_SendRecv
	MessageC_SendRecvBound
	MessageC_SendRecvOverloaded
	MessageC_SendRecvOverloadedBound
	MessageD_SendRecv
	MessageD_SendRecvBound
	MessageD_SendRecvOverloaded
	MessageD_SendRecvOverloadedBound
	MaxArityMessage_SendRecv
	MaxArityMessage_SendRecvBound
	MaxArityMessage_SendRecvOverloaded
	MaxArityMessage_SendRecvOverloadedBound)

add_boost_test(BasicRoundtrip
	SOURCES
	BasicRoundtrip.cpp
	TESTS
	${COMMON_ROUNDTRIP_TESTS})

add_boost_test(ChecksumRoundtrip
	SOURCES
	ChecksumRoundtrip.cpp
	TESTS
	${COMMON_ROUNDTRIP_TESTS})


add_subdirectory(cleanbuild)
