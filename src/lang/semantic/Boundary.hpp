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

#ifndef OPFLOW_JIT_BOUNDARY_HPP
#define OPFLOW_JIT_BOUNDARY_HPP

namespace OpFlow {
    class BoundaryDescriptor {};

    enum class BCType { Dirc, Neum, Robin };

    class BC {
    public:
        BC() = default;

        virtual BCType get_type() const = 0;
    };

    class DircBC : public virtual BC {
    public:
        explicit DircBC(double value);
        [[nodiscard]] BCType get_type() const override;

    private:
        double value_ = 0;
    };

    class NeumBC : public virtual BC {
    public:
        explicit NeumBC(double value);
        [[nodiscard]] BCType get_type() const override;

    private:
        double value_ = 0;
    };
}// namespace OpFlow

#endif//OPFLOW_JIT_BOUNDARY_HPP
