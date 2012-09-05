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

add_custom_target(tuple-transmission
	SOURCES
	${HEADERS})

set(HEADERS ${HEADERS} PARENT_SCOPE)
