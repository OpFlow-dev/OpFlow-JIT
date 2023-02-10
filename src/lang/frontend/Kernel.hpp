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

#include "lang/ir/IRNode.hpp"
#include <functional>

namespace OpFlow::lang {
    class Kernel {
    public:
        void operator()() const;
    };

    class KernelBuilder {
    public:
        Kernel def(std::function<void()> ker);
    };
}// namespace OpFlow::lang

#endif//OPFLOW_JIT_KERNEL_HPP
