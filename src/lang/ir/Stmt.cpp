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

#include "Stmt.hpp"
#include "utils/Macros.hpp"
#include <fmt/format.h>

namespace OpFlow::lang {
    std::atomic_int Stmt::instance_counter_ = 0;

    Stmt::Stmt() { id_ = instance_counter_++; }
    Stmt::~Stmt() noexcept = default;

    std::string Stmt::type_name() const { return "Stmt"; }

    Block* Stmt::get_parent_block() { return parent_; }
    const Block* Stmt::get_parent_block() const { return parent_; }

    std::string Stmt::get_name() const { return fmt::format("${}", id_); }
    std::string Stmt::get_raw_name() const { return fmt::format("v{}", id_); }

    std::vector<Stmt*> Stmt::get_operands() const { return operands_; }
    int Stmt::num_operands() const { return (int) operands_.size(); }
    Stmt* Stmt::get_operand(int i) const {
        check_operands_at(i);
        return operands_[i];
    }
    void Stmt::add_operand(Stmt* stmt) { operands_.push_back(stmt); }
    void Stmt::set_operand(int i, Stmt* stmt) {
        check_operands_at(i);
        operands_[i] = stmt;
    }
    void Stmt::check_operands_at(int i) const {
        OP_ASSERT_MSG(operands_.size() > i, "Stmt {} only have {} operands. Trying to index at {}.",
                      get_name(), num_operands(), i);
    }

    void Stmt::check_cast(bool is, const std::string& target_type) const {
        OP_ASSERT_MSG(is, "Cannot cast stmt of type {} to {}", this->type_name(), target_type);
    }

    bool Stmt::operator==(const Stmt& other) const { return id_ == other.id_; }

    void Stmt::accept(IRVisitor* visitor) { visitor->visit(this); }
}// namespace OpFlow::lang