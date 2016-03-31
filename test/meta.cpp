// Copyright (c) 2016, Lingxi Li <lilingxi.cs@gmail.com>
// All rights reserved.
// Happy Hacking CXX Library (https://github.com/Lingxi-Li/Happy_Hacking_CXX)

#include <hhxx/meta.hpp>

#include <memory>
#include <random>
#include <vector>

#include <gtest/gtest.h>

TEST(enable_if_well_formed, basic) {
  using hhxx::enable_if_well_formed_t;
  static_assert(std::is_same<void, enable_if_well_formed_t<decltype(0)>>::value, "");
  static_assert(std::is_same<int, enable_if_well_formed_t<decltype(0), int>>::value, "");
}

TEST(multi_array, basic) {
  using hhxx::multi_array_t;
  using array1d = std::array<int, 1>;
  using array2d = std::array<array1d, 1>;
  using array3d = std::array<array2d, 1>;
  static_assert(std::is_same<array1d, multi_array_t<int, 1>>{}, "");
  static_assert(std::is_same<array2d, multi_array_t<int, 1, 1>>{}, "");
  static_assert(std::is_same<array3d, multi_array_t<int, 1, 1, 1>>{}, "");
}

TEST(multi_t, basic) {
  using hhxx::multi_t;
  using vec1d = std::vector<int>;
  using vec2d = std::vector<vec1d>;
  using vec3d = std::vector<vec2d>;
  static_assert(std::is_same<vec1d, multi_t<std::vector, int, 1>>{}, "");
  static_assert(std::is_same<vec2d, multi_t<std::vector, int, 2>>{}, "");
  static_assert(std::is_same<vec3d, multi_t<std::vector, int, 3>>{}, "");
}

TEST(make_multi, basic) {
  using hhxx::make_multi;
  using vec1d = std::vector<int>;
  using vec2d = std::vector<vec1d>;
  using vec3d = std::vector<vec2d>;
  auto a = make_multi<std::vector>(2, 1);
  auto b = make_multi<std::vector>(2, 1, 2);
  auto c = make_multi<std::vector>(2, 1, 2, 3);
  static_assert(std::is_same<vec1d, decltype(a)>{}, "");
  static_assert(std::is_same<vec2d, decltype(b)>{}, "");
  static_assert(std::is_same<vec3d, decltype(c)>{}, "");
  EXPECT_EQ(1u, a.size());
  EXPECT_EQ(2, a[0]);
  EXPECT_EQ(1u, b.size());
  EXPECT_EQ(2u, b[0].size());
  EXPECT_EQ(2, b[0][0]);
  EXPECT_EQ(1u, c.size());
  EXPECT_EQ(2u, c[0].size());
  EXPECT_EQ(3u, c[0][0].size());
  EXPECT_EQ(2, c[0][0][0]);
}

TEST(size, basic) {
  using hhxx::size;
  int arr[10] = {};
  std::array<int, 10> std_arr = {};
  std::vector<int> vec(10);
  EXPECT_EQ(10u, size(arr));
  EXPECT_EQ(10u, size(std_arr));
  EXPECT_EQ(10u, size(vec));
}

TEST(make, basic) {
  using hhxx::make;
  std::minstd_rand engine;
  std::uniform_int_distribution<> dis;
  int a = 0, b = 1;
  auto r = dis(engine, make(0, 1));
  EXPECT_TRUE(r == 0 || r == 1);
  r = dis(engine, make(a, b));
  EXPECT_TRUE(r == 0 || r == 1);
  std::shared_ptr<int> p = make(new int(7));
  EXPECT_EQ(7, *p);
}
