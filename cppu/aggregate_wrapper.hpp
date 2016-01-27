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

/// Since aggregates do not support initialization using the `()` syntax, they
/// cannot be in-place constructed with the `emplace*()` methods. Wrap them to
/// support the `()` initialization syntax and enable in-place construction.
/// While a default initialized aggregate may have an indeterminate value, this
/// wrapper class ensures that the wrapped aggregate always has a determinate value.

/// Primary template for wrapping non-array aggregate type `T`.
template <typename T>
class aggregate_wrapper : public T {
private:
  using base = T;

public:
  using aggregate_type = T;

  /// Forwarding constructor that enables the `()` initialization syntax and
  /// in-place construction. The wrapped aggregate is list-initialized using
  /// the forwarded arguments. Enabled only when the aggregate is initializable
  /// from the arguments. When no argument is provided, value-initialization is
  /// performed.
  // no `explicit`; aggregate initialization can be done implicitly;
  // be consistent with that; as to the SFINAE disabler, see
  // http://stackoverflow.com/a/35012938/1348273
  template <typename... Ts, typename = decltype(base{std::declval<Ts>()...})>
  aggregate_wrapper(Ts&&... xs)
      : base{std::forward<Ts>(xs)...} {
    // nop
  }
};

/// Specialized template for wrapping array type `T[n]`.
template <typename T, std::size_t n>
class aggregate_wrapper<T[n]> {
private:
  using array = T[n];

public:
  using aggregate_type = T[n];

  template <typename... Ts, typename = decltype(array{std::declval<Ts>()...})>
  aggregate_wrapper(Ts&&... xs)
      : arr_{std::forward<Ts>(xs)...} {
    // nop
  }

  /// You can't initialize an array directly from another. The constructor
  /// default initializes the wrapped array, and then copies/moves each element
  /// from `arr` to it.

  aggregate_wrapper(const array& arr) {
    std::copy(arr, arr + n, arr_);
  }
  aggregate_wrapper(array&& arr) {
    std::move(arr, arr + n, arr_);
  }

  /// Provides transparent access to the wrapped array.

  operator T* () {
    return arr_;
  }
  operator const T* () const {
    return arr_;
  }

  /// Returns the size of the wrapped array.
  std::size_t size() const {
    return n;
  }

private:
  array arr_;
};

/// Makes an `aggregate_wrapper` that wraps `x`.
// you won't want to use `std::decay_t`;
// consider the case when `T` is an array type
template <typename T>
aggregate_wrapper<std::remove_const_t<std::remove_reference_t<T>>>
wrap_aggregate(T&& x) {
  return std::forward<T>(x);
}

} // namespace cppu

#endif // CPPU_AGGREGATE_WRAPPER_HPP_
