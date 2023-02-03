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

#ifndef OPFLOW_JIT_MESHES_HPP
#define OPFLOW_JIT_MESHES_HPP

#include "lang/semantic/Boundary.hpp"
#include "lang/semantic/Field.hpp"
#include <functional>

namespace OpFlow {
    enum class Loc { CellCenter, EdgeCenter, Vertex, Undefined };

    class GeneralMesh;

    class MeshLocProxy {
    public:
        MeshLocProxy() = default;
        explicit MeshLocProxy(GeneralMesh* mesh, Loc loc) : mesh_(mesh), loc_(loc) {}

        void place(Field& field);

    private:
        Loc loc_ = Loc::Undefined;
        GeneralMesh* mesh_ = nullptr;
    };

    class GeneralMesh {
    public:
        MeshLocProxy location(Loc loc) { return MeshLocProxy(this, loc); }
    };

    class StructuredMesh : public virtual GeneralMesh {};

    class UnstructuredMesh : public virtual GeneralMesh {};

    enum class Position { start, end };

    class CartesianMesh : public virtual StructuredMesh {
    public:
        class Builder {
        public:
            CartesianMesh build() { return {}; }
        };

        BoundaryDescriptor get_boundary(int dim, Position pos) const;
    };

    void layout(std::function<void()> describer);
}// namespace OpFlow

#endif//OPFLOW_JIT_MESHES_HPP
