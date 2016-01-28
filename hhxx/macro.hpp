// Copyright (c) 2016, Lingxi Li <lilingxi.cs@gmail.com>
// All rights reserved.
// Happy Hacking CXX Library (https://github.com/Lingxi-Li/Happy_Hacking_CXX)

#ifndef HHXX_MACRO_HPP_
#define HHXX_MACRO_HPP_

#define HHXX_JOIN2_(a, ...) a##__VA_ARGS__
#define HHXX_JOIN3_(a, b, ...) a##b##__VA_ARGS__
#define HHXX_STR_(...) #__VA_ARGS__

/// Expands and concatenates.
#define HHXX_JOIN2(a, ...) HHXX_JOIN2_(a, __VA_ARGS__)
#define HHXX_JOIN3(a, b, ...) HHXX_JOIN3_(a, b, __VA_ARGS__)

/// Expands and stringifies.
#define HHXX_STR(...) HHXX_STR_(__VA_ARGS__)

/// Expands to `prefix_at_line_<__LINE__>`.
#define HHXX_UNIQUE_NAME(prefix) HHXX_JOIN3(prefix, _at_line_, __LINE__)

#endif // HHXX_MACRO_HPP_
