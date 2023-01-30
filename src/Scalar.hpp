// ----------------------------------------------------------------------------
//
// Copyright (c) 2019 - 2023 by the OpFlow developers
//
// This file is part of OpFlow.
//
// OpFlow is free software and is distributed under the MPL v2.0 license.
// The full text of the license can be found in the file LICENSE at the top
// level directory of OpFlow.
//
// ----------------------------------------------------------------------------

#ifndef OPFLOW_JIT_SCALAR_HPP
#define OPFLOW_JIT_SCALAR_HPP

#include "Expression.hpp"

namespace OpFlow {

    class Scalar : public virtual Expr {
    public:
        Scalar();
        Scalar(const Scalar& other);
        ~Scalar() override = default;

        Scalar& operator=(const Scalar& other);
        Scalar& operator=(const Expr& other);
    };
}

#endif//OPFLOW_JIT_SCALAR_HPP
