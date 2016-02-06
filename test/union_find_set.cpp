// Copyright (c) 2016, Lingxi Li <lilingxi.cs@gmail.com>
// All rights reserved.
// Happy Hacking CXX Library (https://github.com/Lingxi-Li/Happy_Hacking_CXX)

#include <hhxx/union_find_set.hpp>

#include <gtest/gtest.h>

TEST(find_unite_reset, basic) {
  using hhxx::union_find_set;
  using key_type = union_find_set::key_type;
  union_find_set ufset;
  // find
  key_type key = 0;
  for (key = 0; key < 5; ++key) {
    EXPECT_EQ(key, ufset.find(key));
  }
  // unite
  EXPECT_EQ(0u, ufset.unite(0, 1));
  EXPECT_EQ(2u, ufset.unite(2, 3));
  EXPECT_EQ(2u, ufset.unite(3, 4));
  EXPECT_EQ(2u, ufset.unite(1, 4));
  // reset
  for (key = 0; key < 5; ++key) {
    EXPECT_EQ(2u, ufset.find(key));
  }
  ufset.reset();
  for (key = 0; key < 5; ++key) {
    EXPECT_EQ(key, ufset.find(key));
  }
}
