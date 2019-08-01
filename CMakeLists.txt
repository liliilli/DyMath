cmake_minimum_required (VERSION 3.8)
project(DyMath LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQAUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_VERBOSE_MAKEFILE true)

# Option list
OPTION(MATH_BUILD_LIB "Build as library" OFF)
OPTION(MATH_BUILD_WITH_EXPR "Build as DyExpression" OFF)
OPTION(MATH_BUILD_WITH_RTTR "Build with dy::expr::reflect (Refection)" OFF)
OPTION(MATH_BUILD_WITH_BOOST "Build with boost" OFF)

# Dependent option branches
if ("${UTIL_BUILD_WITH_MT}" STREQUAL "ON")
	OPTION(MATH_BUILD_WITH_MT "Build as MTd or MT" ON)
else()
	OPTION(MATH_BUILD_WITH_MT "Build as MTd or MT" OFF)
endif()

if ("${MATH_BUILD_LIB}" STREQUAL "ON")
	# Add static library
	add_library(${PROJECT_NAME} STATIC)

	# Common includes
	target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Include)
	# Common sources
	target_sources(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Source/Utility/XMath.cc)

	# Add DyExpression when enabled.
	if ("${MATH_BUILD_WITH_EXPR}" STREQUAL "ON")
		target_include_directories(${PROJECT_NAME}
		PUBLIC
			${CMAKE_CURRENT_SOURCE_DIR}/../DyExpression/Include
		)
	endif()

	# Add boost when enabled.
	if ("${MATH_BUILD_WITH_BOOST}" STREQUAL "ON")
		set (Boost_DETAILED_FAILURE_MSG ON)
		if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
			set (BOOST_DEBUG ON)
		endif()

		find_package(Boost)
		if (Boost_FOUND)
			target_include_directories(${PROJECT_NAME} PUBLIC ${Boost_INCLUDE_DIRS})
			target_compile_definitions(${PROJECT_NAME} PUBLIC MATH_ENABLE_UUID)

			# Add boost sources
			target_sources(${PROJECT_NAME}
			PUBLIC
				${CMAKE_CURRENT_SOURCE_DIR}/Source/Math/Type/Micellanous/DUuid.cc
				${CMAKE_CURRENT_SOURCE_DIR}/Source/Utility/XBoost.cc
			)
		else()
			message(FATAL_ERROR "Could not find boost library on ${BOOST_ROOT}.")
		endif()
	endif()

	# Bind groups
	source_group("Inline" FILES ${INLINE})
	source_group("Include" FILES ${INCLUDE})

	# If math library `.lib` `.so` should be built with `dy::expr::reflect`...
	if ("MATH_BUILD_WITH_RTTR" STREQUAL "ON")
		# Fatal error case.
		if (NOT MATH_BUILD_WITH_EXPR)
			message(FATAL_ERROR "To build DyMath with dy::expr::reflect, \"MATH_BUILD_WITH_EXPR\" must be enabled as a \"ON\"")
		endif()

		message(STATUS "Build DyMath with dy::expr::reflect...")

		# Set ENABLE macro.
		target_compile_definitions(${PROJECT_NAME} PUBLIC MATH_ENABLE_RTTR)
		# Bind RTTR sources.
		target_sources(${PROJECT_NAME}
		PUBLIC
			${CMAKE_CURRENT_SOURCE_DIR}/Source/Math/Common/XRttrEntry.cc
		)
	endif()

else()
	add_library(${PROJECT_NAME} INTERFACE)
	target_include_directories(DyMath INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/Include)

endif()

# If GNU, Clang or MSVC, Add common/debug/release flags.
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	set(CMAKE_CXX_FLAGS	"${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Werror -pedantic")
	set(CMAKE_CXX_FLAGS_DEBUG	"-g -O0 -pg")
	set(CMKAE_CXX_FLAGS_RELEASE "-s -O2 -DNDEBUG -march=native")

elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Werror -Wno-ignored-qualifiers -pedantic")
	set(CMAKE_CXX_FLAGS_DEBUG	"-g -O0 -pg")
	set(CMKAE_CXX_FLAGS_RELEASE "-s -O2 -DNDEBUG -march=native")

elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17 /WX /MP")

	# If MSVC, Convert MD and MDd to MT and MTd.
	if("${MATH_BUILD_WITH_MT}" STREQUAL "ON")
		set(CompilerFlags
			CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
			CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE
		)

		if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
			foreach(CompilerFlag ${CompilerFlags}) 
				string(REPLACE "/MDd" "/MTd" ${CompilerFlag} "${${CompilerFlag}}")
			endforeach()

		elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
			foreach(CompilerFlag ${CompilerFlags}) 
				string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
			endforeach()

		else()
			message(FATAL_ERROR "Unexpected error branch.")

		endif()
	endif()

	# Warning level 4 as warning to error. Force to always compile with W4
	if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
		string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
	endif()
endif()

# Install Settings
set_target_properties(${PROJECT_NAME}
	PROPERTIES
	LINKER_LANGUAGE CXX
	ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}\\lib\\${CMAKE_BUILD_TYPE}"
	LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}\\lib\\${CMAKE_BUILD_TYPE}"
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}\\bin\\${CMAKE_BUILD_TYPE}"
)

