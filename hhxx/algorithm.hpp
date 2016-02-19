// Copyright (c) 2016, Lingxi Li <lilingxi.cs@gmail.com>
// All rights reserved.
// Happy Hacking CXX Library (https://github.com/Lingxi-Li/Happy_Hacking_CXX)

#ifndef HHXX_ALGORITHM_HPP_
#define HHXX_ALGORITHM_HPP_

#include <cassert>
#include <cstddef>
#include <cinttypes>
#include <ctime>

#include <algorithm>
#include <array>
#include <chrono>
#include <functional>
#include <initializer_list>
#include <numeric>
#include <random>
#include <utility>
#include <vector>

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

/// Returns `{ std::cref(x), std::cref(xs)... }`. Sample usage:
/// `std::min(cref_init_list(const_a, b, c))`.
template <class T, class... Ts>
std::initializer_list<std::reference_wrapper<const T>>
cref_init_list(const T& x, const Ts&... xs) {
  return { std::ref(x), std::ref(xs)... };
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

/// Return value can be used to seed pseudo-random number generators. If you
/// intend to use `std::random_device` for this purpose, mind that the
/// performance of many implementations of `std::random_device` degrades sharply
/// once the entropy pool is exhausted.
template <typename Clock = std::chrono::high_resolution_clock>
auto tick_count() {
  return Clock::now().time_since_epoch().count();
}

/// Randomly selects `m` elements from `{0, 1, 2, ..., (n - 1)}` using the
/// pseudo-random number generator `rand`, and copies the result to the range
/// specified by `it`. Since each element in a set of size `n` can be identified
/// using a unique index from `{0, 1, 2, ..., (n - 1)}`, this function template
/// can be used to select a random subset of a given size. `rand` would be
/// invoked `min{m, (n - m)}` times. The space complexity is `O(n)`.
template <typename OutIt, typename RAND = std::minstd_rand,
          typename Uint = typename RAND::result_type>
void sample(std::size_t n, std::size_t m, OutIt it, RAND&& rand =
            RAND(static_cast<Uint>(tick_count()))) {
  assert(m <= n);
  auto swapped = false;
  auto tmp = n - m;
  if (tmp < m) {
    m = tmp;
    swapped = true;
  }
  std::vector<std::size_t> indices(n);
  std::iota(indices.begin(), indices.end(), static_cast<std::size_t>(0));
  auto back_it = indices.end();
  std::uniform_int_distribution<std::size_t> gen;
  for (std::size_t i = 0; i < m; ++i) {
    auto idx = gen(rand, decltype(gen)::param_type(0, n - i - 1));
    std::swap(indices[idx], *--back_it);
  }
  swapped ? std::copy(indices.begin(), back_it, it) :
            std::copy(back_it, indices.end(), it);
}

} // namespace hhxx

#endif // HHXX_ALGORITHM_HPP_
