# CMake entry point
cmake_minimum_required (VERSION 2.6)
project (Huffman)

set(LIBSRC Utils)

add_library(huffman SHARED ${LIBSRC}/huffman.cc)
add_library(auxiliar SHARED ${LIBSRC}/auxiliar.cc)

add_executable(Huffman
  main.cc
  Utils/auxiliar.cc
  Utils/huffman.cc
  )
