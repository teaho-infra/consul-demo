cmake_minimum_required(VERSION 3.22.1)
project(ppconsul_demo)

set(CMAKE_CXX_STANDARD 11)

set (DEPS_DIR ${CMAKE_SOURCE_DIR}/deps)

find_library(LIBRT rt)
find_package(OpenSSL REQUIRED)
set(WORKFLOW_LIB workflow pthread OpenSSL::SSL OpenSSL::Crypto ${LIBRT})

set (WORKFLOW_DIR ${DEPS_DIR}/workflow)
include_directories(${WORKFLOW_DIR}/include)
find_library(WORKFLOW libworkflow.a ${WORKFLOW_DIR}/lib)
link_directories(${WORKFLOW_DIR}/lib)

set (PPCONSUL_DIR ${DEPS_DIR}/ppconsul)
include_directories(${PPCONSUL_DIR}/include)
find_library(PPCONSUL libppconsul.so ${PPCONSUL_DIR}/lib)



add_executable(server_demo serverMain.cpp)
target_link_libraries(server_demo PRIVATE
        ppconsul
        ${WORKFLOW_LIB})

add_executable(client_discovery_demo clientDiscoveryMain.cpp)
target_link_libraries(client_discovery_demo PRIVATE
        ppconsul
        ${WORKFLOW_LIB})

