macro(add_getstatus_test _TEST_NAME)
    add_executable(${_TEST_NAME}_tests
        ${_TEST_NAME}_tests.cpp)
    target_link_libraries(${_TEST_NAME}_tests
        ${GETSTATUS_LIBRARIES}
        ${GTEST_LIBRARIES}
        ${CPR_LIBRARIES})
    add_test(NAME getstatus_${_TEST_NAME}_tests COMMAND ${_TEST_NAME}_tests)
    # Group under the "tests" project folder in IDEs such as Visual Studio.
    set_property(TARGET ${_TEST_NAME}_tests PROPERTY FOLDER "tests")
    # if(WIN32)
    #     add_custom_command(TARGET ${_TEST_NAME}_tests POST_BUILD
    #                        COMMAND ${CMAKE_COMMAND} -E copy
    #                             $<TARGET_FILE_DIR:libcurl>/libcurl.dll $<TARGET_FILE_DIR:${_TEST_NAME}_tests>)
    # endif()
endmacro()

include_directories(
    ${GETSTATUS_INCLUDE_DIRS}
    ${GTEST_INCLUDE_DIRS}
    ${CPR_INCLUDE_DIRS}
    ${JSON_INCLUDE_DIRS})
    # ${CHANNEL_INCLUDE_DIRS}) need to add back in if the getstatus includes
    #                          uses <channel> as a dependency.

add_getstatus_test(fetch)
add_getstatus_test(util)
