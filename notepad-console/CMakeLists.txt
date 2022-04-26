# CMakeList.txt : CMake project for notepad-console, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (notepad-console "notepad-console.cpp" "notepad-console.h"  "file/file.cpp" "file/file.h"  "utils/util.h")

# TODO: Add tests and install targets if needed.
