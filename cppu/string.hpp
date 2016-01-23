// Copyright (c) 2016, Lingxi Li <lilingxi.cs@gmail.com>
// All rights reserved.
// CPP Utility Library (https://github.com/Lingxi-Li/CPP_Utility)

#ifndef CPPU_STRING_HPP_
#define CPPU_STRING_HPP_

#include <cctype>
#include <cstring>

#include <string>
#include <type_traits>

namespace cppu {

/// Calls either `to_string(x)` or `to_wstring(x)` based on `CharT`. Lookups in
/// namespace `std` and that of `T` (by ADL). By providing a uniform name, this
/// function template facilitates writing generic code.
template <typename CharT, typename T,
          typename = std::enable_if_t<std::is_same<CharT, char>::value>>
std::string to_xstring(const T& x) {
  // explicitly pulls in `std` in case `T` is not a class type
  using std::to_string;
  return to_string(x);
}

/// Calls either `to_string(x)` or `to_wstring(x)` based on `CharT`. Lookups in
/// namespace `std` and that of `T` (by ADL). By providing a uniform name, this
/// function template facilitates writing generic code.
template <typename CharT, typename T,
          typename = std::enable_if_t<std::is_same<CharT, wchar_t>::value>>
std::wstring to_xstring(const T& x) {
  // explicitly pulls in `std` in case `T` is not a class type
  using std::to_wstring;
  return to_wstring(x);
}

} // namespace cppu

#endif // CPPU_STRING_HPP_
