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

#include "Scalar.hpp"
#include "lang/program/Program.hpp"
#include "utils/Macros.hpp"

namespace OpFlow::lang {
    Var &Scalar::operator=(const Expr &other) {
        if (this != &other) {
            auto &prog = Program::get_current_program();
            if (auto ker = prog.get_current_kernel()) {
                // standalone kernel

            } else if (prog.is_interactive_mode()) {
                // push stmt into global kernel
            } else {
                OP_ERROR("Assignment not in any kernel scope");
            }
        }
        return *this;
    }
    Scalar::Scalar(double d) { this->elem_type_ = DataType::f64; }

    Scalar::Scalar(float f) { this->elem_type_ = DataType::f32; }

}// namespace OpFlow