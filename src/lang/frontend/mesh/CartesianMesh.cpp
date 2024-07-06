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

#include "CartesianMesh.hpp"
#include "utils/Macros.hpp"

namespace OpFlow::lang {
    CartesianMesh::~CartesianMesh() noexcept = default;

    int CartesianMesh::dimension() const { return index_dimension(); }
    int CartesianMesh::index_dimension() const { return (int) coord_.size(); }

    std::unique_ptr<Mesh> CartesianMesh::clone() const { return std::make_unique<CartesianMesh>(*this); }

    double CartesianMesh::x(int d, int pos) const { return coord_[d][pos]; }
    bool CartesianMesh::is_uniform(int d) const { return is_uniform_[d]; }

    std::vector<std::unique_ptr<BoundaryDescriptor>> CartesianMesh::get_boundaries() const {
        std::vector<std::unique_ptr<BoundaryDescriptor>> ret;
        for (int i = 0; i < dimension(); ++i) {
            for (auto pos : {Position::start, Position::end}) ret.push_back(get_boundary(i, pos));
        }
        return ret;
    }

    std::unique_ptr<BoundaryDescriptor> CartesianMesh::get_boundary(int d, Position pos) const {
        return std::make_unique<CartMeshBoundary>(*this, d, pos);
    }

    using Builder = MeshBuilder<CartesianMesh>;

    Builder::MeshBuilder() = default;

    MeshBuilder<CartesianMesh>& Builder ::new_mesh(std::initializer_list<int> sizes) {
        mesh_.coord_.clear();
        for (auto s : sizes) { mesh_.coord_.emplace_back(s); }
        return *this;
    }

    MeshBuilder<CartesianMesh>& Builder ::set_mesh_of_dim(int dim, double start, double end) {
        double dx = (end - start) / ((double) mesh_.coord_[dim].size() - 1);
        for (int i = 0; i < mesh_.coord_[dim].size(); ++i) { mesh_.coord_[dim][i] = start + i * dx; }
        mesh_.is_uniform_[dim] = true;
        return *this;
    }

    MeshBuilder<CartesianMesh>& Builder ::set_mesh_of_dim(int dim,
                                                          const std::function<double(int)>& generator) {
        for (int i = 0; i < mesh_.coord_[dim].size(); ++i) { mesh_.coord_[dim][i] = generator(i); }
        bool uniform = true;
        for (int i = 0; i < mesh_.coord_[dim].size() - 2; ++i) {
            uniform &= (mesh_.x(dim, i + 1) - mesh_.x(dim, i)) == (mesh_.x(dim, i + 2) - mesh_.x(dim, i + 1));
        }
        mesh_.is_uniform_[dim] = uniform;
        return *this;
    }

    CartesianMesh Builder ::build() const { return mesh_; }

    CartMeshBoundary::CartMeshBoundary() = default;
    CartMeshBoundary::CartMeshBoundary(const CartesianMesh& mesh, int d, Position pos)
        : mesh_(&mesh), d_(d), pos_(pos) {}
}// namespace OpFlow::lang