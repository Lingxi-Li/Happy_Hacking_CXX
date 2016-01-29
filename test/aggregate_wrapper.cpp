// Copyright (c) 2016, Lingxi Li <lilingxi.cs@gmail.com>
// All rights reserved.
// Happy Hacking CXX Library (https://github.com/Lingxi-Li/Happy_Hacking_CXX)

#include <hhxx/aggregate_wrapper.hpp>
#include <hhxx/aggregate_wrapper.hpp>

#include <array>
#include <memory>
#include <type_traits>
#include <utility>

#include <gtest/gtest.h>

namespace aggregate_wrapper_test_ns {

struct foo_t {
  int v0;
  int v1;
  std::unique_ptr<int> ptr;
};

auto make(int x) {
  return std::make_unique<int>(x);
}

} // namespace aggregate_wrapper_test_ns

TEST(aggregate_wrapper, construction) {
  using aggregate_wrapper_test_ns::make;
  // basic
  {
    using foo_t = aggregate_wrapper_test_ns::foo_t;
    using wrapper = hhxx::aggregate_wrapper<foo_t>;
    static_assert(std::is_same<foo_t, wrapper::aggregate_type>{}, "");
    static_assert(! std::is_constructible<wrapper, int, int, int>{}, "");
    wrapper a;
    EXPECT_EQ(0, a.v0);
    EXPECT_EQ(0, a.v1);
    EXPECT_FALSE(a.ptr);
    wrapper b(1);
    EXPECT_EQ(1, b.v0);
    EXPECT_EQ(0, b.v1);
    EXPECT_FALSE(b.ptr);
    wrapper c(1, 2, make(3));
    EXPECT_EQ(1, c.v0);
    EXPECT_EQ(2, c.v1);
    EXPECT_EQ(3, *c.ptr);
    foo_t base { 1, 2, make(3) };
    wrapper d(std::move(base));
    EXPECT_EQ(1, d.v0);
    EXPECT_EQ(2, d.v1);
    EXPECT_EQ(3, *d.ptr);
    wrapper e(std::move(d));
    EXPECT_EQ(1, e.v0);
    EXPECT_EQ(2, e.v1);
    EXPECT_EQ(3, *e.ptr);
  }
  // array
  {
    hhxx::aggregate_wrapper<int[3]> x;
    static_assert(x.size == 3, "");
    EXPECT_EQ(0, x[0]);
    EXPECT_EQ(0, x[1]);
    EXPECT_EQ(0, x[2]);
    using foo_t = std::unique_ptr<int>[3];
    using wrapper = hhxx::aggregate_wrapper<foo_t>;
    using ptr_t = std::unique_ptr<int>;
    static_assert(std::is_same<foo_t, wrapper::aggregate_type>::value, "");
    static_assert(std::is_constructible<wrapper, ptr_t&&, ptr_t&&, ptr_t&&>{}, "");
    static_assert(! std::is_constructible<wrapper, ptr_t&&, ptr_t&&, ptr_t&&, ptr_t&&>{}, "");
    wrapper a;
    EXPECT_FALSE(a[0]);
    EXPECT_FALSE(a[1]);
    EXPECT_FALSE(a[2]);
    wrapper b(make(1));
    EXPECT_EQ(1, *b[0]);
    EXPECT_FALSE(b[1]);
    EXPECT_FALSE(b[2]);
    wrapper c(make(1), make(2), make(3));
    EXPECT_EQ(1, *c[0]);
    EXPECT_EQ(2, *c[1]);
    EXPECT_EQ(3, *c[2]);
    foo_t base { make(1), make(2), make(3) };
    wrapper d(std::move(base));
    EXPECT_EQ(1, *d[0]);
    EXPECT_EQ(2, *d[1]);
    EXPECT_EQ(3, *d[2]);
    wrapper e(std::move(d));
    EXPECT_EQ(1, *e[0]);
    EXPECT_EQ(2, *e[1]);
    EXPECT_EQ(3, *e[2]);
  }
  // std::array
  {
    using foo_t = std::array<std::unique_ptr<int>, 3>;
    using wrapper = hhxx::aggregate_wrapper<foo_t>;
    static_assert(std::is_same<foo_t, wrapper::aggregate_type>::value, "");
    using ptr_t = std::unique_ptr<int>;
    static_assert(std::is_constructible<wrapper, ptr_t&&, ptr_t&&, ptr_t&&>{}, "");
    static_assert(! std::is_constructible<wrapper, ptr_t&&, ptr_t&&, ptr_t&&, ptr_t&&>{}, "");
    wrapper a;
    static_assert(a.size() == 3, "");
    EXPECT_FALSE(a[0]);
    EXPECT_FALSE(a[1]);
    EXPECT_FALSE(a[2]);
    EXPECT_EQ(3u, a.size());
    wrapper b(make(1));
    EXPECT_EQ(1, *b[0]);
    EXPECT_FALSE(b[1]);
    EXPECT_FALSE(b[2]);
    wrapper c(make(1), make(2), make(3));
    EXPECT_EQ(1, *c[0]);
    EXPECT_EQ(2, *c[1]);
    EXPECT_EQ(3, *c[2]);
    foo_t base{ make(1), make(2), make(3) };
    wrapper d(std::move(base));
    EXPECT_EQ(1, *d[0]);
    EXPECT_EQ(2, *d[1]);
    EXPECT_EQ(3, *d[2]);
    wrapper e(std::move(d));
    EXPECT_EQ(1, *e[0]);
    EXPECT_EQ(2, *e[1]);
    EXPECT_EQ(3, *e[2]);
  }
}

TEST(aggregate_wrapper, assignment) {
  using aggregate_wrapper_test_ns::make;
  // basic
  {
    using foo_t = aggregate_wrapper_test_ns::foo_t;
    using wrapper = hhxx::aggregate_wrapper<foo_t>;
    wrapper a;
    wrapper b(1, 2);
    static_assert(std::is_same<wrapper&, decltype(a = std::move(b))>::value, "");
    a = std::move(b);
    EXPECT_EQ(1, a.v0);
    EXPECT_EQ(2, a.v1);
    foo_t base { 3, 4 };
    static_assert(std::is_same<wrapper&, decltype(a = std::move(base))>::value, "");
    a = std::move(base);
    EXPECT_EQ(3, a.v0);
    EXPECT_EQ(4, a.v1);
  }
  // array
  {
    using foo_t = std::unique_ptr<int>[3];
    using wrapper = hhxx::aggregate_wrapper<foo_t>;
    wrapper a;
    wrapper b(make(1), make(2));
    static_assert(std::is_same<wrapper&, decltype(a = std::move(b))>::value, "");
    a = std::move(b);
    EXPECT_EQ(1, *a[0]);
    EXPECT_EQ(2, *a[1]);
    foo_t base{ make(3), make(4) };
    static_assert(std::is_same<wrapper&, decltype(a = std::move(base))>::value, "");
    a = std::move(base);
    EXPECT_EQ(3, *a[0]);
    EXPECT_EQ(4, *a[1]);
  }
  // std::array
  {
    using foo_t = std::array<std::unique_ptr<int>, 3>;
    using wrapper = hhxx::aggregate_wrapper<foo_t>;
    wrapper a;
    wrapper b(make(1), make(2));
    static_assert(std::is_same<wrapper&, decltype(a = std::move(b))>::value, "");
    a = std::move(b);
    EXPECT_EQ(1, *a[0]);
    EXPECT_EQ(2, *a[1]);
    foo_t base{ make(3), make(4) };
    static_assert(std::is_same<wrapper&, decltype(a = std::move(base))>::value, "");
    a = std::move(base);
    EXPECT_EQ(3, *a[0]);
    EXPECT_EQ(4, *a[1]);
  }
}

TEST(aggregate_wrapper, wrap_aggregate) {
  using aggregate_wrapper_test_ns::make;
  // basic
  {
    using foo_t = aggregate_wrapper_test_ns::foo_t;
    using wrapper = hhxx::aggregate_wrapper<foo_t>;
    foo_t base{ 1, 2 };
    static_assert(std::is_same<wrapper, decltype(hhxx::wrap_aggregate(std::move(base)))>::value, "");
    auto a = hhxx::wrap_aggregate(std::move(base));
    EXPECT_EQ(1, a.v0);
    EXPECT_EQ(2, a.v1);
  }
  // array
  {
    using foo_t = std::unique_ptr<int>[3];
    using wrapper = hhxx::aggregate_wrapper<foo_t>;
    foo_t base{ make(1), make(2) };
    static_assert(std::is_same<wrapper, decltype(hhxx::wrap_aggregate(std::move(base)))>::value, "");
    auto a = hhxx::wrap_aggregate(std::move(base));
    EXPECT_EQ(1, *a[0]);
    EXPECT_EQ(2, *a[1]);
  }
  // std::array
  {
    using foo_t = std::array<std::unique_ptr<int>, 3>;
    using wrapper = hhxx::aggregate_wrapper<foo_t>;
    foo_t base{ make(1), make(2) };
    static_assert(std::is_same<wrapper, decltype(hhxx::wrap_aggregate(std::move(base)))>::value, "");
    auto a = hhxx::wrap_aggregate(std::move(base));
    EXPECT_EQ(1, *a[0]);
    EXPECT_EQ(2, *a[1]);
  }
}
