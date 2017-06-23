# CMake entry point
cmake_minimum_required (VERSION 3.1)
set (CMAKE_CXX_STANDARD 11)
project (Huffman)

set(LIBSRC Utils)

add_library(huffman SHARED ${LIBSRC}/huffman.cc)
add_library(auxiliar SHARED ${LIBSRC}/auxiliar.cc)

add_executable(Huffman
  main.cc
  Utils/auxiliar.cc
  Utils/huffman.cc
  )
