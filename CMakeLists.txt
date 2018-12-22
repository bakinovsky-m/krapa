cmake_minimum_required(VERSION 2.8)
project(krapa C CXX)

set(src
  main.cpp
  port.cpp
  )

set(hdr
  cargo_type.hpp
  ship.hpp
  port.h
  )

add_executable(${PROJECT_NAME} ${src} ${hdr})
