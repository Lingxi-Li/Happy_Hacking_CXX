// Copyright (c) 2016, Lingxi Li <lilingxi.cs@gmail.com>
// All rights reserved.
// CPP Utility Library (https://github.com/Lingxi-Li/CPP_Utility)

#ifndef CPPU_ALGORITHM_HPP_
#define CPPU_ALGORITHM_HPP_

#include <algorithm>
#include <array>
#include <functional>
#include <utility>

#include "meta.hpp"

namespace cppu {

namespace detail {

// performs `swap(x, y)`, looking up in both namespace `std` and that of `T`
// (by ADL)
template <typename T>
void iswap(T& x, T& y, int) {
  // fallbacks to `std::swap()` if ADL failed
  using std::swap;
  swap(x, y);
}

// performs `x.swap(y)`; disabled if `x.swap(y)` is ill-formed
template <typename T>
auto iswap(T& x, T& y, char) -> decltype(x.swap(y)) {
  return x.swap(y);
}

template <typename T, typename F>
auto for_each(T& obj, F& f, char)
-> decltype(static_cast<void>(f(obj))) {
  f(obj);
}

template <typename T, typename F>
void for_each(T& obj, F& f, int) {
  for (auto& sub : obj) {
    for_each(sub, f, ' ');
  }
}

} // namespace detail

/// Introspective swap. Basically swaps `x` and `y`. It performs `x.swap(y)` if
/// possible. Otherwise, performs `swap(x, y)`, looking up `swap()` in both
/// namespace `std` and that of `T` (by ADL).
template <typename T>
void iswap(T& x, T& y) {
  // the last argument makes `detail::iswap(int&, int&, char)`, if enabled,
  // a better match than `detail::iswap(int&, int&, int)`, implementing a
  // preference of `x.swap(y)` over `swap(x, y)`; uses `static_cast<void>()`
  // to ignore possible (though very unlikely) return value from
  // `detail::iswap(int&, int&, char)`
  static_cast<void>(detail::iswap(x, y, ' '));
}

/// Introspective swap for arrays. For each pair of elements `x[i]` and `y[i]`,
/// performs `x[i].swap(y[i])` if possible. Otherwise, performs
/// `swap(x[i], y[i])`, looking up in both namespace `std` and that of `T`
/// (by ADL). Introspective swap is invoked recursively when necessary.
template <typename T, std::size_t n>
void iswap(T (&x)[n], T (&y)[n]) {
  for (std::size_t i = 0; i < n; ++i) {
    iswap(x[i], y[i]);
  }
}

/// Introspective swap for `std::array`. For each pair of elements `x[i]` and
/// `y[i]`, performs `x[i].swap(y[i])` if possible. Otherwise, performs
/// `swap(x[i], y[i])`, looking up in both namespace `std` and that of `T`
/// (by ADL). Introspective swap is invoked recursively when necessary.
template <typename T, std::size_t n>
void iswap(std::array<T, n>& x, std::array<T, n>& y) {
  for (std::size_t i = 0; i < n; ++i) {
    iswap(x[i], y[i]);
  }
}

template <template <typename> class Pred = std::less,
          typename T, typename... Ts>
const T& min(const T& x, const Ts&... ys) {
  return std::min({std::ref(x), std::ref(ys)...}, Pred<T>{});
}

template <template <typename> class Pred = std::less,
          typename T, typename... Ts>
const T& max(const T& x, const Ts&... ys) {
  return std::max({std::ref(x), std::ref(ys)...}, Pred<T>{});
}

/// Applies `f` to each element of `obj`. `obj` may be a scalar, a linear
/// one-dimensional object, or a multi-dimensional object. `T` may be an array
/// or standard container type. Advanced uses: `f` may accept a multi-dimensional
/// object. In that case, instead of going all the way down to scalar level,
/// `for_each()` stops at the right dimension and applies `f` there.
template <typename T, typename F>
void for_each(T& obj, F f) {
  detail::for_each(obj, f, ' ');
}

} // namespace cppu

#endif // CPPU_ALGORITHM_HPP_
