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

#ifndef OPFLOW_JIT_BLOCK_HPP
#define OPFLOW_JIT_BLOCK_HPP

#include "lang/ir/IRNode.hpp"
#include "lang/ir/Stmt.hpp"
#include <memory>

namespace OpFlow::lang {
    class Block : public virtual IRNode {
    public:
        Block();
        ~Block() noexcept override;

        void accept(IRVisitor* visitor) override;

        [[nodiscard]] const Block* get_parent() const;
        void set_parent(const Block* parent);

        int find_stmt(const Stmt* stmt) const;
        Stmt* append_stmt(std::unique_ptr<Stmt>&& stmt);
        Stmt* insert_stmt(int loc, std::unique_ptr<Stmt>&& stmt);
        void remove_stmt(const Stmt* stmt);
        void replace_stmt(const Stmt* stmt, std::unique_ptr<Stmt>&& new_stmt);
        void replace_stmt(const Stmt* stmt, std::vector<std::unique_ptr<Stmt>>&& new_stmt);

    private:
        const Block* parent_ = nullptr;
        std::vector<std::unique_ptr<Stmt>> statements_;
    };
}// namespace OpFlow::lang

#endif//OPFLOW_JIT_BLOCK_HPP
