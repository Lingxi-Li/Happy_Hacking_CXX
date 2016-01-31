// Copyright (c) 2016, Lingxi Li <lilingxi.cs@gmail.com>
// All rights reserved.
// Happy Hacking CXX Library (https://github.com/Lingxi-Li/Happy_Hacking_CXX)

#ifndef HHXX_SCOPE_GUARD_HPP_
#define HHXX_SCOPE_GUARD_HPP_

#include <utility>

#include "hhxx/macro.hpp"

/// Mainly used to implement RAII with C-style API.

/// Executes the function object as defined by `__VA_ARGS__` upon exiting the
/// enclosing scope. Given multiple such statements, the executions are
/// performed in reverse order of their statements in code.
#define HHXX_ON_SCOPE_EXIT_F(...)                                              \
  auto HHXX_UNIQUE_NAME(hhxx_scope_guard) = hhxx::make_scope_guard(__VA_ARGS__)

#define HHXX_ON_SCOPE_EXIT(...) HHXX_ON_SCOPE_EXIT_F([&] { __VA_ARGS__ })

namespace hhxx {

/// Invokes function object `f` upon destruction. The behavior can be disarmed.
template <typename F>
class scope_guard {
public:
  explicit scope_guard(F f)
      : f_(std::move(f)) {
    // nop
  }

  /// `other` is disarmed after move.
  scope_guard(scope_guard&& other)
      : f_(std::move(other.f_)),
        armed_(std::exchange(other.armed_, false)) {
    // nop
  }

  ~scope_guard() {
    if (armed_) f_();
  }

  scope_guard(const scope_guard&) = delete;
  scope_guard& operator =(const scope_guard&) = delete;
  scope_guard& operator =(scope_guard&&) = delete;

  void disarm() {
    armed_ = false;
  }

private:
  F f_;
  bool armed_ = true;
};

/// Creates a `scope_guard` from `f`.
template <typename F>
auto make_scope_guard(F f) {
  return scope_guard<F>(std::move(f));
}

} // namespace hhxx

#endif // HHXX_SCOPE_GUARD_HPP_
