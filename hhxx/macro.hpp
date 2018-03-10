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

#define HHXX_DECLARE_HAS_MEMBER_FUNC(NAME) \
  template<class T, class... ARGS> struct has_member_func_##NAME { \
    template <class U> constexpr static auto check(int) -> decltype(std::declval<U>().NAME(std::declval<ARGS>()...), std::true_type()); \
    template <class U> constexpr static std::false_type check(...); \
    static constexpr bool value = decltype(check<T>(0))::value; \
  }; \
  template <class T> struct has_member_func_##NAME<T, void> { \
    template <class U> constexpr static auto check(int) -> decltype(std::declval<U>().NAME(), std::true_type()); \
    template <class U> constexpr static std::false_type check(...); \
    static constexpr bool value = decltype(check<T>(0))::value; \
  }

#define HHXX_HAS_MEMBER_FUNC(CLASS, MEMBER, ...) \
  has_member_func_##MEMBER<CLASS, __VA_ARGS__>::value

#endif // HHXX_MACRO_HPP_
