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

#ifndef OPFLOW_JIT_ENVIRONMENT_HPP
#define OPFLOW_JIT_ENVIRONMENT_HPP

namespace OpFlow {
    enum class Arch { x86_64, CUDA };
    enum class Para { SingleNode, Cluster };

    void init(Arch arch, Para para);
}// namespace OpFlow

#endif//OPFLOW_JIT_ENVIRONMENT_HPP
