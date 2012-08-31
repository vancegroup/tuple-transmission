set(HEADERS
	Sizeof.h
	TupleTransmission.h)

add_custom_target(tuple-transmission
	SOURCES
	${HEADERS})

set(HEADERS ${HEADERS} PARENT_SCOPE)
