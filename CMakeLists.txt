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
#
# The main CMakeList for OpFlow-JIT
#
# ----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.20)

# ----------------------------------------------------------------------------
# Start OpFlow-JIT project
# ----------------------------------------------------------------------------
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
include(Utils)

opflow_extract_version()

project(OpFlow-JIT VERSION ${OPFLOW_VERSION} LANGUAGES C CXX)
message(STATUS "Build OpFlow-JIT: ${OPFLOW_VERSION}")

include(GNUInstallDirs)

# ----------------------------------------------------------------------------
# Set CMake policies to support later version behaviour
# ----------------------------------------------------------------------------
if (POLICY CMP0077)
    cmake_policy(SET CMP0077 NEW) # option() honors variables already set
endif ()

# ----------------------------------------------------------------------------
# Set default build to release
# ----------------------------------------------------------------------------
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose Release or Debug" FORCE)
endif ()

# ----------------------------------------------------------------------------
# Compiler config
# ----------------------------------------------------------------------------
if (NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 20)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
elseif (CMAKE_CXX_STANDARD LESS 20)
    message(WARNING "OpFlow needs C++20 to compile. Changing the standard to C++20.")
    set(CMAKE_CXX_STANDARD 20)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif ()
if (NOT CMAKE_C_STANDARD)
    set(CMAKE_C_STANDARD 99)
    set(CMAKE_C_STANDARD_REQUIRED ON)
elseif (CMAKE_C_STANDARD LESS 99)
    message(WARNING "OpFlow needs C99 to compile. Changing the standard to C99.")
    set(CMAKE_C_STANDARD 99)
    set(CMAKE_C_STANDARD_REQUIRED ON)
endif ()

# make sure __cplusplus is defined when using msvc
if (MSVC)
    string(APPEND CMAKE_CXX_FLAGS " /Zc:__cplusplus /wd4267 /wd4390 /wd4244")
endif ()

set(CMAKE_CXX_EXTENSIONS OFF)

if (CMAKE_SYSTEM_NAME MATCHES "CYGWIN" OR CMAKE_SYSTEM_NAME MATCHES "MSYS")
    set(CMAKE_CXX_EXTENSIONS ON)
endif ()

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_THREAD_LIBS_INIT "-lpthread")
    set(CMAKE_HAVE_THREADS_LIBRARY 1)
    set(CMAKE_USE_WIN32_THREADS_INIT 0)
    set(CMAKE_USE_PTHREADS_INIT 1)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
endif ()

# ----------------------------------------------------------------------------
# Set OPFLOW_MASTER_PROJECT to ON if we are building OpFlow-JIT
# ----------------------------------------------------------------------------
# Check if OpFlow-JIT is being used directly or via add_subdirectory, but allow overriding
if (NOT DEFINED OPFLOW_MASTER_PROJECT)
    if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
        set(OPFLOW_MASTER_PROJECT ON)
    else ()
        set(OPFLOW_MASTER_PROJECT OFF)
    endif ()
endif ()

option(OPFLOW_BUILD_ALL "Build all artifacts" OFF)

# example options
option(OPFLOW_BUILD_EXAMPLES "Build OpFlow's example cases" ON)

# document options
option(OPFLOW_BUILD_DOCS "Build OpFlow's document" OFF)

# testing options
option(OPFLOW_BUILD_TESTS "Build tests" OFF)
option(OPFLOW_ENABLE_COVERAGE "Enable converage" OFF)

# benchmark options
option(OPFLOW_BUILD_BENCHMARKS "Build benchmarks" OFF)

# sanitizer options
option(OPFLOW_SANITIZE_ADDRESS "Enable address sanitizer in tests" OFF)
option(OPFLOW_SANITIZE_LEAK "Enable leak sanitizer in tests" OFF)
option(OPFLOW_SANITIZE_THREAD "Enable thread sanitizer in tests" OFF)
option(OPFLOW_SANITIZE_UB "Enable undefined behavior sanitizer in tests" OFF)

# compile options
option(OPFLOW_BUILD_WARNINGS "Enable compiler warnings" OFF)
option(OPFLOW_NO_EXCEPTIONS "Compile with -fno-exceptions" OFF)
option(OPFLOW_GEN_COMPILE_COMMANDS "Generate compile_commands.json for IDE integration" ON)

# install options
option(OPFLOW_INSTALL "Generate the install target" ${OPFLOW_MASTER_PROJECT})

message(STATUS "Build type: " ${CMAKE_BUILD_TYPE})

set(CMAKE_EXPORT_COMPILE_COMMANDS ${OPFLOW_GEN_COMPILE_COMMANDS})

# ----------------------------------------------------------------------------
# Use spdlog package
# ----------------------------------------------------------------------------
find_package(spdlog REQUIRED CONFIG)
message(STATUS "Found spdlog ${spdlog_PACKAGE_VERSION}")
message(STATUS "Using spdlogConfig.cmake in ${spdlog_DIR}")

# ----------------------------------------------------------------------------
# Use MLIR package
# ----------------------------------------------------------------------------
find_package(MLIR REQUIRED CONFIG)
message(STATUS "Found MLIR ${MLIR_PACKAGE_VERSION}")
message(STATUS "Using MLIRConfig.cmake in ${MLIR_DIR}")
find_program(MLIRTG NAMES mlir-tblgen-18 mlir-tblgen)
message(STATUS "Found mlir-tblgen ${MLIRTG}")
find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
list(APPEND CMAKE_MODULE_PATH "${MLIR_CMAKE_DIR}")
list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")

# ----------------------------------------------------------------------------
# Declare the OpFlow-JIT target
# ----------------------------------------------------------------------------
add_subdirectory(src)

# ----------------------------------------------------------------------------
# All_CI target (= AllExamples + AllBenchmarks + AllTests)
# ----------------------------------------------------------------------------
add_custom_target(All_CI)

# ----------------------------------------------------------------------------
# Build binaries
# ----------------------------------------------------------------------------
if (OPFLOW_BUILD_EXAMPLES OR OPFLOW_BUILD_ALL)
    message(STATUS "Generating examples")
    add_subdirectory(examples)
endif ()

# ----------------------------------------------------------------------------
# Build tests
# ----------------------------------------------------------------------------
if (OPFLOW_BUILD_TESTS OR OPFLOW_BUILD_ALL)
    message(STATUS "Generating tests")
    enable_testing()
    add_subdirectory(test)
endif ()

# ----------------------------------------------------------------------------
# Build benchmarks
# ----------------------------------------------------------------------------
if (OPFLOW_BUILD_BENCHMARKS OR OPFLOW_BUILD_ALL)
    message(STATUS "Generating benchmarks")
    # config google benchmark as part of the project
    set(BENCHMARK_ENABLE_INSTALL OFF)
    set(BENCHMARK_ENABLE_TESTING OFF)
    set(BENCHMARK_ENABLE_GTEST_TESTS OFF)
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/external/benchmark EXCLUDE_FROM_ALL)
    add_subdirectory(benchmark)
endif ()

# ----------------------------------------------------------------------------
# Build docs
# ----------------------------------------------------------------------------
if (OPFLOW_BUILD_DOCS OR OPFLOW_BUILD_ALL)
    message(STATUS "Generating docs")
    find_program(SPHINX_PATH sphinx-build
            HINTS $ENV{PATH} ${SPHINX_DIR})
    if (NOT SPHINX_PATH)
        message(FATAL_ERROR "sphinx-build not found. Please install it via \
        instructions at https://www.sphinx-doc.org/en/master/usage/installation.html")
    else ()
        message(STATUS "Found sphinx-build at ${SPHINX_PATH}")
    endif ()
    find_program(DOXYGEN_PATH doxygen
            HINTS ${DOXYGEN_DIR}
            REQUIRED
            )
    if (NOT DOXYGEN_PATH)
        message(FATAL_ERROR "Doxygen not found. Please install doxygen with version >= 1.9.2")
    else ()
        execute_process(
                COMMAND ${DOXYGEN_PATH} --version
                RESULT_VARIABLE _
                OUTPUT_VARIABLE _out
        )
        string(REGEX REPLACE "\n$" "" _out "${_out}")
        if (${_out} VERSION_LESS "1.9.2")
            message(FATAL_ERROR "Doxygen version too low. Found v${_out}, require >= v1.9.2")
        endif ()
    endif ()
    message(STATUS "Found Doxygen version: ${_out}")
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc/doxygen)
    add_custom_target(doxygen_doc
            COMMAND ${DOXYGEN_PATH} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
    add_custom_target(doc
            COMMAND ${SPHINX_PATH} -b html
            -Dbreathe_projects.OpFlow=${CMAKE_CURRENT_BINARY_DIR}/doc/doxygen/xml
            ${CMAKE_CURRENT_LIST_DIR}/doc ${CMAKE_CURRENT_BINARY_DIR}/doc
            DEPENDS doxygen_doc
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
endif ()

# uninstall target
if (NOT TARGET uninstall)
    configure_file(
            "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Uninstall.cmake.in"
            "${CMAKE_CURRENT_BINARY_DIR}/Uninstall.cmake"
            IMMEDIATE @ONLY)

    add_custom_target(uninstall
            COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/Uninstall.cmake)
endif ()
