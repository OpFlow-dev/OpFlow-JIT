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

#ifndef OPFLOW_JIT_IRPRINTER_HPP
#define OPFLOW_JIT_IRPRINTER_HPP

#include "lang/pass/IRVisitor.hpp"

namespace OpFlow::lang {
    class IRPrinter : public virtual IRVisitor {
    public:
        void visit(IRNode *irNode) const override;

        static void run(IRNode* root);
    };
}

#endif//OPFLOW_JIT_IRPRINTER_HPP
