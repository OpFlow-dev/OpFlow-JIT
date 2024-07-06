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

#ifndef OPFLOW_JIT_IRBUILDER_HPP
#define OPFLOW_JIT_IRBUILDER_HPP

#include "lang/ir/Block.hpp"
#include "lang/ir/Stmt.hpp"
#include <vector>

namespace OpFlow::lang {
    class IRBuilder {
    public:
        explicit IRBuilder(Block* root);

        static IRBuilder* get_current_builder();
        static void set_current_builder(IRBuilder* builder);

        Stmt* append(std::unique_ptr<Stmt>&& stmt);

        class ScopeGuard {
        public:
            ScopeGuard(IRBuilder* builder, Block* block);
            ~ScopeGuard();

        private:
            IRBuilder* builder_ = nullptr;
            Block* block_ = nullptr;
        };

        ScopeGuard create_scope(Block* block);

    private:
        static IRBuilder* current_ir_builder_;
        std::vector<Block*> ir_stack_;
    };
}// namespace OpFlow::lang

#endif//OPFLOW_JIT_IRBUILDER_HPP
