cmake_minimum_required(VERSION 2.8.7)
project(getstatuslib)

# Config for Clang? c++11 compatibility?
if(NOT ${CMAKE_VERSION} LESS 3.2)
    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
else()
    message(STATUS "Checking compiler flags for C++11 support.")
    # Set C++11 support flags for various compilers
    include(CheckCXXCompilerFlag)
    check_cxx_compiler_flag("-std=c++11" COMPILER_SUPPORTS_CXX11)
    check_cxx_compiler_flag("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
    if(COMPILER_SUPPORTS_CXX11)
        message(STATUS "C++11 is supported.")
        if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")
        else()
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
        endif()
    elseif(COMPILER_SUPPORTS_CXX0X)
        message(STATUS "C++0x is supported.")
        if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -stdlib=libc++")
        else()
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
        endif()
    else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
    endif()
endif()

# Set output to bin (probably as build/bin/)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

# Add getstatus source files
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
# Get ref to all .h and .cpp files in source directory.
# FILE(GLOB SOURCE_FILES ${GETSTATUS_INCLUDE_DIRS}/*.h ${SRC_DIR}/*.cpp)
FILE(GLOB SOURCE_FILES ${SRC_DIR}/*.cpp)

# build test option
macro(add_option OPTION_NAME OPTION_TEXT OPTION_DEFAULT)
    option(${OPTION_NAME} ${OPTION_TEXT} ${OPTION_DEFAULT})
    if(DEFINED ENV{${OPTION_NAME}})
        # Allow setting the option through an environment variable
        set(${OPTION_NAME} $ENV{${OPTION_NAME}})
    endif()
    if(${OPTION_NAME})
        add_definitions(-D${OPTION_NAME})
    endif()
    message(STATUS "  ${OPTION_NAME}: ${${OPTION_NAME}}")
endmacro()

# Add build test option flag
add_option(BUILD_GETSTATUS_TESTS "Set to ON to build ghost tests." ON)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

# This seems ineffectual (original value was `getstatus` but perhaps project name interference?)
set(GETSTATUS_LIBRARIES ${PROJECT_NAME} CACHE INTERNAL "")
set(GETSTATUS_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include CACHE INTERNAL "")

# Add subdirectories to build
add_subdirectory(opt)
add_subdirectory(src)
if (BUILD_GETSTATUS_TESTS)    
    add_subdirectory(test)
endif()

# Build main executable as `getstatus` program
set(PROGRAM_NAME getstatus)

add_executable(${PROGRAM_NAME} ${SOURCE_FILES})

include_directories(${GETSTATUS_INCLUDE_DIRS}
    ${CPR_INCLUDE_DIRS}
    ${JSON_INCLUDE_DIRS}
    ${CHANNEL_INCLUDE_DIRS})

target_link_libraries(${PROGRAM_NAME}
    ${CPR_LIBRARIES})
