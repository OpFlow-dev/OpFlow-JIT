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

#ifndef OPFLOW_JIT_CARTESIANMESH_HPP
#define OPFLOW_JIT_CARTESIANMESH_HPP

#include "StructuredMesh.hpp"
#include "lang/frontend/mesh/MeshLocDescriptor.hpp"
#include <vector>

namespace OpFlow::lang {
    class CartesianMesh : public virtual StructuredMesh {
    public:
        ~CartesianMesh() noexcept override;
        [[nodiscard]] int dimension() const override;
        [[nodiscard]] int index_dimension() const override;
        [[nodiscard]] std::unique_ptr<Mesh> clone() const override;

        [[nodiscard]] double x(int d, int pos) const;
        [[nodiscard]] bool is_uniform(int d) const;
        [[nodiscard]] std::vector<std::unique_ptr<BoundaryDescriptor>> get_boundaries() const override;
        [[nodiscard]] std::unique_ptr<BoundaryDescriptor> get_boundary(int d, Position pos) const;

        friend MeshBuilder<CartesianMesh>;

    private:
        std::vector<std::vector<double>> coord_;
        std::vector<bool> is_uniform_;
    };

    template <>
    class MeshBuilder<CartesianMesh> {
    public:
        MeshBuilder();

        MeshBuilder& new_mesh(std::initializer_list<int> sizes);
        MeshBuilder& set_mesh_of_dim(int dim, double start, double end);
        MeshBuilder& set_mesh_of_dim(int dim, const std::function<double(int)>& generator);
        [[nodiscard]] CartesianMesh build() const;

    private:
        CartesianMesh mesh_;
    };

    class CartMeshBoundary : public virtual BoundaryDescriptor {
    public:
        CartMeshBoundary();
        CartMeshBoundary(const CartesianMesh& mesh, int d, Position pos);

    private:
        const CartesianMesh* mesh_ = nullptr;
        int d_ = 0;
        Position pos_ = Position::start;
    };
}// namespace OpFlow::lang

#endif//OPFLOW_JIT_CARTESIANMESH_HPP
