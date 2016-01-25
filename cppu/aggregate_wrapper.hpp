// Copyright (c) 2016, Lingxi Li <lilingxi.cs@gmail.com>
// All rights reserved.
// CPP Utility Library (https://github.com/Lingxi-Li/CPP_Utility)

#ifndef CPPU_AGGREGATE_WRAPPER_HPP_
#define CPPU_AGGREGATE_WRAPPER_HPP_

#include <cstddef>

#include <algorithm>
#include <type_traits>
#include <utility>

namespace cppu {

/// Wraps aggregates and provides a variadic forwarding constructor.
/// Enables in-place construction. Value initializes the aggregate
/// when default constructed.
template <typename T>
class aggregate_wrapper : public T {
private:
  using base = T;

public:
  using aggregate_type = T;

  // no `explicit`; aggregate initialization can be done implicitly;
  // be consistent with that
  template <typename... Ts>
  aggregate_wrapper(Ts&&... xs)
      : base{std::forward<Ts>(xs)...} {
    // nop
  }
};

template <typename T, std::size_t n>
class aggregate_wrapper<T[n]> {
private:
  using array = T[n];

public:
  using aggregate_type = T[n];

  template <typename... Ts>
  aggregate_wrapper(Ts&&... xs)
      : arr_{std::forward<Ts>(xs)...} {
    // nop
  }
  aggregate_wrapper(const array& arr) {
    std::copy(arr, arr + n, arr_);
  }
  aggregate_wrapper(array&& arr) {
    std::move(arr, arr + n, arr_);
  }

  operator T* () {
    return arr_;
  }
  operator const T* () const {
    return arr_;
  }

private:
  array arr_;
};

// you won't want to use `std::decay_t`;
// consider the case when `T` is an array type
template <typename T>
aggregate_wrapper<std::remove_const_t<std::remove_reference_t<T>>>
wrap_aggregate(T&& x) {
  return std::forward<T>(x);
}

} // namespace cppu

#endif // CPPU_AGGREGATE_WRAPPER_HPP_
