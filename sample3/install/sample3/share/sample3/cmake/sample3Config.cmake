# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_sample3_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED sample3_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(sample3_FOUND FALSE)
  elseif(NOT sample3_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(sample3_FOUND FALSE)
  endif()
  return()
endif()
set(_sample3_CONFIG_INCLUDED TRUE)

# output package information
if(NOT sample3_FIND_QUIETLY)
  message(STATUS "Found sample3: 0.0.0 (${sample3_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'sample3' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${sample3_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(sample3_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${sample3_DIR}/${_extra}")
endforeach()
