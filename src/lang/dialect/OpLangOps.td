#ifndef OPLANG_OPS_TD
#define OPLANG_OPS_TD

include "mlir/IR/OpBase.td"
include "OpLangDialect.td"
include "mlir/Interfaces/SideEffectInterfaces.td"

class OpOp<string mnemonic, list<Trait> traits = []> :
    Op<OpLangDialect, mnemonic, traits>;



#endif
