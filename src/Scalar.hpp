// ----------------------------------------------------------------------------
//
// Copyright (c) 2019 - 2023 by the OpFlow developers
//
// This file is part of OpFlow.
//
// OpFlow is free software and is distributed under the MPL v2.0 license.
// The full text of the license can be found in the file LICENSE at the top
// level directory of OpFlow.
//
// ----------------------------------------------------------------------------

#ifndef OPFLOW_JIT_SCALAR_HPP
#define OPFLOW_JIT_SCALAR_HPP

#include "DataType.hpp"
#include "Variable.hpp"

namespace OpFlow {

    class Scalar : public virtual Var {
    public:
        Scalar();
        Scalar(const Scalar& other);
        ~Scalar() override = default;

        Scalar& operator=(const Scalar& other);
        Scalar& operator=(const Expr& other);

        template <typename T = void>
        void bind(T* data) {
            this->elem_type_ = get_runtime_type(*data);
            data_ = data;
        }

    private:
        void* data_ = nullptr;
    };
}// namespace OpFlow

#endif//OPFLOW_JIT_SCALAR_HPP
