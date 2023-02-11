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

#include "Kernel.hpp"
#include "lang/pass/IRPrinter.hpp"
#include "lang/program/Program.hpp"
#include "utils/Macros.hpp"

namespace OpFlow::lang {
    Kernel::Kernel(const std::function<void()> &func) {
        ir_root_ = std::make_unique<Block>();
        ir_builder_ = std::make_unique<IRBuilder>(ir_root_.get());
        IRBuilder::set_current_builder(ir_builder_.get());
        func();
        if (!Program::get_current_program().is_lazy_compile()) compile();
    }

    void Kernel::operator()() const {
        if (!compiled_kernel_) compile();
        Program::get_current_program().set_current_kernel(this);
        auto ctx = Program::get_current_program().get_context();
        compiled_kernel_(&ctx);
        Program::get_current_program().set_current_kernel(nullptr);
    }

    void Kernel::compile() const {
        IRPrinter::run(ir_root_.get());
        compiled_kernel_ = [](auto &&) {};
        OP_NOT_IMPLEMENTED;
    }
}// namespace OpFlow::lang