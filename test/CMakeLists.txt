# ----------------------------------------------------------------------------
#
# Copyright (c) 2019 - 2024 by the OpFlow developers
#
# This file is part of OpFlow-JIT.
# 
# OpFlow is free software and is distributed under the Apache-2.0 license.
# The full text of the license can be found in the file LICENSE at the top
# level directory of OpFlow-JIT.
#
# ----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.10)
project(OpFlow_Tests)

if (NOT TARGET OpFlow-JIT)
    find_package(OpFlow-JIT REQUIRED)
endif ()

if (OPFLOW_ENABLE_COVERAGE)
    include(${CMAKE_CURRENT_LIST_DIR}/../cmake/CodeCoverage.cmake)
else ()
    function(SETUP_TARGET_FOR_COVERAGE)
    endfunction()
endif ()

#define_property(GLOBAL PROPERTY all_test_srcs)
set_property(GLOBAL PROPERTY all_test_srcs)

add_custom_target(AllTests)

# Find google test
find_package(GTest REQUIRED CONFIG)

function(add_gmock testname testfile)
    add_executable(${testname} EXCLUDE_FROM_ALL ${testfile} ${ARGN} ${CMAKE_SOURCE_DIR}/test/test_main.cpp)
    target_link_libraries(${testname} GTest::gmock OpFlow::OpFlow-JIT)
    target_compile_definitions(${testname} PUBLIC OPFLOW_TEST_ENVIRONMENT)
    set_property(GLOBAL APPEND PROPERTY all_test_srcs ${testfile} ${ARGN})
    add_dependencies(AllTests ${testname})
    if (NOT ${testname} STREQUAL "UniTests")
        add_test(NAME ${testname} COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${testname})
    endif ()
    if (${CMAKE_BUILD_TYPE} STREQUAL "Debug" AND OPFLOW_ENABLE_CONVERAGE)
        target_link_libraries(${testname} gcov)
        target_compile_options(${testname} PRIVATE $<$<CXX_COMPILER_ID:GNU>:--coverage>
                PRIVATE $<$<CXX_COMPILER_ID:GNU>:-fconcepts-diagnostics-depth=5>
                PRIVATE $<$<CXX_COMPILER_ID:Clang>:-fprofile-instr-generate -fcoverage-mapping>)
        SETUP_TARGET_FOR_COVERAGE(${testname}_coverage ${testname} ${testname}_coverage)
    endif ()
endfunction()

include_directories(${CMAKE_CURRENT_BINARY_DIR})
if (NOT CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")
endif ()

add_subdirectory(lang)

# Add global tests target
get_property(all_test_srcs_list GLOBAL PROPERTY all_test_srcs)
list(REMOVE_DUPLICATES all_test_srcs_list)
#add_gmock(UniTests ${all_test_srcs_list})

add_dependencies(All_CI AllTests)