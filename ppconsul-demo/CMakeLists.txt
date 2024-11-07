cmake_minimum_required(VERSION 3.22.1)
project(ppconsul_demo)

set(CMAKE_CXX_STANDARD 11)

set (DEPS_DIR ${CMAKE_SOURCE_DIR}/deps)
set (WORKFLOW_DIR ${DEPS_DIR}/workflow)
include_directories(${WORKFLOW_DIR}/include)
find_library(WORKFLOW libworkflow.so ${WORKFLOW_DIR}/lib)

set (PPCONSUL_DIR ${DEPS_DIR}/ppconsul)
include_directories(${PPCONSUL_DIR}/include)
find_library(PPCONSUL libppconsul.so ${PPCONSUL_DIR}/lib)



add_executable(ppconsul_demo main.cpp)

target_link_libraries(ppconsul_demo PRIVATE
        ppconsul
        workflow)
