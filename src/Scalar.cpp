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

#include "Scalar.hpp"
#include "Macros.hpp"
#include "Program.hpp"

namespace OpFlow {
    Scalar &Scalar::operator=(const Expr &other) {
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

}// namespace OpFlow