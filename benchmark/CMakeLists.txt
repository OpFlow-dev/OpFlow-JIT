# ----------------------------------------------------------------------------
#
# Copyright (c) 2019 - 2021 by the OpFlow developers
#
# This file is part of OpFlow-JIT.
#
# OpFlow is free software and is distributed under the Apache-2.0 license.
# The full text of the license can be found in the file LICENSE at the top
# level directory of OpFlow-JIT.
#
# ----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.10)
project(OpFlow_Benchmarks)

if (NOT TARGET OpFlow-JIT)
    find_package(OpFlow-JIT REQUIRED)
endif ()

find_package(benchmakr REQUIRED CONFIG)

add_custom_target(AllBenchmarks)

function(add_bench name)
    add_executable(BENCH_${name} EXCLUDE_FROM_ALL ${ARGN})
    target_link_libraries(BENCH_${name} OpFlow::OpFlow-JIT benchmark::benchmark)
    add_dependencies(AllBenchmarks BENCH_${name})
endfunction()

add_dependencies(All_CI AllBenchmarks)