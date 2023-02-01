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

#include "Boundary.hpp"

namespace OpFlow {
    DircBC::DircBC(double value) : value_(value) {}
    BCType DircBC::get_type() const { return BCType::Dirc; }

    NeumBC::NeumBC(double value) : value_(value) {}
    BCType NeumBC::get_type() const { return BCType::Neum; }
}// namespace OpFlow