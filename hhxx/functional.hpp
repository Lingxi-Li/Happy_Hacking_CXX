// Copyright (c) 2016, Lingxi Li <lilingxi.cs@gmail.com>
// All rights reserved.
// Happy Hacking CXX Library (https://github.com/Lingxi-Li/Happy_Hacking_CXX)

#ifndef HHXX_FUNCTIONAL_HPP_
#define HHXX_FUNCTIONAL_HPP_

#include <cstddef>

#include <functional>
#include <tuple>
#include <type_traits>
#include <utility>

#define HHXX_ARG_PACK(Ts, Is) ::hhxx::detail::arg_pack<::std::tuple<Ts...>, ::std::index_sequence<Is...>>
#define HHXX_UNPACK(args, Is) ::std::get<Is>(::std::move(args.vs))...

namespace hhxx {

namespace detail {

template <typename Tuple, typename Indices>
struct arg_pack {
  Tuple vs;
  Indices is;
};

} // namespace detail

template <typename... Ts>
auto pack(Ts&&... args) noexcept {
  std::tuple<Ts&&...> vs(std::forward<Ts>(args)...);
  std::index_sequence_for<Ts...> is;
  return detail::arg_pack<decltype(vs), decltype(is)>{ std::move(vs), is };
}

template <typename>
class function;

/// Extended `std::function`, capable of disambiguating overloaded function
/// according to the specified signature `R(Args...)`. Constructing and
/// assigning from overloaded functions no longer require help from the user.
template <typename R, typename... Args>
class function<R(Args...)> : public std::function<R(Args...)> {
private:
  template <typename F>
  using enable_if_fn_t = std::enable_if_t<
                           std::is_same<R, std::result_of_t<F&&(Args&&...)>>{}>;

public:
  using base = std::function<R(Args...)>;

  function(R(*ptr)(Args...)) : base(ptr) {}

  // inheriting constructors does not work with some standard library
  // implementations; see http://stackoverflow.com/q/34973369/1348273
  // a variadic forwarding constructor doesn't work either;
  // see http://stackoverflow.com/q/34978160/1348273

  function() = default;
  function(std::nullptr_t) : base(nullptr) {}
  template <typename F, typename = enable_if_fn_t<F>>
  function(F f) : base(std::move(f)) {}

  function& operator =(R(*ptr)(Args...)) {
    base::operator =(ptr);
    return *this;
  }

  // makes sure not to return `base&`; so overriding assignment operators in
  // base; besides, a forwarding assignment operator doesn't work here;
  // see http://stackoverflow.com/q/34978160/1348273

  function& operator =(std::nullptr_t) {
    base::operator =(nullptr);
    return *this;
  }
  template <typename F, typename = enable_if_fn_t<F>>
  function& operator =(F&& f) {
    base::operator =(std::forward<F>(f));
    return *this;
  }
  template <typename F, typename = enable_if_fn_t<F>>
  function& operator =(std::reference_wrapper<F> f) {
    base::operator =(f);
    return *this;
  }
};

} // namespace hhxx

#endif // HHXX_FUNCTIONAL_HPP_
