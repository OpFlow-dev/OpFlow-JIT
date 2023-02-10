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

#ifndef OPFLOW_JIT_INDEX_HPP
#define OPFLOW_JIT_INDEX_HPP

#include <initializer_list>
#include <vector>

namespace OpFlow::lang {
    class Index {
    public:
        Index() = default;

        Index(std::initializer_list<int> list) : indexes_(list) {}

        [[nodiscard]] std::size_t dim() const { return indexes_.size(); }

    private:
        std::vector<int> indexes_;
    };
}// namespace OpFlow::lang

#endif//OPFLOW_JIT_INDEX_HPP
