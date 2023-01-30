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

#include "Program.hpp"
#include "Macros.hpp"

namespace OpFlow {
    Program& Program::get_current_program() {
        static Program program;
        return program;
    }

    bool Program::is_interactive_mode() const {
        return interactive_mode && lazy_compile;
    }

    Kernel* Program::get_current_kernel() { return current_kernel; }

    void Program::set_interactive_mode(bool option) { interactive_mode = option; }

    void Program::set_lazy_compile(bool option) { lazy_compile = option; }
}// namespace OpFlow
