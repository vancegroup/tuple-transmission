
add_boost_test(TupleTransmission
	SOURCES
	TupleTransmission.cpp
#	TESTS
	)


add_boost_test(Sizeof
	SOURCES
	Sizeof.cpp
	TESTS
	SizeofRefactored
	SizeofMessageVsTypelist
	WholeMessageSize
	WholeMessageSizeDirectConstruction)

add_subdirectory(cleanbuild)
