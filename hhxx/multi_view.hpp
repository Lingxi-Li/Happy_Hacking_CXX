// Copyright (c) 2016, Lingxi Li <lilingxi.cs@gmail.com>
// All rights reserved.
// Happy Hacking CXX Library (https://github.com/Lingxi-Li/Happy_Hacking_CXX)

#ifndef HHXX_MULTI_VIEW_HPP_
#define HHXX_MULTI_VIEW_HPP_

#include <cassert>
#include <cstddef>

#include <algorithm>
#include <initializer_list>
#include <utility>

namespace hhxx {

/// Provides a multi-dimensional view of a one-dimensional linear object. The
/// linear object can then be accessed like a multi-dimensional one. `Iterator`
/// specifies the iterator type of the linear object.

template <typename Iterator>
class multi_view {
public:
  /// Maximum number of dimensions supported.
  static constexpr std::size_t max_dim = 10;

  /// `base` is an iterator addressing the first element of a one-dimensional
  /// object. `extents...` specifies the extent of each dimension of the
  /// multi-dimensional view. So, `sizeof...(extents)` is the number of dimensions.
  template <typename... Ts>
  multi_view(Iterator base, Ts... extents)
      : base_(base),
        steps_{} {
    constexpr auto n = sizeof...(extents);
    static_assert(0 < n && n <= max_dim, "");
    auto init_list = { extents... };
    std::copy(init_list.begin(), init_list.end(), steps_);
    auto i = n - 1;
    std::size_t acc = 1;
    do {
      acc *= std::exchange(steps_[i], acc);
    }
    while (i-- > 0);
    assert(acc);
  }

  /// Accesses an element. If `sizeof...(indices)` is smaller than the number
  /// of dimensions, remaining indices are zero filled. If `sizeof...(indices)`
  /// is larger than the number of dimensions, extra indices are ignored. At
  /// least one index must be provided.
  template <typename... Ts>
  auto operator ()(Ts... indices) const {
    static_assert(sizeof...(indices) > 0, "");
    auto idxes = std::begin({ indices... });
    std::size_t offset = 0;
    for (std::size_t i = 0; i < sizeof...(indices) && steps_[i]; ++i) {
      assert(idxes[i] >= 0);
      offset += idxes[i] * steps_[i];
    }
    return *(base_ + offset);
  }

private:
  Iterator base_;
  std::size_t steps_[max_dim + 1];
};

} // namespace hhxx

#endif // HHXX_MULTI_VIEW_HPP_
