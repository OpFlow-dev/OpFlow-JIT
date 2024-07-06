// ----------------------------------------------------------------------------
//
// Copyright (c) 2019 - 2024 by the OpFlow developers
//
// This file is part of OpFlow-JIT.
//
// OpFlow-JIT is free software and is distributed under the Apache-2.0 license.
// The full text of the license can be found in the file LICENSE at the top
// level directory of OpFlow-JIT.
//
// ----------------------------------------------------------------------------

#ifndef OPFLOW_JIT_EXPRESSION_HPP
#define OPFLOW_JIT_EXPRESSION_HPP

#include "DataType.hpp"
#include "Index.hpp"
#include <functional>
#include <utility>

namespace OpFlow::lang {
    class Expr {
    public:
        virtual ~Expr() = default;

        [[nodiscard]] virtual bool is_lvalue() const;

        [[nodiscard]] DataType get_elem_type() const;

        template <typename T>
        [[nodiscard]] T& val(const Index& index) {
            auto ptr = val_impl(index, get_runtime_type<T>());
            return *static_cast<T*>(ptr);
        }

        virtual Expr& operator+=(const Expr& o);
        virtual Expr& operator-=(const Expr& o);
        virtual Expr& operator*=(const Expr& o);
        virtual Expr& operator/=(const Expr& o);

    protected:
        [[nodiscard]] void* val_impl(const Index& index, DataType desire_type);

        DataType elem_type_ = DataType::unknown;
        std::function<void*(const Index&)> data_accessor_;
    };

    Expr operator+(const Expr& a, const Expr& b);
    Expr operator-(const Expr& a, const Expr& b);
    Expr operator*(const Expr& a, const Expr& b);
    Expr operator/(const Expr& a, const Expr& b);
}// namespace OpFlow::lang

#endif//OPFLOW_JIT_EXPRESSION_HPP
