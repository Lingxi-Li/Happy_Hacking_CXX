// Copyright (c) 2016, Lingxi Li <lilingxi.cs@gmail.com>
// All rights reserved.
// Happy Hacking CXX Library (https://github.com/Lingxi-Li/Happy_Hacking_CXX)

#include <hhxx/scope_guard.hpp>

#include <utility>

#include <gtest/gtest.h>

TEST(macro, basic) {
  int i = 0;
  {
    HHXX_ON_SCOPE_EXIT_F([&] {
      EXPECT_EQ(4, ++i);
    });
    HHXX_ON_SCOPE_EXIT_F([&] {
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

TEST(clazz, basic) {
  using hhxx::make_scope_guard;
  int i = 0;
  {
    auto guard4 = make_scope_guard([&] { EXPECT_EQ(3, ++i); });
    auto guard3 = make_scope_guard([&] { EXPECT_EQ(2, ++i); });
    auto guard2 = make_scope_guard([&] { EXPECT_EQ(2, ++i); });
    auto guard1 = make_scope_guard([&] { EXPECT_EQ(1, ++i); });
    guard2.disarm();
    auto tmp = std::move(guard4);
    tmp.disarm();
  }
  EXPECT_EQ(2, i);
}
