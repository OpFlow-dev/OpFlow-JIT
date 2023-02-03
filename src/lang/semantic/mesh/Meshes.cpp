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

#include "Meshes.hpp"
#include "utils/Macros.hpp"

namespace OpFlow {
    void MeshLocProxy::place(Field &field) { OP_NOT_IMPLEMENTED; }

    BoundaryDescriptor CartesianMesh::get_boundary(int dim, Position pos) const {
        return BoundaryDescriptor {};
    }

    void layout(std::function<void()> describer) { OP_NOT_IMPLEMENTED; }
}// namespace OpFlow