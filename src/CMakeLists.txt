message("src/GETSTATUS_INCLUDE_DIRS ${GETSTATUS_INCLUDE_DIRS}")
message("src/GETSTATUS_LIBARIES ${GETSTATUS_LIBARIES} ${PROJECT_NAME}")

add_library(${PROJECT_NAME}#${GETSTATUS_LIBARIES}
# add_library(abc#${PROJECT_NAME}#getstatus #${GETSTATUS_LIBARIES}

    commit.cpp
    gitlab-api.cpp

    ${GETSTATUS_INCLUDE_DIRS}/commit.h
    ${GETSTATUS_INCLUDE_DIRS}/gitlab-api.h
    ${GETSTATUS_INCLUDE_DIRS}/url.h
    ${GETSTATUS_INCLUDE_DIRS}/util.h)

    include_directories(
        ${GETSTATUS_INCLUDE_DIRS}
        ${CPR_INCLUDE_DIRS}
        ${JSON_INCLUDE_DIRS})

target_link_libraries(${GETSTATUS_LIBARIES}
    ${CPR_LIBRARIES})
