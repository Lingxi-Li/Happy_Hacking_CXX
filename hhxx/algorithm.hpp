// Copyright (c) 2016, Lingxi Li <lilingxi.cs@gmail.com>
// All rights reserved.
// Happy Hacking CXX Library (https://github.com/Lingxi-Li/Happy_Hacking_CXX)

#ifndef HHXX_ALGORITHM_HPP_
#define HHXX_ALGORITHM_HPP_

#include <algorithm>
#include <array>
#include <functional>
#include <utility>

#include "meta.hpp"

namespace hhxx {

namespace detail {

template <typename T>
void iswap(T& x, T& y, int) {
  using std::swap;
  swap(x, y);
}

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

/// Introspective swap. Swaps `x` and `y` in the most specialized way possible.
/// It performs `x.swap(y)` if possible. Otherwise, performs `swap(x, y)`, looking
/// up `swap()` in both namespace `std` and that of `T` (by ADL). If `T` is an array
/// or `std::array` type, applies the above operation to each pair of elements `x[i]`
/// and `y[i]`, and invokes introspective swap recursively when necessary.

template <typename T>
void iswap(T& x, T& y) {
  // uses `static_cast<void>()` to ignore possible (though very unlikely) return
  // value from `detail::iswap(int&, int&, char)`
  static_cast<void>(detail::iswap(x, y, ' '));
}

template <typename T, std::size_t n>
void iswap(T (&x)[n], T (&y)[n]) {
  for (std::size_t i = 0; i < n; ++i) {
    iswap(x[i], y[i]);
  }
}

template <typename T, std::size_t n>
void iswap(std::array<T, n>& x, std::array<T, n>& y) {
  for (std::size_t i = 0; i < n; ++i) {
    iswap(x[i], y[i]);
  }
}

/// Returns the minimum of `x`, `ys...`, using `Pred<T>{}` as the less-than predicate.
template <template <typename> class Pred = std::less,
          typename T, typename... Ts>
const T& min(const T& x, const Ts&... ys) {
  return std::min({std::ref(x), std::ref(ys)...}, Pred<T>{});
}

/// Returns the maximum of `x`, `ys...`, using `Pred<T>{}` as the less-than predicate.
template <template <typename> class Pred = std::less,
          typename T, typename... Ts>
const T& max(const T& x, const Ts&... ys) {
  return std::max({std::ref(x), std::ref(ys)...}, Pred<T>{});
}

/// Applies `f` to each element of `obj`. `obj` may be a scalar, a linear
/// one-dimensional object, or a multi-dimensional object. Advanced Use: `f`
/// may accept a multi-dimensional object. In that case, instead of going all
/// the way down to scalar (element) level, `for_each()` stops at the right
/// dimension and applies `f` there.
template <typename T, typename F>
void for_each(T& obj, F f) {
  detail::for_each(obj, f, ' ');
}

} // namespace hhxx

#endif // HHXX_ALGORITHM_HPP_
