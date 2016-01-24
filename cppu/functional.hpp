// Copyright (c) 2016, Lingxi Li <lilingxi.cs@gmail.com>
// All rights reserved.
// CPP Utility Library (https://github.com/Lingxi-Li/CPP_Utility)

#ifndef CPPU_FUNCTIONAL_HPP_
#define CPPU_FUNCTIONAL_HPP_

#include <cstddef>

#include <functional>
#include <utility>

namespace cppu {

template <typename>
class function;

/// Extended `std::function` capable of disambiguating overloaded function.
/// Constructing and assigning from overloaded functions no longer require
/// help from the user.
template <typename R, typename... Args>
class function<R(Args...)> : public std::function<R(Args...)> {
public:
  using base = std::function<R(Args...)>;

  function(R(*ptr)(Args...)) : base{ptr} {}
  // inheriting constructors does not work with some standard library
  // implementations; see http://stackoverflow.com/q/34973369/1348273
  template <typename... Ts>
  function(Ts... xs) : base{std::forward<Ts>(xs)...} {}
  // the above doesn't cover these two; then why do we need them?
  // see http://stackoverflow.com/a/34977207/1348273;
  // explicit cast to base is necessary, or overload resolution will select
  // a wrong constructor
  template <typename Alloc>
  function(std::allocator_arg_t tag, const Alloc& alloc, const function& other)
      : base{tag, alloc, static_cast<const base&>(other)} {}
  template <typename Alloc>
  function(std::allocator_arg_t tag, const Alloc& alloc, function&& other)
      : base{tag, alloc, std::move(static_cast<base&>(other))} {}

  function& operator =(R(*ptr)(Args...)) {
    base::operator =(ptr);
    return *this;
  }
  // makes sure not to return `base&`
  template <typename T>
  function& operator =(T&& x) {
    base::operator =(std::forward<T>(x));
    return *this;
  }
};

} namespace std {

template <typename R, typename... Args, typename Alloc>
struct uses_allocator<cppu::function<R(Args...)>, Alloc> : true_type {};

} namespace cppu {

} // namespace cppu

#endif // CPPU_FUNCTIONAL_HPP_
