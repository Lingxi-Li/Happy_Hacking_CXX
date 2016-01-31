// Copyright (c) 2016, Lingxi Li <lilingxi.cs@gmail.com>
// All rights reserved.
// Happy Hacking CXX Library (https://github.com/Lingxi-Li/Happy_Hacking_CXX)

#ifndef HHXX_BIT_HPP_
#define HHXX_BIT_HPP_

#include <type_traits>

namespace hhxx {

/// The index is zero-based, starting from the least significant bit.
/// The most significant bit or sign bit is the head bit.

/// Returns the number of bits used to represent type `T`.
template <typename T>
constexpr unsigned num_bits(T = 0) {
  return sizeof(T) << 3;
}

/// Returns index of of the head bit of type `T`.
template <typename T>
constexpr unsigned head_bit_idx(T = 0) {
  return num_bits<T>() - 1;
}

/// Returns a value of type `T` with a single bit set at index `idx`.
template <typename T>
T bit_flag(unsigned idx) {
  // since C++14, `1 << (num_bits<int> - 1)` is well-defined and makes `INT_MIN`
  return static_cast<T>(1) << idx;
}

/// Returns a value of type `T` with head bit set only.
template <typename T>
constexpr T head_bit_flag() {
  return static_cast<T>(1) << head_bit_idx<T>();
}

/// Tests if the bit at index `idx` of `x` is set.
template <typename T>
bool test_bit(T x, unsigned idx) {
  return x & bit_flag<T>(idx);
}

/// Tests if the head bit of `x` is set.
template <typename T>
bool test_head_bit(T x) {
  return test_bit(x, head_bit_idx(x));
}

/// Sets the bit at index `idx` of `x` and returns the result.
template <typename T>
T set_bit(T x, unsigned idx) {
  return x | bit_flag<T>(idx);
}

/// Sets the head bit of `x` and returns the result.
template <typename T>
T set_head_bit(T x) {
  return set_bit(x, head_bit_idx<T>());
}

/// Clears the bit at index `idx` of `x` and returns the result.
template <typename T>
T clear_bit(T x, unsigned idx) {
  return x & ~bit_flag<T>(idx);
}

/// Clears the head bit of `x` and returns the result.
template <typename T>
T clear_head_bit(T x) {
  return clear_bit(x, head_bit_idx<T>());
}

/// Flips the bit at index `idx` of `x` and returns the result.
template <typename T>
T flip_bit(T x, unsigned idx) {
  return x ^ bit_flag<T>(idx);
}

/// Flips the head bit of `x` and returns the result.
template <typename T>
T flip_head_bit(T x) {
  return flip_bit(x, head_bit_idx<T>());
}

/// Returns the number of bits set in `x`.
template <typename T>
unsigned num_bits_set(T x) {
  unsigned cnt = 0;
  // behavior of signed type underflow is unspecified
  std::make_unsigned_t<T> v = x;
  while (v) {
    ++cnt;
    v &= v - 1;
  }
  return cnt;
}

} // namespace hhxx

#endif // HHXX_BIT_HPP_
