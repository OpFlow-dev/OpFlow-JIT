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

#ifndef OPFLOW_JIT_EQUATION_HPP
#define OPFLOW_JIT_EQUATION_HPP

#include "Expression.hpp"
#include "Variable.hpp"

namespace OpFlow::lang {
    class Equation {
    public:
        Equation() = default;
        Equation(Expr lhs, Expr rhs);
        Equation(Expr lhs, Expr rhs, Var& target);

        void set_equation(Expr lhs, Expr rhs);
        void set_target(Var& target);

    private:
        Expr lhs_, rhs_;
        Var* target_ = nullptr;
    };

    Equation operator==(const Expr& lhs, const Expr& rhs);
}// namespace OpFlow

#endif//OPFLOW_JIT_EQUATION_HPP
