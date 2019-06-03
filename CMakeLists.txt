cmake_minimum_required (VERSION 3.8)
project(DyMath LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQAUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_VERBOSE_MAKEFILE true)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	# Do something 
endif()
if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
	# Do something 
endif()

# Find files
file(GLOB_RECURSE INCLUDE RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/Include" "*.h")
file(GLOB_RECURSE INLINE RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/Include" "*.inl")
file(GLOB_RECURSE SOURCE RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/Source" "*.cc")

OPTION(MATH_BUILD_WITH_BOOST "Build with boost" OFF)
OPTION(MATH_BUILD_LIB "Build as library" OFF)

if (MATH_BUILD_LIB)
	message(STATUS "BUild DyMath as library file...")
	if (MATH_BUILD_WITH_BOOST)
		message(STATUS "Build DyMath with boost...")
		set(SOURCE
			Source/Math/Type/Micellanous/DUuid.cc
			Source/Utility/XBoost.cc
		)
	else()
		set(SOURCE "")
	endif()
endif()

# https://stackoverflow.com/questions/2110795/how-to-use-all-c-files-in-a-directory-with-the-cmake-build-system
# AUX_SOURCE_DIRECTORY("${CMAKE_CURRENT_SOURCE_DIR}/Source" SOURCE)

# Set static library setting.
include_directories("./Include")
if (MATH_BUILD_WITH_BOOST)
	set (Boost_DETAILED_FAILURE_MSG ON)
	if (WIN32)
		set (BOOST_ROOT "C:/boost")
	endif()
	set (BOOST_DEBUG ON)

	find_package(Boost)
	if (Boost_FOUND)
		message(STATUS "Found boost library ${Boost_VERSION}")
		include_directories("${Boost_INCLUDE_DIRS}")
	else()
		message(FATAL_ERROR "Could not find boost library.")
	endif()
endif()

# Add library with include files.
if (MATH_BUILD_LIB)
	add_library(DyMath STATIC ${SOURCE})
	if (MATH_BUILD_WITH_BOOST)
		target_include_directories(DyMath
		PRIVATE
			${CMAKE_CURRENT_SOURCE_DIR}/Include
			${Boost_INCLUDE_DIRS}
		)
	else()
		target_include_directories(DyMath
		PRIVATE
			${CMAKE_CURRENT_SOURCE_DIR}/Include
		)
	endif()

	# Add dependencies.
	# ADD_DEPENDENCIES(DyMath DyExpression)
	set_target_properties(DyMath PROPERTIES 
		LINKER_LANGUAGE CXX
		OUTPUT_NAME "DyMath"
	)
	target_include_directories(DyMath PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

	# Bind groups
	source_group("Inline" FILES ${INLINE})
	source_group("Include" FILES ${INCLUDE})

	# Install Settings
	set_target_properties(DyMath
		PROPERTIES
		ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}\\lib\\${CMAKE_BUILD_TYPE}"
		LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}\\lib\\${CMAKE_BUILD_TYPE}"
		RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}\\bin\\${CMAKE_BUILD_TYPE}"
	)

	if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
		message(STATUS "Build ${PROJECT_NAME} with ${CMAKE_CXX_COMPILER_ID}...")
		# Warning level 4 as warning to error.
		# Enable Multiple core building.
		# Force to always compile with W4
		if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
			string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
		else()
			set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
		endif()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX /MP")
	endif()
endif()

