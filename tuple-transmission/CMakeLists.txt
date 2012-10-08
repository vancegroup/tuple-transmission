set(HEADERS
	detail/bases/EnvelopeBase_fwd.h
	detail/bases/EnvelopeBase.h
	detail/bases/ReceiveAdapterBase.h
	detail/bases/ReceiveAdapterBase_fwd.h
	detail/bases/SerializerBase.h
	detail/bases/TransmitterBase_fwd.h
	detail/bases/TransmitterBase.h

	detail/constants/ControlCodes.h
	detail/constants/MessageBufferSizeScale.h

	detail/operations/ComputeFieldOffsets.h
	detail/operations/ComputeReceiveBufferSize.h
	detail/operations/DeserializeAndInvoke.h
	detail/operations/DeserializeDirectly.h
	detail/operations/DeserializeToFusion.h
	detail/operations/IsIdValid.h
	detail/operations/MaxMessageLength.h
	detail/operations/MessageArity.h
	detail/operations/MessageCount_fwd.h
	detail/operations/MessageCount.h
	detail/operations/MessageLength.h
	detail/operations/SerializedFieldSize_fwd.h
	detail/operations/SerializedFieldSize.h
	detail/operations/Sizeof_fwd.h
	detail/operations/Sizeof.h

	detail/types/EnvelopeReceiveBuffer.h
	detail/types/IntegralTypes.h
	detail/types/MessageIdType.h
	detail/types/MessageSizeType_fwd.h
	detail/types/MessageSizeType.h

	envelopes/BasicChecksum.h
	envelopes/Basic.h
	envelopes/Envelopes_fwd.h

	BoundMessageType_fwd.h
	BoundMessageType.h
	MessageCollection.h
	MessageType.h
	Receiver.h
	Send.h

	serializers/BitwiseCopySerialization.h

	transmitters/AutosizedBoostArrayBuffer.h
	transmitters/BoostArrayBuffer.h
	transmitters/ChecksumComputer.h
	transmitters/TransmitterComposition.h
	transmitters/VectorBuffer.h
)

set(GENERATED_HEADERS
	detail/constants/ArityConfig.h
	detail/operations/DeserializeOverloads_Generated.h
	detail/operations/SendOverloads_Generated.h
	PartialHandlerBase.h
)

# These headers have extra dependencies we probably don't satisfy, but they're
# useful to keep in this tree.
set(INTEGRATION_HEADERS
	integration/ArduinoStreamReceiveHelper.h
	receiveadapters/VrpnSerial.h
	transmitters/ArduinoI2C.h
	transmitters/ArduinoSerial.h
	transmitters/VrpnSerial.h
)

add_custom_target(tuple-transmission
	ALL
	SOURCES
	${HEADERS}
	${GENERATED_HEADERS}
	${INTEGRATION_HEADERS})

if(TARGET regenerate-headers)
	add_dependencies(tuple-transmission regenerate-headers)
endif()

set(HEADERS ${HEADERS} ${GENERATED_HEADERS} PARENT_SCOPE)

###
# Check to ensure we have all headers listed
###
file(GLOB_RECURSE globbed_headers RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" *.h)
list(REMOVE_ITEM globbed_headers ${HEADERS} ${GENERATED_HEADERS} ${INTEGRATION_HEADERS})
list(LENGTH globbed_headers num_unknown_headers)
if(num_unknown_headers GREATER 0)
	message(FATAL_ERROR "The following headers are present in the file system, but missing in the build system: ${globbed_headers}")
endif()

