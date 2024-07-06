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

#ifndef OPFLOW_JIT_SCALAR_HPP
#define OPFLOW_JIT_SCALAR_HPP

#include "DataType.hpp"
#include "Variable.hpp"

namespace OpFlow::lang {
    class Scalar : public virtual Var {
    public:
        Scalar();
        Scalar(const Scalar& other);
        ~Scalar() override = default;

        explicit Scalar(double d);
        explicit Scalar(float f);

        Scalar& operator=(const Scalar& other);
        Var& operator=(const Expr& other) override;

        template <typename T = void>
        void bind(T* data) {
            this->elem_type_ = get_runtime_type(*data);
            data_ = data;
        }

    private:
        void* data_ = nullptr;
    };
}// namespace OpFlow::lang

#endif//OPFLOW_JIT_SCALAR_HPP
