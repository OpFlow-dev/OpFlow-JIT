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

#ifndef OPFLOW_JIT_MESH_HPP
#define OPFLOW_JIT_MESH_HPP

#include "lang/frontend/Field.hpp"
#include "lang/frontend/bc/Boundary.hpp"
#include "lang/frontend/mesh/BoundaryDescriptor.hpp"
#include "lang/frontend/mesh/MeshProxy.hpp"
#include "utils/Prototypes.hpp"
#include <functional>

namespace OpFlow::lang {
    class Mesh : public virtual internal::cloneable_object<Mesh> {
    public:
        Mesh();
        virtual ~Mesh() noexcept;

        MeshProxy location(LocOnMesh loc);
        [[nodiscard]] bool is_dynamic() const;
        void mark_as_dynamic();

        [[nodiscard]] virtual int dimension() const = 0;
        [[nodiscard]] virtual int index_dimension() const = 0;
        [[nodiscard]] virtual std::vector<std::unique_ptr<BoundaryDescriptor>> get_boundaries() const = 0;

    protected:
        bool is_dynamic_ = false;
    };

    template <typename M>
    class MeshBuilder;

    void layout(const std::function<void()>& describer);
}// namespace OpFlow::lang

#endif//OPFLOW_JIT_MESH_HPP
