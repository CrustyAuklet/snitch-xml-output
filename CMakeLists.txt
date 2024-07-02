cmake_minimum_required(VERSION 3.28)
project(test_output)

set(CPM_snitch_SOURCE "E:/wildlife/nextgen/snitch")
set(CPM_USE_NAMED_CACHE_DIRECTORIES ON)
include(cmake/CPM.cmake)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

CPMAddPackage(NAME Catch2
              GITHUB_REPOSITORY catchorg/Catch2
              VERSION 3.6.0
              SYSTEM ON
)
CPMAddPackage(NAME snitch
              GITHUB_REPOSITORY CrustyAuklet/snitch
              VERSION 1.2.5
              GIT_TAG feat/catch2-compat
              SYSTEM ON
)

macro(add_test test_name)
    add_executable(${test_name}_snitch ${test_name}.cpp)
    target_link_libraries(${test_name}_snitch PRIVATE snitch::snitch)
    target_include_directories(${test_name}_snitch PUBLIC ${CMAKE_SOURCE_DIR})

    add_executable(${test_name}_catch2 ${test_name}.cpp)
    target_link_libraries(${test_name}_catch2 PRIVATE Catch2::Catch2WithMain)
    target_compile_definitions(${test_name}_catch2 PUBLIC TESTING_USE_CATCH2)
    target_include_directories(${test_name}_catch2 PUBLIC ${CMAKE_SOURCE_DIR})
endmacro()

add_test(all_pass)
add_test(all_fail)
add_test(exceptions)
