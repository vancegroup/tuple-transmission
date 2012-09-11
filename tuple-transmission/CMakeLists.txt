set(HEADERS
	envelopes/Basic.h
	envelopes/BasicChecksum.h
	BoostArrayBuffer.h
	ChecksumComputer.h
	EnvelopeBase_fwd.h
	EnvelopeBase.h
	Envelopes_fwd.h
	IntegralTypes.h
	MessageCollection.h
	MessageCount.h
	MessageCount_fwd.h
	MessageIdType.h
	MessageIdType_fwd.h
	MessageSizeType.h
	MessageSizeType_fwd.h
	MessageType.h
	Send.h
	Sizeof_fwd.h
	Sizeof.h
	TransmissionBase_fwd.h
	TransmissionBase.h
	Transmission_fwd.h
	Transmission.h
	TransmitterBase_fwd.h
	TransmitterBase.h
	TransmitterComposition.h
)

set(DETAIL_HEADERS
	detail/ControlCodes.h
	detail/MaxMessageLength.h
	detail/MessageLength.h)

add_custom_target(tuple-transmission
	SOURCES
	${HEADERS}
	${DETAIL_HEADERS})

set(HEADERS ${HEADERS} ${DETAIL_HEADERS} PARENT_SCOPE)
