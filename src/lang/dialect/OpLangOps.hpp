#ifndef OPFLOW_JIT_OPLANG_OPS_HPP
#define OPFLOW_JIT_OPLANG_OPS_HPP

#include <mlir/IR/Builders.h>
#include <mlir/IR/BuiltinOps.h>

#include "OpLangDialect.hpp"
#include <mlir/Interfaces/SideEffectInterfaces.h>

#define GET_OP_CLASSES
#include "OpLang.h.inc"
#undef GET_OP_CLASSES

#endif