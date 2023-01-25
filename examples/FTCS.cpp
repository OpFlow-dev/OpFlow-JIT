// ----------------------------------------------------------------------------
//
// Copyright (c) 2019 - 2022 by the OpFlow developers
//
// This file is part of OpFlow.
//
// OpFlow is free software and is distributed under the MPL v2.0 license.
// The full text of the license can be found in the file LICENSE at the top
// level directory of OpFlow.
//
// ----------------------------------------------------------------------------

#include <OpFlow>

using namespace OpFlow;

int main(int argc, char** argv) {
    // init environment
    OpFlow::init(Arch::x86_64);
    // declare meshes
    auto mesh = MeshBuilder<CartesianMesh>().build();
    CartesianField u, v, w;
    u.placeAt(mesh, center);
    v.placeAt(mesh, center);
    w.placeAt(mesh, corner);

}