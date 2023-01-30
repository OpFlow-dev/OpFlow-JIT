// ----------------------------------------------------------------------------
//
// Copyright (c) 2019 - 2022 by the OpFlow developers
//
// This file is part of OpFlow.
//
// OpFlow is free software and is distributed under the MPL v2.0 license.
// The full text of the license can be found in the file LICENSE at the top
// level directory of OpFlow.
//
// ----------------------------------------------------------------------------

#ifndef OPFLOW_JIT_EXPRESSION_HPP
#define OPFLOW_JIT_EXPRESSION_HPP

#include "DataType.hpp"
#include "Index.hpp"
#include <functional>
#include <utility>

namespace OpFlow {

    class Expr {
    public:
        virtual ~Expr() = default;

        [[nodiscard]] virtual bool is_lvalue() const = 0;

        [[nodiscard]] DataType get_elem_type() const;

        template <typename T>
        [[nodiscard]] T& val(const Index& index) {
            auto ptr = data_accessor_(index);
            OP_ASSERT(ptr);
            OP_ASSERT(elem_type_ == DataType::unknown || elem_type_ == get_runtime_type<T>());
            return *static_cast<T*>(ptr);
        }

    protected:
        DataType elem_type_ = DataType::unknown;
        std::function<void*(const Index&)> data_accessor_;
    };
}// namespace OpFlow

#endif//OPFLOW_JIT_EXPRESSION_HPP
