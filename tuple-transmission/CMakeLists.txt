set(HEADERS
	detail/bases/EnvelopeBase_fwd.h
	detail/bases/EnvelopeBase.h
	detail/bases/SerializerBase.h
	detail/bases/TransmissionBase_fwd.h
	detail/bases/TransmissionBase.h
	detail/bases/TransmitterBase_fwd.h
	detail/bases/TransmitterBase.h

	detail/constants/ControlCodes.h
	detail/constants/MessageBufferSizeScale.h

	detail/operations/ComputeReceiveBufferSize.h
	detail/operations/IsIdValid.h
	detail/operations/MaxMessageLength.h
	detail/operations/MessageCount_fwd.h
	detail/operations/MessageCount.h
	detail/operations/MessageLength.h
	detail/operations/Sizeof_fwd.h
	detail/operations/Sizeof.h

	detail/types/IntegralTypes.h
	detail/types/MessageCollectionTypes.h
	detail/types/MessageIdType_fwd.h
	detail/types/MessageIdType.h
	detail/types/MessageSizeType_fwd.h
	detail/types/MessageSizeType.h

	envelopes/BasicChecksum.h
	envelopes/Basic.h
	envelopes/Envelopes_fwd.h

	MessageCollection.h
	MessageType.h
	ReceiveHandler.h
	Send.h
	Transmission_fwd.h
	Transmission.h

	serializers/BitwiseCopySerialization.h

	transmitters/AutosizedBoostArrayBuffer.h
	transmitters/BoostArrayBuffer.h
	transmitters/ChecksumComputer.h
	transmitters/TransmitterComposition.h
)

add_custom_target(tuple-transmission
	SOURCES
	${HEADERS}
	${DETAIL_HEADERS})

set(HEADERS ${HEADERS} ${DETAIL_HEADERS} PARENT_SCOPE)
