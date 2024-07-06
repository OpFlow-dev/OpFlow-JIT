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

#include "Expression.hpp"
#include "Equation.hpp"
#include "utils/Macros.hpp"

namespace OpFlow::lang {
    DataType Expr::get_elem_type() const { return elem_type_; }

    void *Expr::val_impl(const Index &index, DataType desire_type) {
        OP_ASSERT_MSG(data_accessor_, "Data accessor for expr not loaded.");
        auto ptr = data_accessor_ ? data_accessor_(index) : nullptr;
        OP_ASSERT(ptr);
        OP_ASSERT(elem_type_ == DataType::unknown || elem_type_ == desire_type);
        return ptr;
    }

    bool Expr::is_lvalue() const { return false; }

    Expr &Expr::operator+=(const Expr &o) {
        OP_NOT_IMPLEMENTED;
        return *this;
    }

    Expr &Expr::operator-=(const Expr &o) {
        OP_NOT_IMPLEMENTED;
        return *this;
    }

    Expr &Expr::operator*=(const Expr &o) {
        OP_NOT_IMPLEMENTED;
        return *this;
    }

    Expr &Expr::operator/=(const Expr &o) {
        OP_NOT_IMPLEMENTED;
        return *this;
    }

    Expr operator+(const Expr &a, const Expr &b) {
        auto ret = a;
        return ret += b;
    }

    Expr operator-(const Expr &a, const Expr &b) {
        auto ret = a;
        return ret -= b;
    }

    Expr operator*(const Expr &a, const Expr &b) {
        auto ret = a;
        return ret *= b;
    }

    Expr operator/(const Expr &a, const Expr &b) {
        auto ret = a;
        return ret /= b;
    }

}// namespace OpFlow::lang