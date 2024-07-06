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

#include "IRBuilder.hpp"
#include "lang/frontend/Kernel.hpp"
#include "utils/Macros.hpp"

namespace OpFlow::lang {
    IRBuilder::IRBuilder(Block* block) { ir_stack_.push_back(block); }

    IRBuilder* IRBuilder::current_ir_builder_ = nullptr;

    IRBuilder* IRBuilder::get_current_builder() { return current_ir_builder_; }

    void IRBuilder::set_current_builder(IRBuilder* builder) { current_ir_builder_ = builder; }

    Stmt* IRBuilder::append(std::unique_ptr<Stmt>&& stmt) { ir_stack_.back()->append_stmt(std::move(stmt)); }

    IRBuilder::ScopeGuard::ScopeGuard(IRBuilder* builder, Block* block) : builder_(builder), block_(block) {
        builder_->ir_stack_.push_back(block_);
    }

    IRBuilder::ScopeGuard::~ScopeGuard() { builder_->ir_stack_.pop_back(); }

    IRBuilder::ScopeGuard IRBuilder::create_scope(Block* block) { return {this, block}; }
}// namespace OpFlow::lang