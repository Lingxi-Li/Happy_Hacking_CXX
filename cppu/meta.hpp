// Copyright (c) 2016, Lingxi Li <lilingxi.cs@gmail.com>
// All rights reserved.
// CPP Utility Library (https://github.com/Lingxi-Li/CPP_Utility)

#ifndef CPPU_META_HPP_
#define CPPU_META_HPP_

#include <type_traits>

namespace cppu {

/// Given `enable_if_well_formed_t<decltype(expr), T>`,
/// gets `T` if `expr` is well-formed.
template <typename, typename T = void>
using enable_if_well_formed_t = T;

} // namespace cppu

#endif // CPPU_META_HPP_
