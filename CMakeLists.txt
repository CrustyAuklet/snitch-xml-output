cmake_minimum_required(VERSION 3.28)
project(test_output)

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

set(TEST_FILES
    test.cpp
)

add_executable(test_snitch ${TEST_FILES})
target_link_libraries(test_snitch PRIVATE snitch::snitch)
target_include_directories(test_snitch PUBLIC ${CMAKE_SOURCE_DIR})

add_executable(test_catch2 ${TEST_FILES})
target_link_libraries(test_catch2 PRIVATE Catch2::Catch2WithMain)
target_compile_definitions(test_catch2 PUBLIC TESTING_USE_CATCH2)
target_include_directories(test_catch2 PUBLIC ${CMAKE_SOURCE_DIR})