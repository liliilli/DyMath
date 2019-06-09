cmake_minimum_required (VERSION 3.8)
project(DyMath LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQAUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_VERBOSE_MAKEFILE true)

OPTION(MATH_BUILD_LIB "Build as library" OFF)
OPTION(MATH_BUILD_WITH_BOOST "Build with boost" OFF)
if (${UTIL_BUILD_WITH_MT} STREQUAL "ON")
	OPTION(MATH_BUILD_WITH_MT "Build as MTd or MT" ON)
else()
	OPTION(MATH_BUILD_WITH_MT "Build as MTd or MT" OFF)
endif()

# If GNU or Clang, Add common/debug/release flags.
if(GNU)
	set(CMAKE_CXX_FLAGS_COMMON	"-std=c++17 -Wall -Werror -pedantic")
	set(CMAKE_CXX_FLAGS_DEBUG	"-g -O0 -pg")
	set(CMKAE_CXX_FLAGS_RELEASE "-s -O2 -DNDEBUG -march=native")
endif(GNU)
if(Clang)
	set(CMAKE_CXX_FLAGS_COMMON	"-std=c++17 -Wall -Werror -pedantic")
	set(CMAKE_CXX_FLAGS_DEBUG	"-g -O0 -pg")
	set(CMKAE_CXX_FLAGS_RELEASE "-s -O2 -DNDEBUG -march=native")
endif(Clang)
if(MSVC)
	set(CMAKE_CXX_FLAGS_COMMON	"/std:c++17 /WX /MP")
endif(MSVC)

# If MSVC, Convert MD and MDd to MT and MTd.
if(${MATH_BUILD_WITH_MT} STREQUAL "ON")
	if (MSVC)
		set(CompilerFlags
			CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
			CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE
		)
		if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
			foreach(CompilerFlag ${CompilerFlags}) 
			string(REPLACE "/MDd" "/MTd" ${CompilerFlag} "${${CompilerFlag}}")
			endforeach()
		elseif (${CMAKE_BUILD_TYPE} STREQUAL "Release")
			foreach(CompilerFlag ${CompilerFlags}) 
			string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
			endforeach()
		else()
			message(FATAL_ERROR "Unexpected error branch.")
		endif()
	endif(MSVC)
endif(${MATH_BUILD_WITH_MT} STREQUAL "ON")

# Find files
file(GLOB_RECURSE INCLUDE RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/Include" "*.h")
file(GLOB_RECURSE INLINE RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/Include" "*.inl")
file(GLOB_RECURSE SOURCE RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/Source" "*.cc")

if (MATH_BUILD_LIB)
	message(STATUS "BUild DyMath as library file...")
	if (MATH_BUILD_WITH_BOOST)
		message(STATUS "Build DyMath with boost...")
		set(SOURCE
			Source/Math/Type/Micellanous/DUuid.cc
			Source/Utility/XBoost.cc
		)
	else()
		message(FATAL_ERROR "MATH_BUILD_WITH_BOOST flag must be enabled.")
	endif()
endif()

# Set static library setting.
include_directories("./Include")
if (${MATH_BUILD_WITH_BOOST} STREQUAL "ON")
	set (Boost_DETAILED_FAILURE_MSG ON)
	if (WIN32)
		set (BOOST_ROOT "C:/boost")
	elseif (UNIX AND NOT APPLE)
		set (BOOST_ROOT "/usr/include")
	endif()
	if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
		set (BOOST_DEBUG ON)
	elseif (${CMAKE_BUILD_TYPE} STREQUAL "DEBUG")
		set (BOOST_DEBUG ON)
	endif()

	find_package(Boost)
	if (Boost_FOUND)
		message(STATUS "Found boost library ${Boost_VERSION}")
		include_directories("${Boost_INCLUDE_DIRS}")
	else()
		message(FATAL_ERROR "Could not find boost library on ${BOOST_ROOT}.")
	endif()
endif()

# Add library with include files.
if (${MATH_BUILD_LIB} STREQUAL "ON")
	if (MATH_BUILD_WITH_BOOST)
		add_library(DyMath STATIC ${SOURCE})
		target_include_directories(DyMath
		PRIVATE
			${CMAKE_CURRENT_SOURCE_DIR}/Include
			${Boost_INCLUDE_DIRS}
		)
	else()
		add_library(DyMath STATIC)
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

	# If compiler is GNUC, set flags following CMAKE variables.
	message(STATUS "Build ${PROJECT_NAME} with ${CMAKE_CXX_COMPILER_ID} as ${CMAKE_BUILD_TYPE} mode...")
	if (GNU)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_COMMON}")
		if (${CMAKE_BUILD_TYPE} STREQUAL "DEBUG")
			set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG}")
		elseif (${CMAKE_BUILD_TYPE} STREQUAL "RELEASE")
			set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMKAE_CXX_FLAGS_RELEASE}")
		else()
			message(FATAL_ERROR "CMAKE_BUILD_TYPE is not specified. Failed to build.")
		endif()
	elseif (MSVC)
		# Warning level 4 as warning to error.
		# Enable Multiple core building.
		# Force to always compile with W4
		if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
			string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
		else()
			set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
		endif()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_COMMON}")
	endif()
else()
	add_library(${PROJECT_NAME} INTERFACE)
endif()

