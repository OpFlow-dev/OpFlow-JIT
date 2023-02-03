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

#include "lang/OpLang.hpp"
#include <gmock/gmock.h>

TEST(ScalarTest, DeclearTest) {
    OpFlow::Scalar a {1.0};
    ASSERT_TRUE(true);
}