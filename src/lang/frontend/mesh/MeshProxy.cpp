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

#include "MeshProxy.hpp"
#include "lang/frontend/Field.hpp"

namespace OpFlow::lang {
    MeshProxy::MeshProxy(const Mesh *mesh, LocOnMesh loc) : mesh_(mesh), loc_(loc) {}

    void MeshProxy::place(Field &field) { field.bind_to_mesh(this->mesh_, this->loc_); }

    void MeshProxy::place(FieldGroup &fieldGroup) {
        for (auto &f : fieldGroup) { place(*f); }
    }
}// namespace OpFlow::lang