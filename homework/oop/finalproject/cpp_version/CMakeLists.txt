cmake_minimum_required(VERSION 3.10)

project(ExpressManager)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB SOURCES 
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

file(GLOB HEADERS 
    "${PROJECT_SOURCE_DIR}/include/*.h"
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})