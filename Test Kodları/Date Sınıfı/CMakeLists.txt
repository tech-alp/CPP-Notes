cmake_minimum_required(VERSION 3.10)

project(Test-Kodları)

set(PROJECT_HEADERS 
            ${CMAKE_SOURCE_DIR}/date.h
    )

set(PROJECT_SOURCES 
            ${CMAKE_SOURCE_DIR}/../src/main.cpp
            ${CMAKE_SOURCE_DIR}/date.cpp
            )

add_library(datelib ${PROJECT_SOURCES} ${PROJECT_HEADERS})

            
add_executable(datelib ${PROJECT_SOURCES})