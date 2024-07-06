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

#include "Environment.hpp"
#include "utils/Macros.hpp"

namespace OpFlow {
    Environment &Environment::getInstance() {
        static Environment instance;
        return instance;
    }

    void Environment::init(int argc, char **argv) {}

    void Environment::setMode(OpFlow::Arch arch, OpFlow::Para para) {
        auto &env = getInstance();
        env.arch_ = arch;
        env.para_ = para;
        OP_INFO("Running with {}, {}", env.arch_ == Arch::x86_64 ? "x86_64" : "CUDA",
                env.para_ == Para::SingleNode ? "localhost" : "cluster");
    }
}// namespace OpFlow