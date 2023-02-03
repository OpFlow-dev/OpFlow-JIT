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
    MeshLocProxy::MeshLocProxy() = default;

    void MeshLocProxy::place(Field &field) { OP_NOT_IMPLEMENTED; }

    void MeshLocProxy::place(FieldGroup &fieldGroup) {
        for (auto &f : fieldGroup) { place(*f); }
    }

    Mesh::Mesh() = default;
    Mesh::~Mesh() noexcept = default;
    MeshLocProxy Mesh::location(LocOnMesh loc) { return MeshLocProxy(this, loc); }
    bool Mesh::is_dynamic() const { return is_dynamic_; }
    void Mesh::mark_as_dynamic() { is_dynamic_ = true; }

    void layout(const std::function<void()> &describer) {
        describer();
        OP_NOT_IMPLEMENTED;
    }
}// namespace OpFlow::lang