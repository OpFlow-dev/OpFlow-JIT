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

#ifndef OPFLOW_JIT_PROGRAM_HPP
#define OPFLOW_JIT_PROGRAM_HPP

#include "lang/frontend/Kernel.hpp"
#include "lang/program/RuntimeContext.hpp"

namespace OpFlow::lang {
    /// \brief The concept of a compile target
    class Program {
    public:
        Program(const Program&) = delete;
        ~Program() = default;

        static Program& get_current_program();
        [[nodiscard]] const Kernel* get_current_kernel() const;
        void set_current_kernel(const Kernel* kernel);
        void set_lazy_compile(bool option);
        [[nodiscard]] bool is_lazy_compile() const;
        RuntimeContext get_context();

    private:
        Program() = default;
        Program(Program&&) = default;

        const Kernel* current_kernel_ = nullptr;
        bool lazy_compile_ = true;
    };
}// namespace OpFlow::lang

#endif//OPFLOW_JIT_PROGRAM_HPP
