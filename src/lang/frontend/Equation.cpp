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

#include "Equation.hpp"

namespace OpFlow::lang {
    Equation::Equation(Expr lhs, Expr rhs) : lhs_(lhs), rhs_(rhs) {}

    Equation::Equation(Expr lhs, Expr rhs, Var& target) : lhs_(lhs), rhs_(rhs), target_(&target) {}

    void Equation::set_equation(Expr lhs, Expr rhs) {
        lhs_ = lhs;
        rhs_ = rhs;
    }

    void Equation::set_target(Var& target) { target_ = &target; }

    Equation operator==(const Expr& lhs, const Expr& rhs) { return {lhs, rhs}; }
}// namespace OpFlow::lang