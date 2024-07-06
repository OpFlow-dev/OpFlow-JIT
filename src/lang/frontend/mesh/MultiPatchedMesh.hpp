// ----------------------------------------------------------------------------
//
// Copyright (c) 2019 - 2024 by the OpFlow developers
//
// This file is part of OpFlow-JIT.
//
// OpFlow-JIT is free software and is distributed under the Apache-2.0 license.
// The full text of the license can be found in the file LICENSE at the top
// level directory of OpFlow-JIT.
//
// ----------------------------------------------------------------------------

#ifndef OPFLOW_JIT_MULTIPATCHEDMESH_HPP
#define OPFLOW_JIT_MULTIPATCHEDMESH_HPP

#include "Mesh.hpp"

namespace OpFlow::lang {
    class MultiPatchedMesh : public virtual Mesh {
    public:
        ~MultiPatchedMesh() noexcept override;
    };
}// namespace OpFlow::lang

#endif//OPFLOW_JIT_MULTIPATCHEDMESH_HPP
