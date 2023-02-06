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

#ifndef OPFLOW_JIT_MESHLOCDESCRIPTOR_HPP
#define OPFLOW_JIT_MESHLOCDESCRIPTOR_HPP

namespace OpFlow::lang {
    enum class LocOnMesh { Cell, Edge, Vertex, Undefined };
    enum class Position { start, end };

    class Mesh;

    class MeshLocDescriptor {
    public:
        MeshLocDescriptor();
        explicit MeshLocDescriptor(const Mesh* mesh, LocOnMesh loc) : base_mesh_(mesh), loc_(loc) {}

    private:
        LocOnMesh loc_ = LocOnMesh::Undefined;
        const Mesh* base_mesh_ = nullptr;
    };
}// namespace OpFlow::lang

#endif//OPFLOW_JIT_MESHLOCDESCRIPTOR_HPP
