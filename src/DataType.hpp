// ----------------------------------------------------------------------------
//
// Copyright (c) 2019 - 2023 by the OpFlow developers
//
// This file is part of OpFlow-JIT.
//
// OpFlow-JIT is free software and is distributed under the Apache-2.0 license.
// The full text of the license can be found in the file LICENSE at the top
// level directory of OpFlow-JIT.
//
// ----------------------------------------------------------------------------

#ifndef OPFLOW_JIT_DATATYPE_HPP
#define OPFLOW_JIT_DATATYPE_HPP

#include "Macros.hpp"
#include <fmt/format.h>
#include <string>
#include <type_traits>

namespace OpFlow {
    enum class DataType : unsigned int {
        uint8,
        uint16,
        uint32,
        uint64,
        int8,
        int16,
        int32,
        int64,
        f16,
        f32,
        f64,
        unknown
    };

    inline std::string to_string(DataType type) {
        switch (type) {
            case DataType::uint8:
                return "uint8";
            case DataType::uint16:
                return "uint16";
            case DataType::uint32:
                return "uint32";
            case DataType::uint64:
                return "uint64";
            case DataType::int8:
                return "int8";
            case DataType::int16:
                return "int16";
            case DataType::int32:
                return "int32";
            case DataType::int64:
                return "int64";
            case DataType::f16:
                return "f16";
            case DataType::f32:
                return "f32";
            case DataType::f64:
                return "f64";
            case DataType::unknown:
                return "unknown";
        }
    }

    template <typename T>
    inline DataType get_runtime_type(T&&) {
        using TT = std::remove_cv_t<std::remove_reference_t<T>>;
        if constexpr (std::is_same_v<TT, std::uint8_t>) {
            return DataType::uint8;
        } else if constexpr (std::is_same_v<TT, std::uint16_t>) {
            return DataType::uint16;
        } else if constexpr (std::is_same_v<TT, std::uint32_t>) {
            return DataType::uint32;
        } else if constexpr (std::is_same_v<TT, std::uint64_t>) {
            return DataType::uint64;
        } else if constexpr (std::is_same_v<TT, std::int8_t>) {
            return DataType::int8;
        } else if constexpr (std::is_same_v<TT, std::int16_t>) {
            return DataType::int16;
        } else if constexpr (std::is_same_v<TT, std::int32_t>) {
            return DataType::int32;
        } else if constexpr (std::is_same_v<TT, std::int64_t>) {
            return DataType::int64;
        } else if constexpr (std::is_same_v<TT, bool>) {
            return DataType::uint8;
        } else if constexpr (std::is_same_v<TT, std::float_t>) {
            return DataType::f32;
        } else if constexpr (std::is_same_v<TT, std::double_t>) {
            return DataType::f64;
        } else {
            return DataType::unknown;
        }
    }

    template <typename T>
    inline DataType get_runtime_type() {
        return get_runtime_type(T {});
    }
}// namespace OpFlow
#endif//OPFLOW_JIT_DATATYPE_HPP
