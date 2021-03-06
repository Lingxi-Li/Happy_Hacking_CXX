// Copyright (c) 2016, Lingxi Li <lilingxi.cs@gmail.com>
// All rights reserved.
// Happy Hacking CXX Library (https://github.com/Lingxi-Li/Happy_Hacking_CXX)

#include <hhxx/functional.hpp>

#include <string>
#include <type_traits>

#include <gtest/gtest.h>

namespace pack_args_test_ns {

auto cnt = 0;

struct stru {
  stru() noexcept { ++cnt; }
  stru(const stru&) noexcept { ++cnt; }
  stru(stru&&) noexcept { }
};

void func(stru, stru) {}

template <HHXX_ARG_PACK_T(Ts, Is), HHXX_ARG_PACK_T(Us, Js)>
void func(HHXX_ARG_PACK(Ts, Is) ap1, HHXX_ARG_PACK(Us, Js) ap2) {
  EXPECT_EQ(4, cnt);
  func(HHXX_UNPACK_ARGS(ap1, Is));
  EXPECT_EQ(6, cnt);
  func(HHXX_UNPACK_ARGS(ap2, Js));
  EXPECT_EQ(7, cnt);
}

} // namespace pack_args_test_ns

TEST(pack_args, basic) {
  using namespace pack_args_test_ns;
  stru a, b; // 2
  const stru c, d; // 4
  EXPECT_EQ(4, cnt);
  func(hhxx::pack_args(a, c), hhxx::pack_args(std::move(b), std::move(d)));
  EXPECT_EQ(7, cnt);
}

namespace function_test_ns {

int func(int x) {
  return x;
}

char func(char);

bool func(std::string) {
  return true;
}

bool func(hhxx::function<void()>) {
  return false;
}

struct null_t {
  operator std::nullptr_t () const {
    return nullptr;
  }
};

} // namespace function_test_ns

TEST(function, construction) {
  using func_t = hhxx::function<int(int)>;
  using std_func_t = std::function<int(int)>;
  auto lambda = [](int x) { return x; };
  EXPECT_FALSE(func_t{});
  EXPECT_EQ(0, func_t{function_test_ns::func}(0));
  EXPECT_FALSE(func_t{nullptr});
  func_t f1 = lambda;
  EXPECT_EQ(0, f1(0));
  EXPECT_FALSE(func_t());
  EXPECT_FALSE(func_t(nullptr));
  func_t f2{f1};
  EXPECT_EQ(0, f2(0));
  func_t f3{std::move(f2)};
  std_func_t std_f1 = lambda;
  std_func_t std_f2{std::move(std_f1)};
  EXPECT_EQ(0, f3(0));
  EXPECT_EQ(0, func_t(lambda)(0));
  auto f4 = f1;
  EXPECT_EQ(0, f4(0));
  auto f5 = std::move(f1);
  std_f1 = lambda;
  auto std_f3 = std::move(std_f1);
  func_t f6 = std_f3;
  EXPECT_EQ(0, f6(0));
}

TEST(function, assignment) {
  using func_t = hhxx::function<int(int)>;
  using std_func_t = std::function<int(int)>;
  auto lambda = [](int x) { return x; };
  // copy assignment
  func_t f1 = lambda;
  func_t f2;
  f2 = f1;
  EXPECT_EQ(0, f1(0));
  EXPECT_EQ(0, f2(0));
  // move assignment
  std_func_t std_f1 = lambda;
  std_func_t std_f2;
  std_f2 = std::move(std_f1);
  static_assert(std::is_same<func_t&, decltype(f2 = nullptr)>::value,
                "`function::operator =()` returned wrong type");
  f2 = nullptr;
  EXPECT_FALSE(f2);
  f2 = std::move(f1);
  EXPECT_EQ(0, f2(0));
  f1 = nullptr;
  static_assert(std::is_same<func_t&, decltype(f2 = lambda)>::value,
                "`function::operator =()` returned wrong type");
  f1 = lambda;
  EXPECT_EQ(0, f1(0));
  f1 = nullptr;
  static_assert(std::is_same<func_t&, decltype(f2 = std::ref(lambda))>::value,
                "`function::operator =()` returned wrong type");
  f1 = std::ref(lambda);
  EXPECT_EQ(0, f1(0));
  f1 = nullptr;
  f1 = function_test_ns::func;
  EXPECT_EQ(0, f1(0));
  f1 = nullptr;
  f1 = std_f2;
  EXPECT_EQ(0, f1(0));
}

TEST(function, overload_resolution) {
  using func_t = hhxx::function<int(int)>;
  auto lambda = [](int x) { return x; };
  // despite implicit conversion from `const char*` to `std::string`,
  // should resolve to `func(std::string)` instead of
  // `func(hhxx::function<void()>)` and compile
  EXPECT_TRUE(function_test_ns::func("test"));
  func_t f = lambda;
  // despite implicit conversion from `null_t` to `std::nullptr_t`,
  // should resolve to `operator =(std::nullptr_t)` instead of `operator =(F&&)`
  // and compile
  f = function_test_ns::null_t{};
  EXPECT_FALSE(f);
}

TEST(function, other) {
  using func_t = hhxx::function<int(int)>;
  auto lambda = [](int x) { return x; };
  // swap
  func_t f1;
  func_t f2 = lambda;
  EXPECT_FALSE(f1);
  EXPECT_EQ(0, f2(0));
  f1.swap(f2);
  EXPECT_FALSE(f2);
  EXPECT_EQ(0, f1(0));
  swap(f1, f2);
  EXPECT_FALSE(f1);
  EXPECT_EQ(0, f2(0));
  // ==, !=
  EXPECT_EQ(f1, nullptr);
  EXPECT_NE(f2, nullptr);
}
