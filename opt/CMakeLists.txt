# Cache variable for accessing in other directory scopes.
macro(set_cache_variable VAR_NAME VAR_DESCRIPTION)
    set(${VAR_NAME} ${${VAR_NAME}} CACHE INTERNAL ${VAR_DESCRIPTION})
    message(STATUS "Set ${VAR_NAME} to ${${VAR_NAME}}.")
endmacro()

# Set include directories for projects without `CMakeLists.txt`
set(JSON_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/json/src PARENT_SCOPE)
set(CHANNEL_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/channel/include PARENT_SCOPE)

if(WIN32)
    option(CMAKE_USE_OPENSSL "Use OpenSSL code. Experimental" OFF)
endif()

set(BUILD_CPR_TESTS OFF CACHE BOOL "Don't build cpr tests")
find_package(CURL)
if(CURL_FOUND)
    set(USE_SYSTEM_CURL ON CACHE BOOL "Use the system curl for faster builds")
endif()
add_subdirectory(cpr)
# find_package(cpr REQUIRED)

# Conditionally add testing library.
if(BUILD_GETSTATUS_TESTS)
# No idea what this commented out stuff below really does.
#     if(USE_SYSTEM_GTEST)
#         find_package(GTest)
#     endif()
#     if(NOT USE_SYSTEM_GTEST OR NOT GTEST_FOUND)
#         message(STATUS "Not using system gtest, using built-in googletest project instead.")
#         if(MSVC)
#             # By default, GTest compiles on Windows in CRT static linkage mode. We use this
#             # variable to force it into using the CRT in dynamic linkage (DLL), just as CPR
#             # does.
#             set(gtest_force_shared_crt ON CACHE BOOL "Force gtest to use the shared c runtime")
#         endif()
    message("using tests")
    add_subdirectory(googletest)
    set(GTEST_FOUND TRUE)
    set(GTEST_LIBRARIES gtest)
    set(GTEST_MAIN_LIBRARIES gtest_main)
    set(GTEST_BOTH_LIBRARIES gtest gtest_main)
    set(GTEST_INCLUDE_DIRS ${gtest_SOURCE_DIR}/include)
        
        # Comment out as I'm not using Visual Studio.
        # Group under the "tests/gtest" project folder in IDEs such as Visual Studio.
        # set_property(TARGET gtest PROPERTY FOLDER "tests/gtest")
        # set_property(TARGET gtest_main PROPERTY FOLDER "tests/gtest")
    # endif() // matches above commented out conditional

    set_cache_variable(GTEST_FOUND "Set if libgtest was found or built")
    set_cache_variable(GTEST_LIBRARIES "Location of libgtest")
    set_cache_variable(GTEST_MAIN_LIBRARIES "Location of libgtest-main")
    set_cache_variable(GTEST_BOTH_LIBRARIES "Location of both gtest libraries")
    set_cache_variable(GTEST_INCLUDE_DIRS "Location of gtest include files")
endif()
