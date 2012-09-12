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
	detail/operations/DeserializeAndInvoke.h
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
	Receive.h
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

set(GENERATED_HEADERS
	detail/operations/DeserializeOverloads_Generated.h
)


add_custom_target(tuple-transmission
	SOURCES
	${HEADERS}
	${GENERATED_HEADERS})

set(HEADERS ${HEADERS} ${GENERATED_HEADERS} PARENT_SCOPE)

###
# Check to ensure we have all headers listed
###
file(GLOB_RECURSE globbed_headers RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" *.h)
list(REMOVE_ITEM globbed_headers ${HEADERS} ${GENERATED_HEADERS})
list(LENGTH globbed_headers num_unknown_headers)
if(num_unknown_headers GREATER 0)
	message(FATAL_ERROR "The following headers are present in the file system, but missing in the build system: ${globbed_headers}")
endif()

