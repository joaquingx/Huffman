# CMake entry point
cmake_minimum_required (VERSION 2.6)
project (Huffman)


add_definitions(
  -DTW_STATIC
  -DTW_NO_LIB_PRAGMA
  -DTW_NO_DIRECT3D
  -DGLEW_STATIC
  -D_CRT_SECURE_NO_WARNINGS
  )

set(LIBSRC Utils)

add_library(huffman SHARED ${LIBSRC}/huffman.cc)
add_library(auxiliar SHARED ${LIBSRC}/auxiliar.cc)

set(ALL_LIBS
  huffman
  auxiliar
  )

add_executable(Huffman
  main.cc
  Utils/auxiliar.cc
  Utils/huffman.cc
  )
target_link_libraries(Huffman
  ${ALL_LIBS}
  )
