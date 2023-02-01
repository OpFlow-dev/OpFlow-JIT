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

#include "Field.hpp"

namespace OpFlow {
    Field::Field(DataType dt) { this->elem_type_ = dt; }

    Field& Field::set_bc(BoundaryDescriptor descriptor, std::unique_ptr<BC>&& bc) { return *this; }

    Var& Field::operator=(const Expr& other) { return *this; }
}// namespace OpFlow