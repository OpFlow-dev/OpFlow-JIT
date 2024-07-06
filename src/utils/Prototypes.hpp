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

#ifndef OPFLOW_JIT_PROTOTYPES_HPP
#define OPFLOW_JIT_PROTOTYPES_HPP

#include <memory>

namespace OpFlow::internal {
    template <typename T>
    class cloneable_object {
    public:
        virtual std::unique_ptr<T> clone() const = 0;
    };
}// namespace OpFlow::internal

#endif//OPFLOW_JIT_PROTOTYPES_HPP
