//  ----------------------------------------------------------------------------
//
//  Copyright (c) 2019 - 2024 by the OpFlow developers
//
//  This file is part of OpFlow-JIT.
//
//  OpFlow is free software and is distributed under the Apache-2.0 license.
//  The full text of the license can be found in the file LICENSE at the top
//  level directory of OpFlow-JIT.
//
//  ----------------------------------------------------------------------------

#ifndef OPFLOW_MACROS_HPP
#define OPFLOW_MACROS_HPP

#include <cassert>
#define OPFLOW_INLINE inline

#if defined(__INTEL_COMPILER) || defined(__clang__)// Intel / Clang compiler
#define OPFLOW_STRONG_INLINE OPFLOW_INLINE
#elif defined(_MSC_VER)// MSVC compiler
#define OPFLOW_STRONG_INLINE __forceinline
#else// GNU compiler
#define OPFLOW_STRONG_INLINE __attribute__((always_inline)) inline
#endif

#if __cplusplus >= 201402L
#define OPFLOW_CPP14
#endif

#if __cplusplus >= 201703L
#define OPFLOW_CPP17
#endif

#if __cplusplus > 201703L
#define OPFLOW_CPP2a
#define OPFLOW_CPP20
#endif

#include <cstring>

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#include <spdlog/spdlog.h>

#define SPD_AUGMENTED_LOG(X, ...)                                                                            \
    spdlog::X(fmt::format("[{}:{}@{}] ", __FILENAME__, __FUNCTION__, __LINE__) + fmt::format(__VA_ARGS__))

#ifndef OP_DEBUGLEVEL
#define OP_DEBUGLEVEL 1
#endif

#define OP_CRITICAL(...) SPD_AUGMENTED_LOG(critical, __VA_ARGS__)
#define OP_INFO(...) SPD_AUGMENTED_LOG(info, __VA_ARGS__)
#define OP_PERFINFO(...) SPD_AUGMENTED_LOG(info, __VA_ARGS__)

#if OP_DEBUGLEVEL > 0
#define OP_ERROR(...) SPD_AUGMENTED_LOG(error, __VA_ARGS__)
#else
#define OP_ERROR(...)
#endif

#if OP_DEBUGLEVEL > 1
#define OP_WARN(...) SPD_AUGMENTED_LOG(warn, __VA_ARGS__)
#else
#define OP_WARN(...)
#endif

#if OP_DEBUGLEVEL > 2
#define OP_DEBUG(...) SPD_AUGMENTED_LOG(debug, __VA_ARGS__)
#else
#define OP_DEBUG(...)
#endif

#if OP_DEBUGLEVEL > 3
#define OP_TRACE(...) SPD_AUGMENTED_LOG(trace, __VA_ARGS__)
#else
#define OP_TRACE(...)
#endif

#if !defined(NDEBUG) && defined(OPFLOW_ENABLE_STACK_TRACE)
#include "Utils/StackTracer.hpp"
// global stack tracer
namespace OpFlow {
    inline static Utils::StackTracer stackTracer;
}

#define OP_STACK_PUSH(...)                                                                                   \
    do {                                                                                                     \
        OpFlow::stackTracer.push(fmt::format("[{}:{}@{}] ", __FILENAME__, __FUNCTION__, __LINE__)            \
                                 + fmt::format(__VA_ARGS__));                                                \
    } while (0)
#define OP_STACK_APPEND(...)                                                                                 \
    do { OpFlow::stackTracer.append(fmt::format(__VA_ARGS__)); } while (0)
#define OP_STACK_POP                                                                                         \
    do { OpFlow::stackTracer.pop(); } while (0)
#define OP_DUMPSTACK                                                                                         \
    do { OP_ERROR("{}", OpFlow::stackTracer.dump()); } while (0)
#else

#define OP_STACK_PUSH(...)
#define OP_STACK_APPEND(...)
#define OP_STACK_POP
#define OP_DUMPSTACK
#endif

#define OP_NOT_IMPLEMENTED OP_ERROR("Function {} not implemented.", __FUNCTION__)
#define OP_EMPTY_BODY OP_WARN("Empty body.")
#define OP_TODO(X) OP_WARN("TODO: {}", X)

#define OP_ABORT                                                                                             \
    OP_DUMPSTACK;                                                                                            \
    OP_CRITICAL("Aborting.");                                                                                \
    std::abort()

#ifndef NDEBUG
#define OP_ASSERT(X)                                                                                         \
    do {                                                                                                     \
        if (!(X)) {                                                                                          \
            OP_ERROR("Assertion {} failed.", #X);                                                            \
            OP_ABORT;                                                                                        \
        }                                                                                                    \
    } while (0)
#define OP_ASSERT_MSG(X, ...)                                                                                \
    do {                                                                                                     \
        if (!(X)) {                                                                                          \
            OP_ERROR("Assertion {} failed.", #X);                                                            \
            OP_ERROR(__VA_ARGS__);                                                                           \
            OP_ABORT;                                                                                        \
        }                                                                                                    \
    } while (0)
#define OP_EXPECT(X)                                                                                         \
    do {                                                                                                     \
        if (!(X)) { OP_WARN("Expectation {} failed.", #X); }                                                 \
    } while (0)
#define OP_EXPECT_MSG(X, ...)                                                                                \
    do {                                                                                                     \
        if (!(X)) {                                                                                          \
            OP_WARN("Expectation {} failed.", #X);                                                           \
            OP_WARN(__VA_ARGS__);                                                                            \
        }                                                                                                    \
    } while (0)
#else
#define OP_ASSERT(X)
#define OP_EXPECT(X)
#define OP_ASSERT_MSG(X, ...)
#define OP_EXPECT_MSG(X, ...)
#endif

#if defined(OPFLOW_WITH_MPI) && defined(OPFLOW_DISTRIBUTE_MODEL_MPI)
#define OP_MPI_SEQ_INFO(...)                                                                                 \
    do {                                                                                                     \
        int _rank;                                                                                           \
        MPI_Comm_rank(MPI_COMM_WORLD, &_rank);                                                               \
        int _nproc;                                                                                          \
        MPI_Comm_size(MPI_COMM_WORLD, &_nproc);                                                              \
        for (auto _i = 0; _i < _nproc; ++_i) {                                                               \
            if (_i == _rank) OP_INFO(__VA_ARGS__);                                                           \
            MPI_Barrier(MPI_COMM_WORLD);                                                                     \
        }                                                                                                    \
    } while (0)
#define OP_MPI_SEQ_WARN(...)                                                                                 \
    do {                                                                                                     \
        int _rank;                                                                                           \
        MPI_Comm_rank(MPI_COMM_WORLD, &_rank);                                                               \
        int _nproc;                                                                                          \
        MPI_Comm_size(MPI_COMM_WORLD, &_nproc);                                                              \
        for (auto _i = 0; _i < _nproc; ++_i) {                                                               \
            if (_i == _rank) OP_WARN(__VA_ARGS__);                                                           \
            MPI_Barrier(MPI_COMM_WORLD);                                                                     \
        }                                                                                                    \
    } while (0)
#define OP_MPI_SEQ_DEBUG(...)                                                                                \
    do {                                                                                                     \
        int _rank;                                                                                           \
        MPI_Comm_rank(MPI_COMM_WORLD, &_rank);                                                               \
        int _nproc;                                                                                          \
        MPI_Comm_size(MPI_COMM_WORLD, &_nproc);                                                              \
        for (auto _i = 0; _i < _nproc; ++_i) {                                                               \
            if (_i == _rank) OP_DEBUG(__VA_ARGS__);                                                          \
            MPI_Barrier(MPI_COMM_WORLD);                                                                     \
        }                                                                                                    \
    } while (0)
#define OP_MPI_SEQ_TRACE(...)                                                                                \
    do {                                                                                                     \
        int _rank;                                                                                           \
        MPI_Comm_rank(MPI_COMM_WORLD, &_rank);                                                               \
        int _nproc;                                                                                          \
        MPI_Comm_size(MPI_COMM_WORLD, &_nproc);                                                              \
        for (auto _i = 0; _i < _nproc; ++_i) {                                                               \
            if (_i == _rank) OP_TRACE(__VA_ARGS__);                                                          \
            MPI_Barrier(MPI_COMM_WORLD);                                                                     \
        }                                                                                                    \
    } while (0)
#define OP_MPI_MASTER_INFO(...)                                                                              \
    do {                                                                                                     \
        int _rank;                                                                                           \
        MPI_Comm_rank(MPI_COMM_WORLD, &_rank);                                                               \
        if (_rank == 0) OP_INFO(__VA_ARGS__);                                                                \
    } while (0)
#define OP_MPI_MASTER_WARN(...)                                                                              \
    do {                                                                                                     \
        int _rank;                                                                                           \
        MPI_Comm_rank(MPI_COMM_WORLD, &_rank);                                                               \
        if (_rank == 0) OP_WARN(__VA_ARGS__);                                                                \
    } while (0)
#define OP_MPI_MASTER_DEBUG(...)                                                                             \
    do {                                                                                                     \
        int _rank;                                                                                           \
        MPI_Comm_rank(MPI_COMM_WORLD, &_rank);                                                               \
        if (_rank == 0) OP_DEBUG(__VA_ARGS__);                                                               \
    } while (0)
#define OP_MPI_MASTER_TRACE(...)                                                                             \
    do {                                                                                                     \
        int _rank;                                                                                           \
        MPI_Comm_rank(MPI_COMM_WORLD, &_rank);                                                               \
        if (_rank == 0) OP_TRACE(__VA_ARGS__);                                                               \
    } while (0)
#else
#define OP_MPI_SEQ_INFO(...) OP_INFO(__VA_ARGS__)
#define OP_MPI_SEQ_DEBUG(...) OP_DEBUG(__VA_ARGS__)
#define OP_MPI_SEQ_TRACE(...) OP_TRACE(__VA_ARGS__)
#define OP_MPI_SEQ_WARN(...) OP_WARN(__VA_ARGS__)
#define OP_MPI_MASTER_INFO(...) OP_INFO(__VA_ARGS__)
#define OP_MPI_MASTER_DEBUG(...) OP_DEBUG(__VA_ARGS__)
#define OP_MPI_MASTER_TRACE(...) OP_TRACE(__VA_ARGS__)
#define OP_MPI_MASTER_WARN(...) OP_WARN(__VA_ARGS__)
#endif

#include <utility>
#define OP_PERFECT_FOWD(X) std::forward<decltype(X)>(X)

#endif//OPFLOW_MACROS_HPP
