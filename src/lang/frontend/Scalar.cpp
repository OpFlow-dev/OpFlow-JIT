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

#include "Scalar.hpp"
#include "utils/Macros.hpp"

namespace OpFlow::lang {
    Var &Scalar::operator=(const Expr &other) {
        if (this != &other) {
            OP_NOT_IMPLEMENTED;
        }
        return *this;
    }
    Scalar::Scalar(double d) { this->elem_type_ = DataType::f64; }

    Scalar::Scalar(float f) { this->elem_type_ = DataType::f32; }

}// namespace OpFlow::lang