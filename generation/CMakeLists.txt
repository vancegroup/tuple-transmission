find_program(LUA_EXECUTABLE NAMES lua lua51 lua5.1)

set(GENERATION_DATAFILES
	DeserializedOverloads.gen.lua)
set(SCRIPTS
	query.lua
	variadicGenerate.lua)
if(LUA_EXECUTABLE)
	set(OUTDIR "${CMAKE_CURRENT_SOURCE_DIR}/../tuple-transmission")
	foreach(script ${SCRIPTS})
		# Re-cmake if the script changes.
		configure_file("${CMAKE_CURRENT_SOURCE_DIR}/${script}" "${CMAKE_CURRENT_BINARY_DIR}/${script}" COPYONLY)
	endforeach()

	set(script variadicGenerate.lua)
	set(OUTPUTS)
	foreach(datafile ${GENERATION_DATAFILES})
		# Re-cmake if the data changes, since that might change the outfile
		configure_file("${CMAKE_CURRENT_SOURCE_DIR}/${datafile}" "${CMAKE_CURRENT_BINARY_DIR}/${datafile}" COPYONLY)

		# Determine the output file
		execute_process(COMMAND ${LUA_EXECUTABLE} "${CMAKE_CURRENT_SOURCE_DIR}/query.lua" outFile "${CMAKE_CURRENT_BINARY_DIR}/${datafile}"
			OUTPUT_VARIABLE outfile
			RESULT_VARIABLE res
			OUTPUT_STRIP_TRAILING_WHITESPACE)

		if(res EQUAL 0)
			# Create the command
			add_custom_command(OUTPUT "${OUTDIR}/${outfile}"
				COMMAND
				"${LUA_EXECUTABLE}"
				"${CMAKE_CURRENT_SOURCE_DIR}/${script}"
				"${CMAKE_CURRENT_SOURCE_DIR}/${datafile}"
				"${script} on input ${datafile}" > "${OUTDIR}/${outfile}"
				MAIN_DEPENDENCY
				"${CMAKE_CURRENT_SOURCE_DIR}/${datafile}"
				DEPENDS
				"${CMAKE_CURRENT_SOURCE_DIR}/${script}"
				COMMENT
				"Generating ${outfile}"
				VERBATIM)
			list(APPEND OUTPUTS "${OUTDIR}/${outfile}")
		endif()
	endforeach()
	if(OUTPUTS)
		add_custom_target(regenerate-headers
			DEPENDS ${OUTPUTS}
			SOURCES ${GENERATION_DATAFILES}	${SCRIPTS})
	endif()

endif()
