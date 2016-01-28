// Copyright (c) 2016, Lingxi Li <lilingxi.cs@gmail.com>
// All rights reserved.
// Happy Hacking CXX Library (https://github.com/Lingxi-Li/Happy_Hacking_CXX)

#include <hhxx/scope_guard.hpp>
#include <hhxx/scope_guard.hpp>

#include <gtest/gtest.h>

TEST(scope_guard, basic) {
  int i = 0;
  {
    HHXX_ON_SCOPE_EXIT_F([&]() {
      EXPECT_EQ(4, ++i);
    });
    HHXX_ON_SCOPE_EXIT_F([&]() {
      EXPECT_EQ(3, ++i);
    });
    HHXX_ON_SCOPE_EXIT(
      EXPECT_EQ(2, ++i);
    );
    HHXX_ON_SCOPE_EXIT(
      EXPECT_EQ(1, ++i);
    );
  }
  EXPECT_EQ(4, i);
}
