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

#ifndef OPFLOW_JIT_PROGRAM_HPP
#define OPFLOW_JIT_PROGRAM_HPP

#include "Kernel.hpp"

namespace OpFlow {
    /// \brief The concept of a compile target
    class Program {
    public:
        Program(const Program&) = delete;
        ~Program() = default;

        static Program& get_current_program();
        Kernel* get_current_kernel();
        [[nodiscard]] bool is_interactive_mode() const;
        void set_interactive_mode(bool option);
        void set_lazy_compile(bool option);

    private:
        Program() = default;
        Program(Program&&) = default;

        Kernel* current_kernel = nullptr;
        bool interactive_mode = false;
        bool lazy_compile = true;
    };
}// namespace OpFlow

#endif//OPFLOW_JIT_PROGRAM_HPP
