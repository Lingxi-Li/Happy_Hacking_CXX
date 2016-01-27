// Copyright (c) 2016, Lingxi Li <lilingxi.cs@gmail.com>
// All rights reserved.
// Happy Hacking CXX Library (https://github.com/Lingxi-Li/Happy_Hacking_CXX)

#include <hhxx/multi_view.hpp>
#include <hhxx/multi_view.hpp>

#include <numeric>
#include <vector>

#include <gtest/gtest.h>

TEST(multi_view, basic) {
  using view = hhxx::multi_view<std::vector<int>::iterator>;
  std::vector<int> vec(8);
  std::iota(vec.begin(), vec.end(), 1);
  view view8(vec.begin(), 8);
  for (auto i = 0; i < 8; ++i) {
    EXPECT_EQ(i + 1, view8(i));
  }
  view view2x4(vec.begin(), 2, 4);
  for (auto i = 0; i < 4; ++i) {
    EXPECT_EQ(i + 1, view2x4(0, i));
  }
  for (auto i = 0; i < 4; ++i) {
    EXPECT_EQ(5 + i, view2x4(1, i));
  }
  view view2x2x2(vec.begin(), 2, 2, 2);
  EXPECT_EQ(1, view2x2x2(0, 0, 0));
  EXPECT_EQ(2, view2x2x2(0, 0, 1));
  EXPECT_EQ(3, view2x2x2(0, 1, 0));
  EXPECT_EQ(4, view2x2x2(0, 1, 1));
  EXPECT_EQ(5, view2x2x2(1, 0, 0));
  EXPECT_EQ(6, view2x2x2(1, 0, 1));
  EXPECT_EQ(7, view2x2x2(1, 1, 0));
  EXPECT_EQ(8, view2x2x2(1, 1, 1));
  EXPECT_EQ(5, view2x2x2(1));
  EXPECT_EQ(5, view2x2x2(1, 0, 0, 100));
}
