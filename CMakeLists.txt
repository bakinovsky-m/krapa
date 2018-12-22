cmake_minimum_required(VERSION 2.8)
project(krapa C CXX)


set(src
  src/main.cpp
  src/port.cpp
  )

set(hdr
  include/cargo_type.hpp
  include/ship.hpp
  include/port.h
  )

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME} ${src} ${hdr})


set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)
