// Copyright (c) 2016, Lingxi Li <lilingxi.cs@gmail.com>
// All rights reserved.
// CPP Utility Library (https://github.com/Lingxi-Li/CPP_Utility)

#ifndef CPPU_ALGORITHM_HPP_
#define CPPU_ALGORITHM_HPP_

#include <algorithm>
#include <utility>

namespace cppu_detail_swap {

template <typename T>
void swap_impl(T& x, T& y) {
  // fallbacks to `std::swap()` if ADL failed
  using std::swap;
  swap(x, y);
}

} // namespace cppu_detail_swap

namespace cppu {

namespace detail {

// performs `swap(x, y)` and lookups in both namespace `std` and that of `T`
// (by ADL)
template <typename T>
void swap(T& x, T& y, int) {
  cppu_detail_swap::swap_impl(x, y);
}

// performs `x.swap(y)`; disabled if `x.swap(y)` is ill-formed
template <typename T>
auto swap(T& x, T& y, char) -> decltype(x.swap(y)) {
  return x.swap(y);
}

} // namespace detail

/// Introspective swap. Performs `x.swap(y)` if possible. Otherwise, performs
/// `swap(x, y)` and lookups in both namespace `std` and that of `T` (by ADL).
template <typename T>
void swap(T& x, T& y) {
  // the last argument makes `detail::swap(int&, int&, char)`, if enabled, a
  // better match than `detail::swap(int&, int&, int)`, implementing a
  // preference of `x.swap(y)` over `swap(x, y)`
  detail::swap(x, y, ' ');
}

/// Introspective swap for arrays. For each pair of elements `x[i]` and `y[i]`,
/// performs `x[i].swap(y[i])` if possible. Otherwise, performs
/// `swap(x[i], y[i])` and lookups in both namespace `std` and that of `T`
/// (by ADL).
template <typename T, std::size_t n>
void swap(T (&x)[n], T (&y)[n]) {
  for (std::size_t i = 0; i < n; ++i) {
    swap(x[i], y[i]);
  }
}

} // namespace cppu

#endif // CPPU_ALGORITHM_HPP_
