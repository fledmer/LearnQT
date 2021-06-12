# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\Counter2_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Counter2_autogen.dir\\ParseCache.txt"
  "Counter2_autogen"
  )
endif()
