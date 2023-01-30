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

#ifndef OPFLOW_JIT_KERNEL_HPP
#define OPFLOW_JIT_KERNEL_HPP

#include <vector>
#include <memory>
#include "IR.hpp"

namespace OpFlow {
    class Kernel {
    public:
        std::vector<std::unique_ptr<Stmt>> statements;
    };
}

#endif//OPFLOW_JIT_KERNEL_HPP
