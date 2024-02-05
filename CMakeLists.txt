cmake_minimum_required(VERSION 3.20)

project(mironov-e-a-23-18)


set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmake")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG bin.dbg)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE bin.rel)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO bin.relwithdbg)

add_subdirectory(prj.codeforces)
add_subdirectory(prj.lab)
add_subdirectory(pr.test)
