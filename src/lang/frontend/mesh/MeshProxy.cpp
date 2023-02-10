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

#include "MeshProxy.hpp"
#include "lang/frontend/Field.hpp"

namespace OpFlow::lang {
    MeshLocDescriptor::MeshLocDescriptor() = default;

    MeshProxy::MeshProxy(const Mesh *mesh, MeshLocDescriptor descriptor)
        : mesh_(mesh), descriptor_(descriptor) {}

    void MeshProxy::place(Field &field) { field.bind_to_mesh(this->mesh_, this->descriptor_); }

    void MeshProxy::place(FieldGroup &fieldGroup) {
        for (auto &f : fieldGroup) { place(*f); }
    }
}// namespace OpFlow::lang