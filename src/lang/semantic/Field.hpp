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

#ifndef OPFLOW_JIT_FIELD_HPP
#define OPFLOW_JIT_FIELD_HPP

#include "Boundary.hpp"
#include "Variable.hpp"
#include <memory>

namespace OpFlow {
    class Field : public virtual Var {
    public:
        ~Field() override = default;

        explicit Field(DataType dt);

        Field& set_bc(BoundaryDescriptor descriptor, std::unique_ptr<BC>&& bc);

        Var& operator=(const Expr& other) override;
    };
}// namespace OpFlow

#endif//OPFLOW_JIT_FIELD_HPP
