// ----------------------------------------------------------------------------
//
// Copyright (c) 2019 - 2022 by the OpFlow developers
//
// This file is part of OpFlow-JIT.
//
// OpFlow-JIT is free software and is distributed under the Apache-2.0 license.
// The full text of the license can be found in the file LICENSE at the top
// level directory of OpFlow-JIT.
//
// ----------------------------------------------------------------------------

#include <OpFlow.hpp>
#include <iostream>
#include <lang/OpLang.hpp>

using namespace OpFlow;
using namespace OpFlow::lang;

int main(int argc, char** argv) {
    // init environment
    Environment::init(argc, argv);
    Environment::setMode(OpFlow::Arch::x86_64, OpFlow::Para::SingleNode);

    // declare meshes
    auto mesh = MeshBuilder<CartesianMesh>().build();

    Field u(DataType::f32), p(DataType::f64);

    layout([&] { mesh.location(LocOnMesh::Cell).place(p); });

    p.set_bc(mesh.get_boundary(0, Position::start).get(), std::make_unique<DircBC>(0.));
    p.set_bc(mesh.get_boundary(0, Position::end).get(), std::make_unique<NeumBC>(0.));

    double alpha = 1.0, dt = 1.0;
    Expr lhs, rhs;
    lhs += u;
    // rhs += FDM::d2x(u);
    rhs *= Scalar(alpha * dt);
    Solve(lhs == rhs, Solver {});

    //auto cal = KernelBuilder().def([&] { u = Scalar(0.1 * dt) * FDM::d2x(u); });

    //cal();

    std::cout << u.val<double>({10});

    //dump_to_file(u);

    return 0;
}