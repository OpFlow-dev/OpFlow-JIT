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

    class Environment {
    public:
        static void init(int argc, char** argv);

        static void setMode(Arch arch, Para para);

    private:
        Environment() = default;
        static Environment& getInstance();
        Arch arch_ = Arch::x86_64;
        Para para_ = Para::SingleNode;
    };
}// namespace OpFlow

#endif//OPFLOW_JIT_ENVIRONMENT_HPP
