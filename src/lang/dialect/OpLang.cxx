#include "OpLangDialect.hpp"
#include "OpLangOps.hpp"

#include "OpLangDialect.cpp.inc"
#define GET_OP_CLASSES
#include "OpLang.cpp.inc"
#undef GET_OP_CLASSES

using namespace mlir;
using namespace OpFlow::lang;

void OpLangDialect::initialize() {
    addOperations<
#define GET_OP_LIST
#include "OpLang.cpp.inc"
#undef GET_OP_LIST
    >();
}