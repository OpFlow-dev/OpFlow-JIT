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

#include "Program.hpp"
#include "utils/Macros.hpp"

namespace OpFlow::lang {
    Program& Program::get_current_program() {
        static Program program;
        return program;
    }

    const Kernel* Program::get_current_kernel() const { return current_kernel_; }

    void Program::set_lazy_compile(bool option) { lazy_compile_ = option; }
    bool Program::is_lazy_compile() const { return lazy_compile_; }
    RuntimeContext Program::get_context() { return RuntimeContext(); }
    void Program::set_current_kernel(const Kernel* kernel) { current_kernel_ = kernel; }
}// namespace OpFlow::lang
