add_custom_target(headercompile)
set(DIR tuple-transmission)

foreach(HEADER ${HEADERS})
	string(REPLACE ".h" "" SHORTNAME "${HEADER}")
	set(stem "test_headercompile_${SHORTNAME}")
	configure_file(test_headercompile.cpp.in "${CMAKE_CURRENT_BINARY_DIR}/${stem}.cpp" @ONLY)

	add_executable(${stem} "${CMAKE_CURRENT_BINARY_DIR}/${stem}.cpp")
	if(LIBRARIES_${SHORTNAME})
		target_link_libraries(${stem} ${LIBRARIES_${SHORTNAME}})
	endif()
	add_test(${stem}_executes ${stem})
	add_dependencies(headercompile ${stem})
endforeach()

