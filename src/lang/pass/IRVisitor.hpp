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

#ifndef OPFLOW_JIT_IRVISITOR_HPP
#define OPFLOW_JIT_IRVISITOR_HPP

namespace OpFlow::lang {
    class IRNode;
    class IRVisitor {
    public:
        virtual void visit(IRNode* irNode) const = 0;
    };
}// namespace OpFlow::lang

#endif//OPFLOW_JIT_IRVISITOR_HPP
