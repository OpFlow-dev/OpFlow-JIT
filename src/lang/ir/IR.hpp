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

#ifndef OPFLOW_JIT_IR_HPP
#define OPFLOW_JIT_IR_HPP

namespace OpFlow {
    class IRVisitor;

    class IRNode {
    public:
        IRNode() = default;
        virtual ~IRNode() = default;

        virtual void accept(IRVisitor* visitor) const = 0;
    };

    class Stmt : public virtual IRNode {};
}// namespace OpFlow

#endif//OPFLOW_JIT_IR_HPP
