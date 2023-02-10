# ----------------------------------------------------------------------------
#
# Copyright (c) 2019 - 2023 by the OpFlow developers
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

cmake_minimum_required(VERSION 3.13)

# ----------------------------------------------------------------------------
# Start OpFlow-JIT project
# ----------------------------------------------------------------------------
include(cmake/Utils.cmake)
include(cmake/IDE.cmake)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

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
option(OPFLOW_BUILD_EXAMPLES "Build OpFlow's example cases" OFF)

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

# architecture options
option(OPFLOW_WITH_OPENMP "Build with OpenMP support" ON)
option(OPFLOW_WITH_MPI "Build with MPI support" OFF)
option(OPFLOW_WITH_CUDA "Build with CUDA support" OFF)

# install options
option(OPFLOW_INSTALL "Generate the install target" ${OPFLOW_MASTER_PROJECT})

message(STATUS "Build type: " ${CMAKE_BUILD_TYPE})

set(CMAKE_EXPORT_COMPILE_COMMANDS OPFLOW_GEN_COMPILE_COMMANDS)

# ----------------------------------------------------------------------------
# Declare the OpFlow-JIT target
# ----------------------------------------------------------------------------
add_library(OpFlow-JIT STATIC src/lang/frontend/Expression.cpp
        src/lang/frontend/Expression.hpp
        src/lang/frontend/Scalar.cpp
        src/lang/frontend/Scalar.hpp
        src/lang/program/Program.cpp
        src/lang/program/Program.hpp
        src/lang/frontend/Kernel.cpp
        src/lang/frontend/Kernel.hpp
        src/lang/ir/IRNode.cpp
        src/lang/ir/IRNode.hpp src/lang/frontend/Field.hpp src/lang/frontend/DataType.hpp src/lang/frontend/Variable.cpp src/lang/frontend/Variable.hpp src/lang/frontend/Index.cpp src/lang/frontend/Index.hpp src/lang/program/Environment.cpp src/lang/program/Environment.hpp src/lang/frontend/mesh/Mesh.hpp src/OpFlow.hpp src/lang/frontend/Field.cpp src/lang/frontend/mesh/Mesh.cpp src/lang/frontend/bc/Boundary.cpp src/lang/frontend/bc/Boundary.hpp src/ops/FDM/fdms.cpp src/ops/FDM/fdms.hpp src/lang/frontend/Equation.cpp src/lang/frontend/Equation.hpp src/lang/frontend/Solve.cpp src/lang/frontend/Solve.hpp src/lang/frontend/mesh/StructuredMesh.cpp src/lang/frontend/mesh/StructuredMesh.hpp src/utils/Prototypes.hpp src/lang/frontend/mesh/CartesianMesh.cpp src/lang/frontend/mesh/CartesianMesh.hpp src/lang/frontend/mesh/UnstructuredMesh.cpp src/lang/frontend/mesh/UnstructuredMesh.hpp src/lang/frontend/mesh/MultiPatchedMesh.cpp src/lang/frontend/mesh/MultiPatchedMesh.hpp src/lang/frontend/mesh/BoundaryDescriptor.cpp src/lang/frontend/mesh/BoundaryDescriptor.hpp src/lang/frontend/mesh/MeshProxy.cpp src/lang/frontend/mesh/MeshProxy.hpp src/lang/frontend/mesh/MeshLocDescriptor.cpp src/lang/frontend/mesh/MeshLocDescriptor.hpp src/lang/pass/IRVisitor.cpp src/lang/pass/IRVisitor.hpp src/lang/ir/Stmt.cpp src/lang/ir/Stmt.hpp src/lang/ir/Block.cpp src/lang/ir/Block.hpp src/lang/pass/IRPrinter.cpp src/lang/pass/IRPrinter.hpp)
add_library(OpFlow::OpFlow-JIT ALIAS OpFlow-JIT)

target_include_directories(OpFlow-JIT PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

# ----------------------------------------------------------------------------
# Use fmt package
# ----------------------------------------------------------------------------
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/fmt EXCLUDE_FROM_ALL)
target_link_libraries(OpFlow-JIT PRIVATE fmt::fmt)

# ----------------------------------------------------------------------------
# Use spdlog package
# ----------------------------------------------------------------------------
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/spdlog EXCLUDE_FROM_ALL)
target_link_libraries(OpFlow-JIT PRIVATE spdlog::spdlog)

# ----------------------------------------------------------------------------
# Use AMGCL
# ----------------------------------------------------------------------------
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/external/amgcl EXCLUDE_FROM_ALL)
target_link_libraries(OpFlow-JIT PRIVATE amgcl::amgcl)

# ----------------------------------------------------------------------------
# Use TBB
# ----------------------------------------------------------------------------
if (OPFLOW_TBB_EXTERNAL)
    if (NOT DEFINED TBB_DIR)
        message(FATAL "Variable TBB_DIR not defined. Use -DTBB_DIR to specify TBB's install path.")
    endif ()
    find_package(TBB REQUIRED PATHS ${TBB_DIR} NO_DEFAULT_PATH)
else ()
    set(BUILD_SHARED_LIBS ON)
    set(TBB_TEST OFF)
    set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/external/tbb EXCLUDE_FROM_ALL)
endif ()
target_link_libraries(OpFlow-JIT INTERFACE TBB::tbb)

# ----------------------------------------------------------------------------
# Find MPI
# ----------------------------------------------------------------------------
if (OPFLOW_WITH_MPI)
    find_package(MPI REQUIRED)
    target_link_libraries(OpFlow-JIT PRIVATE MPI::MPI_C MPI::MPI_CXX)

    list(APPEND PKG_CONFIG_REQUIRES MPI)
endif ()

# ----------------------------------------------------------------------------
# Find OpenMP
# ----------------------------------------------------------------------------
if (OPFLOW_WITH_OPENMP)
    # workarounds for CI to find the correct libomp
    if (APPLE)
        if (EXISTS /usr/local/opt/llvm/lib)
            link_directories("/usr/local/opt/llvm/lib")
        endif ()
    endif ()
    if (CMAKE_C_COMPILER_ID MATCHES "Clang")
        set(OpenMP_C "${CMAKE_C_COMPILER}")
        set(OpenMP_C_FLAGS "-fopenmp=libomp -Wno-unused-command-line-argument")
        set(OpenMP_C_LIB_NAMES "omp")
        set(OpenMP_omp_LIBRARY ${OpenMP_C_LIB_NAMES})
    endif ()
    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(OpenMP_CXX "${CMAKE_CXX_COMPILER}")
        set(OpenMP_CXX_FLAGS "-fopenmp=libomp -Wno-unused-command-line-argument")
        set(OpenMP_CXX_LIB_NAMES "omp")
        set(OpenMP_omp_LIBRARY ${OpenMP_CXX_LIB_NAMES})
    endif ()
    find_package(OpenMP REQUIRED)
    target_link_libraries(OpFlow-JIT INTERFACE OpenMP::OpenMP_C OpenMP::OpenMP_CXX)
    target_compile_options(OpFlow-JIT INTERFACE ${OpenMP_CXX_FLAGS})

    list(APPEND PKG_CONFIG_REQUIRES OpenMP)
endif ()

# ----------------------------------------------------------------------------
# Platform detection
# ----------------------------------------------------------------------------
if (UNIX)
    target_compile_definitions(OpFlow-JIT INTERFACE OPFLOW_PLATFORM_UNIX)
elseif (APPLE)
    target_compile_definitions(OpFlow-JIT INTERFACE OPFLOW_PLATFORM_APPLE)
elseif (WIN32)
    target_compile_definitions(OpFlow-JIT INTERFACE OPFLOW_PLATFORM_WIN)
endif ()

# ----------------------------------------------------------------------------
# Language & library features detection
# ----------------------------------------------------------------------------
include(CheckIncludeFiles)
check_include_files("sys/mman.h" HAS_SYS_MMAN_H)
if (HAS_SYS_MMAN_H)
    target_compile_definitions(OpFlow-JIT INTERFACE OPFLOW_HAS_MMAN_H)
endif ()

# ----------------------------------------------------------------------------
# Misc definitions according to tweak options
# ----------------------------------------------------------------------------
foreach (
        OPFLOW_OPTION
        OPFLOW_SINGLE_PRECISION
        OPFLOW_WITH_MPI
        OPFLOW_WITH_OPENMP
        OPFLOW_WITH_CUDA)
    if (${OPFLOW_OPTION})
        target_compile_definitions(OpFlow-JIT INTERFACE ${OPFLOW_OPTION})
    endif ()
endforeach ()

if (OPFLOW_NO_EXCEPTIONS AND NOT MSVC)
    target_compile_options(OpFlow-JIT INTERFACE -fno-exceptions)
endif ()

# sanitizer flags
target_compile_options(OpFlow-JIT
        PRIVATE $<$<BOOL:${OPFLOW_SANITIZE_ADDRESS}>: -fsanitize=address>
        PRIVATE $<$<BOOL:${OPFLOW_SANITIZE_LEAK}>: -fsanitize=leak>
        PRIVATE $<$<BOOL:${OPFLOW_SANITIZE_THREAD}>: -fsanitize=thread>
        PRIVATE $<$<BOOL:${OPFLOW_SANITIZE_UB}>: -fsanitize=undefined>)
target_link_options(OpFlow-JIT
        PRIVATE $<$<BOOL:${OPFLOW_SANITIZE_ADDRESS}>: -fsanitize=address>
        PRIVATE $<$<BOOL:${OPFLOW_SANITIZE_LEAK}>: -fsanitize=leak>
        PRIVATE $<$<BOOL:${OPFLOW_SANITIZE_THREAD}>: -fsanitize=thread>
        PRIVATE $<$<BOOL:${OPFLOW_SANITIZE_UB}>: -fsanitize=undefined>)

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

# ----------------------------------------------------------------------------
# Install
# ----------------------------------------------------------------------------
if (OPFLOW_INSTALL)
    message(STATUS "Generating install")
    IF (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
        SET(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}" CACHE PATH "" FORCE)
        message(STATUS "Install prefix set to: ${CMAKE_INSTALL_PREFIX}")
    ENDIF (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(project_config_in "${CMAKE_CURRENT_LIST_DIR}/cmake/OpFlowConfig.cmake.in")
    set(project_config_out "${CMAKE_CURRENT_BINARY_DIR}/OpFlowConfig.cmake")
    set(config_targets_file "OpFlowConfigTargets.cmake")
    set(version_config_file "${CMAKE_CURRENT_BINARY_DIR}/OpFlowConfigVersion.cmake")
    set(export_dest_dir "${CMAKE_INSTALL_LIBDIR}/cmake/OpFlow-JIT")
    set(pkgconfig_install_dir "${CMAKE_INSTALL_LIBDIR}/pkgconfig")
    set(pkg_config "${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pc")

    # ----------------------------------------------------------------------------
    # Include files
    # ----------------------------------------------------------------------------
    install(
            TARGETS OpFlow-JIT
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

    # ----------------------------------------------------------------------------
    # Install CMake config files
    # ----------------------------------------------------------------------------
    #install(EXPORT OpFlow-JIT DESTINATION ${export_dest_dir} NAMESPACE OpFlow-JIT:: FILE ${config_targets_file})

    include(CMakePackageConfigHelpers)
    configure_file("${project_config_in}" "${project_config_out}" @ONLY)

    write_basic_package_version_file("${version_config_file}" COMPATIBILITY SameMajorVersion)
    install(FILES "${project_config_out}" "${version_config_file}" DESTINATION "${export_dest_dir}")

    # ----------------------------------------------------------------------------
    # Support creation of installable packages
    # ----------------------------------------------------------------------------
    #include(cmake/opflowCPack.cmake)
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
