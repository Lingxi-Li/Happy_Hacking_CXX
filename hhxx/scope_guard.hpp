// Copyright (c) 2016, Lingxi Li <lilingxi.cs@gmail.com>
// All rights reserved.
// Happy Hacking CXX Library (https://github.com/Lingxi-Li/Happy_Hacking_CXX)

#ifndef HHXX_SCOPE_GUARD_HPP_
#define HHXX_SCOPE_GUARD_HPP_

#include <utility>

#include "hhxx/macro.hpp"

/// Executes the function object as defined by `__VA_ARGS__` upon exiting the
/// enclosing scope. Given multiple such statements, the executions are
/// performed in reverse order of their statement appearance in code.
#define HHXX_ON_SCOPE_EXIT_F(...)                                              \
  auto HHXX_UNIQUE_NAME(hhxx_scope_guard) =                                    \
    hhxx::detail::make_scope_guard(__VA_ARGS__)

#define HHXX_ON_SCOPE_EXIT(...) HHXX_ON_SCOPE_EXIT_F([&]() { __VA_ARGS__ })

namespace hhxx {
namespace detail {

template <typename F>
class scope_guard {
public:
  explicit scope_guard(F f)
      : f_(std::move(f)) {
    // nop
  }
  ~scope_guard() {
    f_();
  }

private:
  F f_;
};

template <typename F>
auto make_scope_guard(F f) {
  return scope_guard<F>(std::move(f));
}

} // namespace detail
} // namespace hhxx

#endif // HHXX_SCOPE_GUARD_HPP_
