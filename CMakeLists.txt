cmake_minimum_required(VERSION 2.8)

set(src
  main.cpp
  )

set(hdr
  cargo_type.hpp
  ship.hpp
  )

project(krapa)
add_executable(${PROJECT_NAME} ${src} ${hdr})
