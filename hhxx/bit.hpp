// Copyright (c) 2016, Lingxi Li <lilingxi.cs@gmail.com>
// All rights reserved.
// Happy Hacking CXX Library (https://github.com/Lingxi-Li/Happy_Hacking_CXX)

#ifndef HHXX_BIT_HPP_
#define HHXX_BIT_HPP_

#include <climits>

#include <bitset>
#include <type_traits>

namespace hhxx {

/// The index is zero-based, starting from the least significant bit.
/// MSB is short for most significant bit, and corresponds to the sign bit
/// for singed types.

/// Returns the number of bits used to represent type `T`.
template <typename T>
constexpr unsigned num_bits(T = 0) {
  return sizeof(T) * CHAR_BIT;
}

/// Returns index of the MSB of type `T`.
template <typename T>
constexpr unsigned msb_idx(T = 0) {
  return num_bits<T>() - 1;
}

/// Returns a value of type `T` with a single bit set at index `idx`.
template <typename T>
constexpr T bit_flag(unsigned idx) {
  // since C++14, `1 << (num_bits<int> - 1)` is well-defined and makes `INT_MIN`
  return static_cast<T>(1) << idx;
}

/// Returns a value of type `T` with MSB set only.
template <typename T>
constexpr T msb_flag() {
  return static_cast<T>(1) << msb_idx<T>();
}

/// Tests if the bit at index `idx` of `x` is set.
template <typename T>
constexpr bool test_bit(T x, unsigned idx) {
  return x & bit_flag<T>(idx);
}

/// Tests if the MSB of `x` is set.
template <typename T>
constexpr bool test_msb(T x) {
  return test_bit(x, msb_idx(x));
}

/// Sets the bit at index `idx` of `x` and returns the result.
template <typename T>
constexpr T set_bit(T x, unsigned idx) {
  return x | bit_flag<T>(idx);
}

/// Sets the MSB of `x` and returns the result.
template <typename T>
constexpr T set_msb(T x) {
  return set_bit(x, msb_idx<T>());
}

/// Clears the bit at index `idx` of `x` and returns the result.
template <typename T>
constexpr T clear_bit(T x, unsigned idx) {
  return x & ~bit_flag<T>(idx);
}

/// Clears the MSB of `x` and returns the result.
template <typename T>
constexpr T clear_msb(T x) {
  return clear_bit(x, msb_idx<T>());
}

/// Flips the bit at index `idx` of `x` and returns the result.
template <typename T>
constexpr T flip_bit(T x, unsigned idx) {
  return x ^ bit_flag<T>(idx);
}

/// Flips the MSB of `x` and returns the result.
template <typename T>
constexpr T flip_msb(T x) {
  return flip_bit(x, msb_idx<T>());
}

/// Returns the number of bits set in `x`.
template <typename T>
unsigned num_bits_set(T x) {
  // `std::bitset::count()` may be highly optimized;
  // see http://codereview.stackexchange.com/a/118484/70823
  return static_cast<unsigned>(std::bitset<num_bits<T>()>(x).count());
}

} // namespace hhxx

#endif // HHXX_BIT_HPP_
