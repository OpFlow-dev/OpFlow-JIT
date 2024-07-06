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

#include "Block.hpp"
#include "utils/Macros.hpp"

namespace OpFlow::lang {
    Block::Block() = default;
    Block::~Block() noexcept = default;

    void Block::accept(IRVisitor *visitor) { visitor->visit(this); }

    const Block *Block::get_parent() const { return parent_; }
    void Block::set_parent(const Block *parent) { parent_ = parent; }

    int Block::find_stmt(const Stmt *stmt) const {
        for (int i = 0; i < statements_.size(); ++i) {
            if (statements_[i].get() == stmt) return i;
        }
        return -1;
    }

    Stmt *Block::append_stmt(std::unique_ptr<Stmt> &&stmt) {
        stmt->set_parent(this);
        statements_.push_back(std::move(stmt));
        return statements_.back().get();
    }

    Stmt *Block::insert_stmt(int loc, std::unique_ptr<Stmt> &&stmt) {
        OP_ASSERT_MSG(loc < statements_.size(), "Location {} greater than block statements number", loc);
        stmt->set_parent(this);
        statements_.insert(statements_.begin() + loc, std::move(stmt));
        return statements_[loc].get();
    }

    void Block::remove_stmt(const Stmt *stmt) {
        int loc = find_stmt(stmt);
        if (loc < 0) return;
        statements_.erase(statements_.begin() + loc);
    }

    void Block::replace_stmt(const Stmt *stmt, std::unique_ptr<Stmt> &&new_stmt) {
        int loc = find_stmt(stmt);
        OP_ASSERT_MSG(loc > 0, "Stmt to be replaced not found");
        new_stmt->set_parent(this);
        std::swap(statements_[loc], new_stmt);
    }

    void Block::replace_stmt(const Stmt *stmt, std::vector<std::unique_ptr<Stmt>> &&new_stmt) {
        int loc = find_stmt(stmt);
        OP_ASSERT_MSG(loc > 0, "Stmt to be replaced not found");
        for (auto &s : new_stmt) { s->set_parent(this); }
        std::vector<std::unique_ptr<Stmt>> new_stmts;
        for (int i = 0; i < loc; ++i) { new_stmts.push_back(std::move(statements_[i])); }
        for (auto &s : new_stmt) { new_stmts.push_back(std::move(s)); }
        for (int i = loc; i < statements_.size(); ++i) { new_stmts.push_back(std::move(statements_[i])); }
        std::swap(statements_, new_stmts);
    }
}// namespace OpFlow::lang
