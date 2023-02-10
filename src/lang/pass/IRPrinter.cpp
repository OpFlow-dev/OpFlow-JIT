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

#include "IRPrinter.hpp"
#include "lang/ir/IRNode.hpp"
#include "utils/Macros.hpp"
#include <fmt/format.h>

namespace OpFlow::lang {
    void IRPrinter::visit(IRNode *irNode) const {
        OP_ERROR(
                "Default visit method of IRPrinter called. IRNode of type {}'s visit method not implemented.",
                irNode->type_name());
    }

    void IRPrinter::run(IRNode *root) {
        IRPrinter printer;
        printer.visit(root);
    }
}// namespace OpFlow::lang