//  ----------------------------------------------------------------------------
//
//  Copyright (c) 2019 - 2023 by the OpFlow developers
//
//  This file is part of OpFlow-JIT.
//
//  OpFlow is free software and is distributed under the Apache-2.0 license.
//  The full text of the license can be found in the file LICENSE at the top
//  level directory of OpFlow-JIT.
//
//  ----------------------------------------------------------------------------

#include <OpFlow>
#include <gmock/gmock.h>

int main(int argc, char** argv) {
    // Filter out Google Test arguments
    ::testing::InitGoogleTest(&argc, argv);

    // Initialize environment
    OpFlow::EnvironmentGardian _(&argc, &argv);

    // Run tests, then clean up and exit. RUN_ALL_TESTS() returns 0 if all tests
    // pass and 1 if some test fails.
    int result = RUN_ALL_TESTS();

    return result;
}