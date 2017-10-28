# - getstatus, GitLab API fetcher
# This module is a GitLab API wrapper and program in C++
#
# Finding this module will define the folowing variables:
#  GETSTATUS_FOUND
#  GETSTATUS_LIBRARIES
#  GETSTATUS_INCLUDE_DIRS

find_path(GETSTATUS_INCLUDE_DIR
          NAMES gitlab-api.h commit.h url.h util.h)

find_library(GETSTATUS_LIBRARY
             NAMES getstatuslib
             HINTS ${GETSTATUS_LIBRARY_ROOT})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GETSTATUS REQUIRED_VARS GETSTATUS_LIBRARY GETSTATUS_INCLUDE_DIR)

if(GETSTATUS_FOUND)
    set(GETSTATUS_LIBRARIES ${GETSTATUS_LIBRARY})
    set(GETSTATUS_INCLUDE_DIRS ${GETSTATUS_INCLUDE_DIR})
endif()
