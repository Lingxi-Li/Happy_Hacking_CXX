// Copyright (c) 2016, Lingxi Li <lilingxi.cs@gmail.com>
// All rights reserved.
// CPP Utility Library (https://github.com/Lingxi-Li/CPP_Utility)

#ifndef CPPU_META_HPP_
#define CPPU_META_HPP_

#include <array>
#include <type_traits>

namespace cppu {

/// Given `enable_if_well_formed_t<decltype(expr), T>`,
/// gets `T` if `expr` is well-formed.
template <typename, typename T = void>
using enable_if_well_formed_t = T;

template <typename T, std::size_t n, std::size_t... ns>
struct multi_array {
  using type = std::array<typename multi_array<T, ns...>::type, n>;
};

template <typename T, std::size_t n>
struct multi_array<T, n> {
  using type = std::array<T, n>;
};

/// Eases the syntax for specifying multi-dimensional `std::array`.
/// `multi_array_t<int, 1, 1>` is equivalent to `std::array<std::array<int, 1>, 1>`
/// and so on.
template <typename T, std::size_t... ns>
using multi_array_t = typename multi_array<T, ns...>::type;

} // namespace cppu

#endif // CPPU_META_HPP_
