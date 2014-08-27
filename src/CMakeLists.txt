project(alisp)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_C_FLAGS "--std=c11 -Wall -Wextra")
if("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")
else()
  set(CMAKE_BUILD_TYPE "Debug")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -g")
  add_definitions("-DDEBUG")
endif()


find_path(READLINE_INCLUDE_DIR readline/readline.h
  /usr/include/readline)
find_library(READLINE_LIBRARY NAMES readline)

include_directories(${READLINE_INCLUDE_DIR})
add_executable(al alisp.c input.c tokenizer.c list.c parse.c output.c)
target_link_libraries(al ${READLINE_LIBRARY})