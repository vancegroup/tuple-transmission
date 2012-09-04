set(HEADERS
	AddContextToMessageType_fwd.h
	AddContextToMessageType.h
	BoostArrayBufferTransmission.h
	CreateMessage.h
	EnvelopeBase_fwd.h
	EnvelopeBase.h
	EnvelopeBasic.h
	Envelopes_fwd.h
	FusionCurry.h
	FusionType.h
	MessageCollection.h
	MessageType.h
	MessageTypeWithContext_fwd.h
	MessageTypeWithContext.h
	SendMessage.h
	Sizeof_fwd.h
	Sizeof.h
	TransmissionBase_fwd.h
	TransmissionBase.h
	TupleTransmission.h)

add_custom_target(tuple-transmission
	SOURCES
	${HEADERS})

set(HEADERS ${HEADERS} PARENT_SCOPE)
