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

#ifndef OPFLOW_JIT_KERNEL_HPP
#define OPFLOW_JIT_KERNEL_HPP

#include "lang/ir/IR.hpp"
#include <functional>
#include <memory>
#include <vector>

namespace OpFlow::lang {
    class Kernel {
    public:
        void operator()() const;
        std::vector<std::unique_ptr<Stmt>> statements;
    };

    class KernelBuilder {
    public:
        Kernel def(std::function<void()> ker);
    };
}// namespace OpFlow

#endif//OPFLOW_JIT_KERNEL_HPP
