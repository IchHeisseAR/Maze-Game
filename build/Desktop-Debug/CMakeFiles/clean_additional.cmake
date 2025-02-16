# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/Mazegame_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/Mazegame_autogen.dir/ParseCache.txt"
  "Mazegame_autogen"
  )
endif()
