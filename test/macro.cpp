// Copyright (c) 2016, Lingxi Li <lilingxi.cs@gmail.com>
// All rights reserved.
// Happy Hacking CXX Library (https://github.com/Lingxi-Li/Happy_Hacking_CXX)

#include <hhxx/macro.hpp>

#include <cstddef>
#include <string>

#include <gtest/gtest.h>

namespace macro_test_ns {

template <std::size_t n>
std::string str_literal(const char (&str)[n]) {
  return str;
}

} // namespace macro_test_ns

#define TEST_MACRO_ABC abc
#define TEST_MACRO_123 123
#define TEST_MACRO____ ___

TEST(STR_and_JOIN, basic) {
  using macro_test_ns::str_literal;
  EXPECT_EQ("abc", str_literal(HHXX_STR(TEST_MACRO_ABC)));
  EXPECT_EQ("abc123", str_literal(HHXX_STR(
    HHXX_JOIN2(TEST_MACRO_ABC, TEST_MACRO_123)
  )));
  EXPECT_EQ("abc___123", str_literal(HHXX_STR(
    HHXX_JOIN3(TEST_MACRO_ABC, TEST_MACRO____, TEST_MACRO_123)
  )));
}

TEST(UNIQUE_NAME, basic) {
  using macro_test_ns::str_literal;
  EXPECT_EQ("obj_at_line_" HHXX_STR(__LINE__), str_literal(HHXX_STR(HHXX_UNIQUE_NAME(obj))));
}
