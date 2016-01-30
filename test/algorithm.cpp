// Copyright (c) 2016, Lingxi Li <lilingxi.cs@gmail.com>
// All rights reserved.
// Happy Hacking CXX Library (https://github.com/Lingxi-Li/Happy_Hacking_CXX)

#include <hhxx/algorithm.hpp>
#include <hhxx/algorithm.hpp>

#include <array>
#include <iterator>
#include <numeric>
#include <vector>

#include <gtest/gtest.h>

namespace swap_test_ns {

struct no_swap_t {
  int v;
};

struct member_swap_t {
  void swap(member_swap_t& other) {
    std::swap(v, other.v);
    // does something different for distinguishing purpose
    ++v;
    ++other.v;
  }
  int v;
};

struct free_adl_swap_t {
  int v;
};

void swap(free_adl_swap_t& x, free_adl_swap_t& y) {
  std::swap(x.v, y.v);
  // does something different for distinguishing purpose
  ++x.v;
  ++y.v;
}

} // namespace swap_test_ns

namespace hhxx {

struct swap_test_no_swap_t {
  int v;
};

struct swap_test_member_swap_t {
  void swap(swap_test_member_swap_t& other) {
    std::swap(v, other.v);
    // does something different for distinguishing purpose
    ++v;
    ++other.v;
  }
  int v;
};

struct swap_test_free_adl_swap_t {
  int v;
};

void swap(swap_test_free_adl_swap_t& x, swap_test_free_adl_swap_t& y) {
  std::swap(x.v, y.v);
  // does something different for distinguishing purpose
  ++x.v;
  ++y.v;
}

} // namespace hhxx

TEST(swap, member_swap) {
  {
    using obj_t = swap_test_ns::member_swap_t;
    obj_t x{0};
    obj_t y{1};
    hhxx::iswap(x, y);
    EXPECT_EQ(2, x.v);
    EXPECT_EQ(1, y.v);
  }
  {
    using obj_t = hhxx::swap_test_member_swap_t;
    obj_t x{0};
    obj_t y{1};
    hhxx::iswap(x, y);
    EXPECT_EQ(2, x.v);
    EXPECT_EQ(1, y.v);
  }
}

TEST(swap, free_adl_swap) {
  {
    using obj_t = swap_test_ns::free_adl_swap_t;
    obj_t x{0};
    obj_t y{1};
    hhxx::iswap(x, y);
    EXPECT_EQ(2, x.v);
    EXPECT_EQ(1, y.v);
  }
  {
    using obj_t = hhxx::swap_test_free_adl_swap_t;
    obj_t x{0};
    obj_t y{1};
    hhxx::iswap(x, y);
    EXPECT_EQ(2, x.v);
    EXPECT_EQ(1, y.v);
  }
}

TEST(swap, free_std_swap) {
  {
    // ADL doesn't apply to primitive types
    int x = 0;
    int y = 1;
    hhxx::iswap(x, y);
    EXPECT_EQ(1, x);
    EXPECT_EQ(0, y);
  }
  {
    using obj_t = swap_test_ns::no_swap_t;
    obj_t x = {0};
    obj_t y = {1};
    hhxx::iswap(x, y);
    EXPECT_EQ(1, x.v);
    EXPECT_EQ(0, y.v);
  }
  {
    using obj_t = hhxx::swap_test_no_swap_t;
    obj_t x = {0};
    obj_t y = {1};
    hhxx::iswap(x, y);
    EXPECT_EQ(1, x.v);
    EXPECT_EQ(0, y.v);
  }
}

TEST(swap, member_swap_array) {
  using obj_t = swap_test_ns::member_swap_t;
  obj_t x[] = { {0}, {0} };
  obj_t y[] = { {1}, {1} };
  hhxx::iswap(x, y);
  for (int i = 0; i < 2; ++i) {
    EXPECT_EQ(2, x[i].v);
    EXPECT_EQ(1, y[i].v);
  }
}

TEST(swap, free_adl_swap_array) {
  using obj_t = swap_test_ns::free_adl_swap_t;
  obj_t x[] = { {0}, {0} };
  obj_t y[] = { {1}, {1} };
  hhxx::iswap(x, y);
  for (int i = 0; i < 2; ++i) {
    EXPECT_EQ(2, x[i].v);
    EXPECT_EQ(1, y[i].v);
  }
}

TEST(swap, free_std_swap_array) {
  // ADL doesn't apply to primitive types
  int x[] = { 0, 0 };
  int y[] = { 1, 1 };
  hhxx::iswap(x, y);
  for (int i = 0; i < 2; ++i) {
    EXPECT_EQ(1, x[i]);
    EXPECT_EQ(0, y[i]);
  }
}

TEST(swap, member_swap_array_recursive) {
  using obj_t = swap_test_ns::member_swap_t;
  obj_t x[2][2] = { { {0}, {0} },
                    { {0}, {0} } };
  obj_t y[2][2] = { { {1}, {1} },
                    { {1}, {1} } };
  hhxx::iswap(x, y);
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      EXPECT_EQ(2, x[i][j].v);
      EXPECT_EQ(1, y[i][j].v);
    }
  }
}

TEST(swap, free_adl_swap_array_recursive) {
  using obj_t = swap_test_ns::free_adl_swap_t;
  obj_t x[2][2] = { { {0}, {0} },
                    { {0}, {0} } };
  obj_t y[2][2] = { { {1}, {1} },
                    { {1}, {1} } };
  hhxx::iswap(x, y);
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      EXPECT_EQ(2, x[i][j].v);
      EXPECT_EQ(1, y[i][j].v);
    }
  }
}

TEST(swap, free_std_swap_array_recursive) {
  // ADL doesn't apply to primitive types
  int x[2][2] = { { 0, 0 },
                  { 0, 0 } };
  int y[2][2] = { { 1, 1 },
                  { 1, 1 } };
  hhxx::iswap(x, y);
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      EXPECT_EQ(1, x[i][j]);
      EXPECT_EQ(0, y[i][j]);
    }
  }
}

TEST(swap, member_swap_std_array) {
  using obj_t = swap_test_ns::member_swap_t;
  using array_t = std::array<obj_t, 2>;
  array_t x = {{ {0}, {0} }};
  array_t y = {{ {1}, {1} }};
  hhxx::iswap(x, y);
  for (int i = 0; i < 2; ++i) {
    EXPECT_EQ(2, x[i].v);
    EXPECT_EQ(1, y[i].v);
  }
}

TEST(swap, free_adl_swap_std_array) {
  using obj_t = swap_test_ns::free_adl_swap_t;
  using array_t = std::array<obj_t, 2>;
  array_t x = {{ {0}, {0} }};
  array_t y = {{ {1}, {1} }};
  hhxx::iswap(x, y);
  for (int i = 0; i < 2; ++i) {
    EXPECT_EQ(2, x[i].v);
    EXPECT_EQ(1, y[i].v);
  }
}

TEST(swap, free_std_swap_std_array) {
  // ADL doesn't apply to primitive types
  using array_t = std::array<int, 2>;
  array_t x = {{ 0, 0 }};
  array_t y = {{ 1, 1 }};
  hhxx::iswap(x, y);
  for (int i = 0; i < 2; ++i) {
    EXPECT_EQ(1, x[i]);
    EXPECT_EQ(0, y[i]);
  }
}

TEST(swap, member_swap_std_array_recursive) {
  using obj_t = swap_test_ns::member_swap_t;
  using array_t = std::array<std::array<obj_t, 2>, 2>;
  array_t x = {{ {{ {0}, {0} }},
                 {{ {0}, {0} }} }};
  array_t y = {{ {{ {1}, {1} }},
                 {{ {1}, {1} }} }};
  hhxx::iswap(x, y);
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      EXPECT_EQ(2, x[i][j].v);
      EXPECT_EQ(1, y[i][j].v);
    }
  }
}

TEST(swap, free_adl_swap_std_array_recursive) {
  using obj_t = swap_test_ns::free_adl_swap_t;
  using array_t = std::array<std::array<obj_t, 2>, 2>;
  array_t x = {{ {{ {0}, {0} }},
                 {{ {0}, {0} }} }};
  array_t y = {{ {{ {1}, {1} }},
                 {{ {1}, {1} }} }};
  hhxx::iswap(x, y);
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      EXPECT_EQ(2, x[i][j].v);
      EXPECT_EQ(1, y[i][j].v);
    }
  }
}

TEST(swap, free_std_swap_std_array_recursive) {
  // ADL doesn't apply to primitive types
  using array_t = std::array<std::array<int, 2>, 2>;
  array_t x = {{ {{ 0, 0 }},
                 {{ 0, 0 }} }};
  array_t y = {{ {{ 1, 1 }},
                 {{ 1, 1 }} }};
  hhxx::iswap(x, y);
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      EXPECT_EQ(1, x[i][j]);
      EXPECT_EQ(0, y[i][j]);
    }
  }
}

////////////////////////////////////////

TEST(min, basic) {
  EXPECT_EQ(0, hhxx::min(0));
  EXPECT_EQ(-1, hhxx::min(-1, 0, 1));
  EXPECT_EQ(0, hhxx::min(0, 1));
}

TEST(min, extended) {
  using vec_t = std::vector<int>;
  vec_t a{0};
  vec_t b{1};
  vec_t c{2};
  EXPECT_EQ(&a, &hhxx::min(a, b, c));
  EXPECT_EQ(&a, &hhxx::min(a, b));
}

TEST(max, basic) {
  EXPECT_EQ(0, hhxx::max(0));
  EXPECT_EQ(1, hhxx::max(-1, 0, 1));
  EXPECT_EQ(1, hhxx::max(0, 1));
}

TEST(max, extended) {
  using vec_t = std::vector<int>;
  vec_t a{0};
  vec_t b{1};
  vec_t c{2};
  EXPECT_EQ(&c, &hhxx::max(a, b, c));
  EXPECT_EQ(&b, &hhxx::max(a, b));
}

////////////////////////////////////////

TEST(for_each, trivial) {
  using hhxx::for_each;
  auto f = [](int& x) { x = 2; };
  int v = 0;
  for_each(v, f);
  EXPECT_EQ(v, 2);
  int arr[3] = {};
  for_each(arr, f);
  for (auto item : arr) {
    EXPECT_EQ(2, item);
  }
  std::array<int, 3> std_arr{{}};
  for_each(std_arr, f);
  for (auto item : std_arr) {
    EXPECT_EQ(2, item);
  }
  std::vector<int> vec(3);
  for_each(vec, f);
  for (auto item : vec) {
    EXPECT_EQ(2, item);
  }
}

TEST(for_each, multi) {
  using hhxx::for_each;
  int a[3][3] = {};
  auto f = [](int& x) { x = 2; };
  for_each(a, f);
  for (auto& row : a) {
    for (auto& val : row) {
      EXPECT_EQ(2, val);
    }
  }
  std::array<std::array<int, 3>, 3> arr{};
  for_each(arr, f);
  for (auto& row : arr) {
    for (auto& val : row) {
      EXPECT_EQ(2, val);
    }
  }
  std::vector<std::vector<int>> vec(3, std::vector<int>(3));
  for_each(vec, f);
  for (auto& row : vec) {
    for (auto& val : row) {
      EXPECT_EQ(2, val);
    }
  }
}

TEST(tick_count, basic) {
  using hhxx::tick_count;
  static_cast<void>(tick_count());
  static_cast<void>(tick_count<std::chrono::system_clock>());
  static_cast<void>(tick_count<std::chrono::steady_clock>());
  static_cast<void>(tick_count<std::chrono::high_resolution_clock>());
}

TEST(sample, basic) {
  using hhxx::sample;
  std::vector<unsigned> vec;
  sample(3, 0, std::back_inserter(vec));
  EXPECT_EQ(0u, vec.size());
  sample(3, 1, std::back_inserter(vec));
  EXPECT_EQ(1u, vec.size());
  EXPECT_TRUE(0 <= vec[0] && vec[0] < 3);
  vec.clear();
  sample(3, 2, std::back_inserter(vec));
  EXPECT_EQ(2u, vec.size());
  EXPECT_TRUE(0 <= vec[0] && vec[0] < 3);
  EXPECT_TRUE(0 <= vec[1] && vec[1] < 3);
  EXPECT_NE(vec[0], vec[1]);
  vec.clear();
  sample(3, 3, std::back_inserter(vec));
  std::sort(vec.begin(), vec.end());
  std::vector<unsigned> target = {0, 1, 2};
  EXPECT_EQ(target, vec);
}
