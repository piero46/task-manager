# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\appPR_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\appPR_autogen.dir\\ParseCache.txt"
  "appPR_autogen"
  )
endif()
