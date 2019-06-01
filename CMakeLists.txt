cmake_minimum_required (VERSION 3.8)
project(DyMath LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQAUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set (CMAKE_VERBOSE_MAKEFILE true)

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

set(SOURCE
	Source/Math/Type/Micellanous/DUuid.cc
	Source/Utility/XBoost.cc
)

# https://stackoverflow.com/questions/2110795/how-to-use-all-c-files-in-a-directory-with-the-cmake-build-system
# AUX_SOURCE_DIRECTORY("${CMAKE_CURRENT_SOURCE_DIR}/Source" SOURCE)

# Set static library setting.
include_directories("./Include")
include_directories("${CMAKE_SOURCE_DIR}/ThirdParty/boost")

# Add library with include files.
add_library(DyMath STATIC ${SOURCE})
target_include_directories(DyMath
PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/Include
	${CMAKE_SOURCE_DIR}/ThridParty/boost
)

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
