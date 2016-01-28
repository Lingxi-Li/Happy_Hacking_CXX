// Copyright (c) 2016, Lingxi Li <lilingxi.cs@gmail.com>
// All rights reserved.
// Happy Hacking CXX Library (https://github.com/Lingxi-Li/Happy_Hacking_CXX)

#ifndef HHXX_META_HPP_
#define HHXX_META_HPP_

#include <array>
#include <type_traits>
#include <utility>

namespace hhxx {

namespace detail {

template <typename T, std::size_t n, std::size_t... ns>
struct multi_array {
  using type = std::array<typename multi_array<T, ns...>::type, n>;
};

template <typename T, std::size_t n>
struct multi_array<T, n> {
  using type = std::array<T, n>;
};

template <template <typename...> class T, typename Base, std::size_t n>
struct multi {
  static_assert(n > 0, "");
  using type = T<typename multi<T, Base, n - 1>::type>;
};

template <template <typename...> class T, typename Base>
struct multi<T, Base, 1> {
  using type = T<Base>;
};

} // namespace detail

/// Counterpart to `std::enable_if_t`. Instead of checking a value be true,
/// this one checks an expression be well-formed. Specifically,
/// `enable_if_well_formed_t<decltype(expr), T>` gets you `T` if `expr` is
/// well-formed. In the case `T` is `void`, you could equivalently write
/// `decltype((void)(expr))`.
template <typename, typename T = void>
using enable_if_well_formed_t = T;

/// Provides easy syntax for specifying multi-dimensional `std::array` type. `T`
/// specifies the element type, `ns...` specifies the extent of each dimension.
/// So `sizeof...(ns)` is the number of dimensions. For example,
/// `multi_array_t<int, 2, 3>` is equivalent to `std::array<std::array<int, 3>, 2>`.
template <typename T, std::size_t... ns>
using multi_array_t = typename detail::multi_array<T, ns...>::type;

/// Provides easy syntax for specifying multi-dimensional types.
/// `T` specifies the container template. `Base` specifies the
/// element type. `n` specifies the number of dimensions. So, it's
/// like `T<Base>` raised to `n`-dimensions. For example,
/// `multi_t<std::vector, int, 2>` is equivalent to `std::vector<std::vector<int>>`.
template <template <typename...> class T, typename Base, std::size_t n>
using multi_t = typename detail::multi<T, Base, n>::type;

template <template <typename...> class T, typename Base, typename N>
auto make_multi(const Base& init_val, N n) {
  return T<Base>(n, init_val);
}

/// Creates a dynamic multi-dimensional object. `T` specifies the container template.
/// `Base` specifies the element type and can be automatically deduced from `init_val`.
/// Each element of the constructed multi-dimensional object is initialized to
/// `init_val`. `ns...` specifies the extent of each dimension. So, `sizeof...(ns)`
/// is the number of dimensions. For example, `make_multi<std::vector>(7, 2, 3)`
/// creates a 2x3 multi-dimensional object of type `std::vector<std::vector<int>>`
/// with each element initialized to 7.
template <template <typename...> class T, typename Base,
          typename N, typename... Ts>
auto make_multi(const Base& init_val, N n, Ts... ns) {
  return multi_t<T, Base, 1 + sizeof...(ns)>(
           n, make_multi<T>(init_val, ns...));
}

/// Returns `x.size()` is the expression is well-formed.
/// For array types `X[n]`, returns `n`.

template <typename T>
auto size(const T& x) -> decltype(x.size()) {
  return x.size();
}

template <typename T, std::size_t n>
auto size(T (&)[n]) {
  return n;
}

} // namespace hhxx

#endif // HHXX_META_HPP_
