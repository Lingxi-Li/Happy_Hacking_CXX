// Copyright (c) 2016, Lingxi Li <lilingxi.cs@gmail.com>
// All rights reserved.
// Happy Hacking CXX Library (https://github.com/Lingxi-Li/Happy_Hacking_CXX)

#include <hhxx/string.hpp>
#include <hhxx/string.hpp>

#include <cstddef>

#include <type_traits>
#include <utility>

#include <gtest/gtest.h>

namespace to_xstring_test_ns {

struct foo_t {};

std::string to_string(foo_t) {
  return "foo_t";
}

std::wstring to_wstring(foo_t) {
  return L"foo_t";
}

} // namespace to_xstring_test_ns

template <typename CharT>
struct to_xstring_test : testing::Test {
  using chr_t = CharT;
  using str_t = std::basic_string<chr_t>;

  template <std::size_t n>
  static str_t str(const char (&x)[n]) {
    // fine for ASCII characters
    return {x + 0, x + n - 1};
  }

  template <typename T>
  static auto to_xstring(const T& x) {
    return hhxx::to_xstring<chr_t>(x);
  }

  static void basic() {
    static_assert(std::is_same<str_t, decltype(to_xstring(0))>::value,
                  "`to_xstring()` returned wrong type");
    // lookups in `std`
    EXPECT_EQ(str("123"), to_xstring(123));
    // ADL lookup
    EXPECT_EQ(str("foo_t"), to_xstring(to_xstring_test_ns::foo_t{}));
  }
};

TYPED_TEST_CASE_P(to_xstring_test);

TYPED_TEST_P(to_xstring_test, basic) { TestFixture::basic(); }

REGISTER_TYPED_TEST_CASE_P(to_xstring_test, basic);

using to_xstring_test_types = testing::Types<char, wchar_t>;

INSTANTIATE_TYPED_TEST_CASE_P(basic, to_xstring_test, to_xstring_test_types);

////////////////////////////////////////
