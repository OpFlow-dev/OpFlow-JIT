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

#ifndef OPFLOW_JIT_KERNEL_HPP
#define OPFLOW_JIT_KERNEL_HPP

#include "lang/ir/Block.hpp"
#include "lang/ir/IRNode.hpp"
#include "lang/program/IRBuilder.hpp"
#include "lang/program/RuntimeContext.hpp"
#include <functional>
#include <memory>

namespace OpFlow::lang {
    class Kernel {
    public:
        explicit Kernel(const std::function<void()>& func);
        void compile() const;
        void operator()() const;

    private:
        std::unique_ptr<Block> ir_root_ = nullptr;
        std::unique_ptr<IRBuilder> ir_builder_ = nullptr;

        mutable std::function<void(RuntimeContext*)> compiled_kernel_;
    };
}// namespace OpFlow::lang

#endif//OPFLOW_JIT_KERNEL_HPP
