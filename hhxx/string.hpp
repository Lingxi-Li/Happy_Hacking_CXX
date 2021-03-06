// Copyright (c) 2016, Lingxi Li <lilingxi.cs@gmail.com>
// All rights reserved.
// Happy Hacking CXX Library (https://github.com/Lingxi-Li/Happy_Hacking_CXX)

#ifndef HHXX_STRING_HPP_
#define HHXX_STRING_HPP_

#include <cctype>
#include <cstring>

#include <string>
#include <type_traits>

namespace hhxx {

/// Calls either `to_string(x)` or `to_wstring(x)` based on `CharT`. Looking up
/// `to_string()`/`to_wstring()` in both namespace `std` and that of `T` (by ADL).
/// By providing a uniform name, this function template facilitates writing generic code.

template <typename CharT, typename T,
          typename = std::enable_if_t<std::is_same<CharT, char>{}>>
std::string to_xstring(const T& x) {
  using std::to_string;
  return to_string(x);
}

template <typename CharT, typename T,
          typename = std::enable_if_t<std::is_same<CharT, wchar_t>{}>>
std::wstring to_xstring(const T& x) {
  using std::to_wstring;
  return to_wstring(x);
}

} // namespace hhxx

#endif // HHXX_STRING_HPP_
