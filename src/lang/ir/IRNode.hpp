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

#ifndef OPFLOW_JIT_IRNODE_HPP
#define OPFLOW_JIT_IRNODE_HPP

#include "lang/pass/IRVisitor.hpp"
#include <atomic>
#include <string>
#include <type_traits>
#include <vector>

namespace OpFlow::lang {
    class IRNode {
    public:
        IRNode() = default;
        virtual ~IRNode() noexcept = default;

        virtual void accept(IRVisitor* visitor) = 0;
        [[nodiscard]] virtual std::string type_name() const { return "IRNode"; }
    };
}// namespace OpFlow::lang

#endif//OPFLOW_JIT_IRNODE_HPP
