# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_sample4_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED sample4_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(sample4_FOUND FALSE)
  elseif(NOT sample4_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(sample4_FOUND FALSE)
  endif()
  return()
endif()
set(_sample4_CONFIG_INCLUDED TRUE)

# output package information
if(NOT sample4_FIND_QUIETLY)
  message(STATUS "Found sample4: 0.0.0 (${sample4_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'sample4' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${sample4_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(sample4_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${sample4_DIR}/${_extra}")
endforeach()
