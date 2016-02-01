// Copyright (c) 2016, Lingxi Li <lilingxi.cs@gmail.com>
// All rights reserved.
// Happy Hacking CXX Library (https://github.com/Lingxi-Li/Happy_Hacking_CXX)

#include <hhxx/bit.hpp>

#include <climits>

#include <gtest/gtest.h>

TEST(num_bits, basic) {
  using hhxx::num_bits;
  static_assert(num_bits<char>() == 8, "");
  static_assert(num_bits('c') == 8, "");
}

TEST(msb_idx, basic) {
  using hhxx::msb_idx;
  static_assert(msb_idx<char>() == 7, "");
  static_assert(msb_idx('c') == 7, "");
}

TEST(bit_flag, basic) {
  using hhxx::bit_flag;
  using hhxx::num_bits;
  static_assert(bit_flag<int>(0) == 1, "");
  static_assert(bit_flag<int>(3) == 8, "");
  static_assert(bit_flag<int>(num_bits<int>() - 1) == INT_MIN, "");
  EXPECT_EQ(1, bit_flag<int>(0));
  EXPECT_EQ(8, bit_flag<int>(3));
  EXPECT_EQ(INT_MIN, bit_flag<int>(num_bits<int>() - 1));
}

TEST(msb_flag, basic) {
  using hhxx::msb_flag;
  static_assert(msb_flag<int>() == INT_MIN, "");
}

TEST(test_bit, basic) {
  using hhxx::test_bit;
  using hhxx::num_bits;
  static_assert(test_bit(-1, num_bits(-1) - 1), "");
  static_assert(! test_bit(0, num_bits(0) - 1), "");
  static_assert(test_bit(2, 1), "");
  static_assert(! test_bit(1, 1), "");
  static_assert(test_bit(1, 0), "");
  static_assert(! test_bit(0, 0), "");
  EXPECT_TRUE(test_bit(-1, num_bits(-1) - 1));
  EXPECT_FALSE(test_bit(0, num_bits(0) - 1));
  EXPECT_TRUE(test_bit(2, 1));
  EXPECT_FALSE(test_bit(1, 1));
  EXPECT_TRUE(test_bit(1, 0));
  EXPECT_FALSE(test_bit(0, 0));
  constexpr std::size_t sz = -1;
  static_assert(test_bit(sz, num_bits(sz) - 1), "");
  EXPECT_TRUE(test_bit(sz, num_bits(sz) - 1));
}

TEST(test_msb, basic) {
  using hhxx::test_msb;
  static_assert(! test_msb(0), "");
  static_assert(test_msb(INT_MIN), "");
  EXPECT_FALSE(test_msb(0));
  EXPECT_TRUE(test_msb(INT_MIN));
}

TEST(set_bit, basic) {
  using hhxx::set_bit;
  using hhxx::num_bits;
  static_assert(set_bit(0, num_bits<int>() - 1) == INT_MIN, "");
  static_assert(set_bit(0, 0) == 1, "");
  static_assert(set_bit(0, 3) == 8, "");
  EXPECT_EQ(INT_MIN, set_bit(0, num_bits<int>() - 1));
  EXPECT_EQ(1, set_bit(0, 0));
  EXPECT_EQ(8, set_bit(0, 3));
}

TEST(set_msb, basic) {
  using hhxx::set_msb;
  static_assert(set_msb(0) == INT_MIN, "");
  EXPECT_EQ(INT_MIN, set_msb(0));
}

TEST(clear_bit, basic) {
  using hhxx::clear_bit;
  using hhxx::num_bits;
  static_assert(clear_bit(1, 0) == 0, "");
  static_assert(clear_bit(8, 3) == 0, "");
  static_assert(clear_bit(INT_MIN, num_bits<int>() - 1) == 0, "");
  EXPECT_EQ(0, clear_bit(1, 0));
  EXPECT_EQ(0, clear_bit(8, 3));
  EXPECT_EQ(0, clear_bit(INT_MIN, num_bits<int>() - 1));
}

TEST(clear_msb, basic) {
  using hhxx::clear_msb;
  static_assert(clear_msb(INT_MIN) == 0, "");
  EXPECT_EQ(0, clear_msb(INT_MIN));
}

TEST(flip_bit, basic) {
  using hhxx::flip_bit;
  using hhxx::num_bits;
  static_assert(flip_bit(0, 0) == 1, "");
  static_assert(flip_bit(1, 0) == 0, "");
  static_assert(flip_bit(0, 3) == 8, "");
  static_assert(flip_bit(8, 3) == 0, "");
  static_assert(flip_bit(0, num_bits<int>() - 1) == INT_MIN, "");
  static_assert(flip_bit(INT_MIN, num_bits<int>() - 1) == 0, "");
  EXPECT_EQ(1, flip_bit(0, 0));
  EXPECT_EQ(0, flip_bit(1, 0));
  EXPECT_EQ(8, flip_bit(0, 3));
  EXPECT_EQ(0, flip_bit(8, 3));
  EXPECT_EQ(INT_MIN, flip_bit(0, num_bits<int>() - 1));
  EXPECT_EQ(0, flip_bit(INT_MIN, num_bits<int>() - 1));
}

TEST(flip_msb, basic) {
  using hhxx::flip_msb;
  static_assert(flip_msb(INT_MIN) == 0, "");
  static_assert(flip_msb(0) == INT_MIN, "");
  EXPECT_EQ(0, flip_msb(INT_MIN));
  EXPECT_EQ(INT_MIN, flip_msb(0));
}

TEST(num_bits_set, basic) {
  using hhxx::num_bits_set;
  using hhxx::num_bits;
  static_assert(num_bits_set(0) == 0, "");
  static_assert(num_bits_set(1) == 1, "");
  static_assert(num_bits_set(8) == 1, "");
  static_assert(num_bits_set(20) == 2, "");
  static_assert(num_bits_set(-1) == num_bits(-1), "");
  static_assert(num_bits_set(INT_MIN) == 1, "");
  EXPECT_EQ(0u, num_bits_set(0));
  EXPECT_EQ(1u, num_bits_set(1));
  EXPECT_EQ(1u, num_bits_set(8));
  EXPECT_EQ(2u, num_bits_set(20));
  EXPECT_EQ(num_bits(-1), num_bits_set(-1));
  EXPECT_EQ(1u, num_bits_set(INT_MIN));
}
