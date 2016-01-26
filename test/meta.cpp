// Copyright (c) 2016, Lingxi Li <lilingxi.cs@gmail.com>
// All rights reserved.
// CPP Utility Library (https://github.com/Lingxi-Li/CPP_Utility)

#include <cppu/meta.hpp>
#include <cppu/meta.hpp>

#include <gtest/gtest.h>

TEST(enable_if_well_formed, basic) {
  using cppu::enable_if_well_formed_t;
  static_assert(std::is_same<void, enable_if_well_formed_t<decltype(0)>>::value, "");
  static_assert(std::is_same<int, enable_if_well_formed_t<decltype(0), int>>::value, "");
}

TEST(multi_array, basic) {
  using cppu::multi_array_t;
  using array1d = std::array<int, 1>;
  using array2d = std::array<array1d, 1>;
  using array3d = std::array<array2d, 1>;
  static_assert(std::is_same<array1d, multi_array_t<int, 1>>{}, "");
  static_assert(std::is_same<array2d, multi_array_t<int, 1, 1>>{}, "");
  static_assert(std::is_same<array3d, multi_array_t<int, 1, 1, 1>>{}, "");
}
