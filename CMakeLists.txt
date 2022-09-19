cmake_minimum_required(VERSION 3.14)

# set the project name
project(SpaceWalk VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

configure_file(${PROJECT_SOURCE_DIR}/src/Config.h.in Config.h)

option(TEST_ROOM "Test room class of engine.h" OFF)
option(TEST_OBJECT "Test object class of engine.h" OFF)

include_directories("${PROJECT_SOURCE_DIR}/src")

macro(runtest testname)
	include(FetchContent)
	FetchContent_Declare(
		googletest
		GIT_REPOSITORY https://github.com/google/googletest.git
		GIT_TAG release-1.12.1
	)
	# For Windows: Prevent overridin the parent project's compiler/linker settings
	set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
	FetchContent_MakeAvailable(googletest)
	enable_testing()
	add_executable(test_module ${testname})
	target_link_libraries(
		test_module	
		GTest::gtest_main
	)
	include(GoogleTest)
	gtest_discover_tests(test_module)
endmacro()

macro(buildworld)
	add_executable(spacewalk src/main.cpp)
	target_include_directories(spacewalk PUBLIC
		"${PROJECT_BINARY_DIR}"
		"${PROJECT_SOURCE_DIR}"
		"${PROJECT_SOURCE_DIR}/src"
		)
endmacro()

if(TEST_ROOM)
	runtest("tests/test_room.cpp")
elseif(TEST_OBJECT)
	runtest("tests/test_object.cpp")
else()
	buildworld()
endif()