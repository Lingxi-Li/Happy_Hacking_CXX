// Copyright (c) 2016, Lingxi Li <lilingxi.cs@gmail.com>
// All rights reserved.
// CPP Utility Library (https://github.com/Lingxi-Li/CPP_Utility)

#include <cppu/algorithm.hpp>
#include <cppu/algorithm.hpp>

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

namespace cppu {

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

} // namespace cppu

TEST(swap, member_swap) {
  {
    using obj_t = swap_test_ns::member_swap_t;
    obj_t x{0};
    obj_t y{1};
    cppu::iswap(x, y);
    EXPECT_EQ(2, x.v);
    EXPECT_EQ(1, y.v);
  }
  {
    using obj_t = cppu::swap_test_member_swap_t;
    obj_t x{0};
    obj_t y{1};
    cppu::iswap(x, y);
    EXPECT_EQ(2, x.v);
    EXPECT_EQ(1, y.v);
  }
}

TEST(swap, free_adl_swap) {
  {
    using obj_t = swap_test_ns::free_adl_swap_t;
    obj_t x{0};
    obj_t y{1};
    cppu::iswap(x, y);
    EXPECT_EQ(2, x.v);
    EXPECT_EQ(1, y.v);
  }
  {
    using obj_t = cppu::swap_test_free_adl_swap_t;
    obj_t x{0};
    obj_t y{1};
    cppu::iswap(x, y);
    EXPECT_EQ(2, x.v);
    EXPECT_EQ(1, y.v);
  }
}

TEST(swap, free_std_swap) {
  {
    // ADL doesn't apply to primitive types
    int x = 0;
    int y = 1;
    cppu::iswap(x, y);
    EXPECT_EQ(1, x);
    EXPECT_EQ(0, y);
  }
  {
    using obj_t = swap_test_ns::no_swap_t;
    obj_t x = {0};
    obj_t y = {1};
    cppu::iswap(x, y);
    EXPECT_EQ(1, x.v);
    EXPECT_EQ(0, y.v);
  }
  {
    using obj_t = cppu::swap_test_no_swap_t;
    obj_t x = {0};
    obj_t y = {1};
    cppu::iswap(x, y);
    EXPECT_EQ(1, x.v);
    EXPECT_EQ(0, y.v);
  }
}

TEST(swap, member_swap_array) {
  using obj_t = swap_test_ns::member_swap_t;
  obj_t x[] = { {0}, {0} };
  obj_t y[] = { {1}, {1} };
  cppu::iswap(x, y);
  for (int i = 0; i < 2; ++i) {
    EXPECT_EQ(2, x[i].v);
    EXPECT_EQ(1, y[i].v);
  }
}

TEST(swap, free_adl_swap_array) {
  using obj_t = swap_test_ns::free_adl_swap_t;
  obj_t x[] = { {0}, {0} };
  obj_t y[] = { {1}, {1} };
  cppu::iswap(x, y);
  for (int i = 0; i < 2; ++i) {
    EXPECT_EQ(2, x[i].v);
    EXPECT_EQ(1, y[i].v);
  }
}

TEST(swap, free_std_swap_array) {
  // ADL doesn't apply to primitive types
  int x[] = { 0, 0 };
  int y[] = { 1, 1 };
  cppu::iswap(x, y);
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
  cppu::iswap(x, y);
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
  cppu::iswap(x, y);
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
  cppu::iswap(x, y);
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
  cppu::iswap(x, y);
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
  cppu::iswap(x, y);
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
  cppu::iswap(x, y);
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
  cppu::iswap(x, y);
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
  cppu::iswap(x, y);
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
  cppu::iswap(x, y);
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      EXPECT_EQ(1, x[i][j]);
      EXPECT_EQ(0, y[i][j]);
    }
  }
}

////////////////////////////////////////

TEST(min, basic) {
  EXPECT_EQ(0, cppu::min(0));
  EXPECT_EQ(-1, cppu::min(-1, 0, 1));
  EXPECT_EQ(0, cppu::min(0, 1));
}

TEST(min, extended) {
  using vec_t = std::vector<int>;
  vec_t a{0};
  vec_t b{1};
  vec_t c{2};
  EXPECT_EQ(&a, &cppu::min(a, b, c));
  EXPECT_EQ(&a, &cppu::min(a, b));
}

TEST(max, basic) {
  EXPECT_EQ(0, cppu::max(0));
  EXPECT_EQ(1, cppu::max(-1, 0, 1));
  EXPECT_EQ(1, cppu::max(0, 1));
}

TEST(max, extended) {
  using vec_t = std::vector<int>;
  vec_t a{0};
  vec_t b{1};
  vec_t c{2};
  EXPECT_EQ(&c, &cppu::max(a, b, c));
  EXPECT_EQ(&b, &cppu::max(a, b));
}
