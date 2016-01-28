// Copyright (c) 2016, Lingxi Li <lilingxi.cs@gmail.com>
// All rights reserved.
// Happy Hacking CXX Library (https://github.com/Lingxi-Li/Happy_Hacking_CXX)

#include <hhxx/multi_view.hpp>
#include <hhxx/multi_view.hpp>

#include <algorithm>
#include <iterator>
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
  const int idx = 0;
  EXPECT_EQ(8, std::distance(std::begin(view8), std::end(view8)));
  std::for_each(std::begin(view8), std::end(view8),
    [idx = idx](int x) mutable {
      EXPECT_EQ(++idx, x);
    });
  view view2x4(vec.begin(), 2, 4);
  for (auto i = 0; i < 4; ++i) {
    EXPECT_EQ(i + 1, view2x4(0, i));
  }
  EXPECT_EQ(4, std::distance(view2x4.begin(0), view2x4.end(0)));
  std::for_each(view2x4.begin(0), view2x4.end(0),
    [idx = idx](int x) mutable {
      EXPECT_EQ(++idx, x);
    });
  for (auto i = 0; i < 4; ++i) {
    EXPECT_EQ(5 + i, view2x4(1, i));
  }
  EXPECT_EQ(4, std::distance(view2x4.begin(1), view2x4.end(1)));
  std::for_each(view2x4.begin(1), view2x4.end(1),
    [idx = idx](int x) mutable {
      EXPECT_EQ(++idx + 4, x);
    });
  auto view2x2x2 = hhxx::make_multi_view(vec.begin(), 2, 2, 2);
  EXPECT_EQ(1, view2x2x2(0, 0, 0));
  EXPECT_EQ(2, view2x2x2(0, 0, 1));
  EXPECT_EQ(3, view2x2x2(0, 1, 0));
  EXPECT_EQ(4, view2x2x2(0, 1, 1));
  EXPECT_EQ(5, view2x2x2(1, 0, 0));
  EXPECT_EQ(6, view2x2x2(1, 0, 1));
  EXPECT_EQ(7, view2x2x2(1, 1, 0));
  EXPECT_EQ(8, view2x2x2(1, 1, 1));
  EXPECT_EQ(2, std::distance(view2x2x2.begin(1, 1), view2x2x2.end(1, 1)));
  std::for_each(view2x2x2.begin(1, 1), view2x2x2.end(1, 1),
    [idx = idx](int x) mutable {
      EXPECT_EQ(++idx + 6, x);
    });
  EXPECT_EQ(1, view2x2x2());
  EXPECT_EQ(5, view2x2x2(1));
}
