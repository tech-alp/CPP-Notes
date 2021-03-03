cmake_minimum_required(VERSION 3.0.0)

project(class_tests)

set(PROJECT_DIR ${CMAKE_SOURCE_DIR})

set(PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

set(PROJECT_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

set(PROJECT_HEADERS 
            ${PROJECT_INCLUDE_DIR}/mint.h
            ${PROJECT_INCLUDE_DIR}/myarray.h
            ${PROJECT_INCLUDE_DIR}/counter.h
            ${PROJECT_INCLUDE_DIR}/counterptr.h)

set(PROJECT_SOURCES 
            ${PROJECT_SOURCE_DIR}/main.cpp
            ${PROJECT_SOURCE_DIR}/mint.cpp
            ${PROJECT_SOURCE_DIR}/myarray.cpp
            )

add_library(mylib ${PROJECT_SOURCES} ${PROJECT_HEADERS})

include_directories(${PROJECT_INCLUDE_DIR})
            
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

