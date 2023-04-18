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

#include "Mesh.hpp"
#include "utils/Macros.hpp"

namespace OpFlow::lang {
    Mesh::Mesh() = default;
    Mesh::~Mesh() noexcept = default;
    MeshProxy Mesh::location(LocOnMesh loc) { return {this, loc}; }

    bool Mesh::is_dynamic() const { return is_dynamic_; }
    void Mesh::mark_as_dynamic() { is_dynamic_ = true; }

    void layout(const std::function<void()> &describer) { describer(); }
}// namespace OpFlow::lang