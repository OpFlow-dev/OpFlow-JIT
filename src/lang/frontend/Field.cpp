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

#include "Field.hpp"

namespace OpFlow::lang {
    Field::Field(DataType dt) { this->elem_type_ = dt; }

    Field& Field::set_bc(BoundaryDescriptor* descriptor, std::unique_ptr<BC>&& bc) { return *this; }

    void Field::bind_to_mesh(const Mesh* mesh, LocOnMesh loc) {
        mesh_ = mesh;
        loc_ = loc;
    }

    Field& Field::operator=(const Expr& other) { return *this; }

    FieldGroup::FieldGroup() = default;

    FieldGroup::FieldGroup(Field& f) : fields_ {&f} {}

    FieldGroup FieldGroup::operator,(Field&f) const & {
        auto ret = *this;
        ret.fields_.push_back(&f);
        return ret;
    }

    std::vector<Field*>::iterator FieldGroup::begin() { return fields_.begin(); }

    std::vector<Field*>::iterator FieldGroup::end() { return fields_.end(); }

    std::vector<Field*>::const_iterator FieldGroup::begin() const { return fields_.begin(); }

    std::vector<Field*>::const_iterator FieldGroup::end() const { return fields_.end(); }
}// namespace OpFlow::lang