set(HEADERS
	CreateMessage.h
	EnvelopeBasic.h
	FusionCurry.h
	FusionType.h
	MessageCollection.h
	MessageType.h
	Sizeof.h
	TransmissionBase.h
	TupleTransmission.h)

add_custom_target(tuple-transmission
	SOURCES
	${HEADERS})

set(HEADERS ${HEADERS} PARENT_SCOPE)
