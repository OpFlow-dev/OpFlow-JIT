#ifndef OP_DIALECT_TD
#define OP_DIALECT_TD

include "mlir/IR/OpBase.td"

def OpLangDialect : Dialect {
    let name = "OpLang";
    let cppNamespace = "::OpFlow::lang";
    let summary = "OpLang Dialect";
    let useDefaultTypePrinterParser = true;
    let 
}

#endif