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

        void accept(IRVisitor *visitor) override;

    private:
        std::vector<std::unique_ptr<Stmt>> statements_;
    };
}// namespace OpFlow::lang

#endif//OPFLOW_JIT_BLOCK_HPP
