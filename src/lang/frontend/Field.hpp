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

#ifndef OPFLOW_JIT_FIELD_HPP
#define OPFLOW_JIT_FIELD_HPP

#include "Variable.hpp"
#include "lang/frontend/bc/Boundary.hpp"
#include "lang/frontend/mesh/BoundaryDescriptor.hpp"
#include "lang/frontend/mesh/MeshLocDescriptor.hpp"
#include <memory>
#include <vector>

namespace OpFlow::lang {
    class Field : public virtual Var {
    public:
        ~Field() override = default;

        explicit Field(DataType dt);

        Field& set_bc(BoundaryDescriptor* descriptor, std::unique_ptr<BC>&& bc);

        void bind_to_mesh(const Mesh* mesh, const MeshLocDescriptor& descriptor);

        Field& operator=(const Expr& other) override;

    private:
        const Mesh* mesh_ = nullptr;
        MeshLocDescriptor mesh_loc_descriptor_;
    };

    class FieldGroup {
    public:
        FieldGroup();
        FieldGroup(Field& f);

        FieldGroup operator,(Field& f) const&;

        std::vector<Field*>::iterator begin();
        std::vector<Field*>::iterator end();

        [[nodiscard]] std::vector<Field*>::const_iterator begin() const;
        [[nodiscard]] std::vector<Field*>::const_iterator end() const;

    private:
        std::vector<Field*> fields_;
    };
}// namespace OpFlow::lang

#endif//OPFLOW_JIT_FIELD_HPP
