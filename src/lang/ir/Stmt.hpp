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

#ifndef OPFLOW_JIT_STMT_HPP
#define OPFLOW_JIT_STMT_HPP

#include "lang/ir/IRNode.hpp"

namespace OpFlow::lang {
    class Block;

    class Stmt : public virtual IRNode {
    public:
        Stmt();
        ~Stmt() noexcept override;
        Stmt(const Stmt&) = delete;
        Stmt(Stmt&&) = default;
        Stmt& operator=(const Stmt&) = delete;
        Stmt& operator=(Stmt&&) = default;

        [[nodiscard]] std::string type_name() const override;

        Block* get_parent_block();
        [[nodiscard]] const Block* get_parent_block() const;
        void set_parent(Block* parent);

        [[nodiscard]] std::string get_name() const;
        [[nodiscard]] std::string get_raw_name() const;

        [[nodiscard]] std::vector<Stmt*> get_operands() const;
        [[nodiscard]] int num_operands() const;
        [[nodiscard]] Stmt* get_operand(int i) const;
        void add_operand(Stmt* stmt);
        void set_operand(int i, Stmt* stmt);

        template <typename T>
        [[nodiscard]] bool is() const {
            return dynamic_cast<std::add_pointer_t<std::add_const_t<T>>>(this);
        }

        template <typename T>
        [[nodiscard]] auto as() const {
            check_cast(is<T>(), std::is_base_of_v<Stmt, T> ? T {}.type_name() : "NaStmt");
            return dynamic_cast<std::add_pointer_t<std::add_const_t<T>>>(this);
        }

        bool operator==(const Stmt& other) const;

        void accept(IRVisitor* visitor) override;

    protected:
        void check_operands_at(int i) const;
        // check the cast pointer is valid; used to avoid introducing "utils/Macros.hpp" in headers
        void check_cast(bool is, const std::string& target_type) const;

        Block* parent_ = nullptr;
        int id_ = -1;
        static std::atomic_int instance_counter_;
        std::vector<Stmt*> operands_;
    };
}// namespace OpFlow::lang

#endif//OPFLOW_JIT_STMT_HPP
