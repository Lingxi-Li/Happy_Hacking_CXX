# [CPPU](https://github.com/Lingxi-Li/CPP_Utility) Reference Manual

Trinkets and extensions to modern C++

## Headers

[`aggregate_wrapper.hpp`](#aggregate_wrapper_hpp)
[`algorithm.hpp`](#algorithm_hpp)
[`functional.hpp`](#functional_hpp)
[`meta.hpp`](#meta_hpp)
[`string.hpp`](#string_hpp)

----------------------------------------

<a name="aggregate_wrapper_hpp"></a>
### `aggregate_wrapper.hpp`

[`aggregate_wrapper`](#aggregate_wrapper)

----------------------------------------

<a name="aggregate_wrapper"></a>
~~~C++
template <typename T>
class aggregate_wrapper {
public:
  using aggregate_type = T;

  template <typename... Ts>
  aggregate_wrapper(Ts&&... xs);
};

template <typename T, std::size_t n>
class aggregate_wrapper<T[n]> {
public:
  using aggregate_type = T[n];

  template <typename... Ts>
  aggregate_wrapper(Ts&&... xs);
  aggregate_wrapper(const aggregate_type& arr);
  aggregate_wrapper(aggregate_type&& arr);

  operator T* ();
  operator const T* () const;
  
  std::size_t size() const;
};

template <typename T>
auto wrap_aggregate(T&& x);
~~~

Wraps aggregates and provides a variadic forwarding constructor. Enables
in-place construction. Value initializes the aggregate when default constructed.

----------------------------------------

<a name="algorithm_hpp"></a>
### `algorithm.hpp`

[`iswap()`](#iswap)
[`max()`](#max)
[`min()`](#min)

----------------------------------------

<a name="iswap"></a>
~~~C++
template <typename T>
void iswap(T& x, T& y);
~~~

**I**ntrospective **swap**. Performs `x.swap(y)` if possible. Otherwise,
performs `swap(x, y)`, looking up in both namespace `std` and that of `T`
(by ADL). If `T` is an array or `std::array` type, applies the above operation
to each pair of elements `x[i]` and `y[i]`. Introspective swap is invoked
recursively when necessary.

----------------------------------------

<a name="max"></a>
~~~C++
template <template <typename> class Pred = std::less,
          typename T, typename... Ts>
const T& max(const T& x, const Ts&... ys);
~~~

Returns the maximum of `x`, `ys...` using `Pred<T>{}`.

----------------------------------------

<a name="min"></a>
~~~C++
template <template <typename> class Pred = std::less,
          typename T, typename... Ts>
const T& min(const T& x, const Ts&... ys);
~~~

Returns the minimum of `x`, `ys...` using `Pred<T>{}`.

----------------------------------------

<a name="functional_hpp"></a>
### `functional.hpp`

[`function`](#function)

----------------------------------------

<a name="function"></a>
~~~C++
template <typename R, typename... Args>
class function<R(Args...)>;
~~~

Extended `std::function` capable of disambiguating overloaded function.
Constructing and assigning from overloaded functions no longer require
help from the user.

----------------------------------------

<a name="meta_hpp"></a>
### `meta.hpp`

[`enable_if_well_formed_t`](#enable_if_well_formed_t)
[`multi_t`](#multi_t)
[`multi_array_t`](#multi_array_t)

----------------------------------------

<a name="enable_if_well_formed_t"></a>
~~~C++
template <typename, typename T = void>
using enable_if_well_formed_t = T;
~~~

Given `enable_if_well_formed_t<decltype(expr), T>`, gets `T` if `expr` is
well-formed.

----------------------------------------

<a name="multi_t"></a>
~~~C++
template <template <typename...> class T, typename Base, std::size_t n>
using multi_t = ...;
~~~

Provides easy syntax for specifying multi-dimensional types. For example,
`multi_t<std::vector, int, 2>` is equivalent to `std::vector<std::vector<int>>`.

----------------------------------------

<a name="multi_array_t"></a>
~~~C++
template <typename T, std::size_t... ns>
using multi_array_t = ...;
~~~

Eases the syntax for specifying multi-dimensional `std::array`.
`multi_array_t<int, 1, 1>` is equivalent to `std::array<std::array<int, 1>, 1>`
and so on.

----------------------------------------

<a name="string_hpp"></a>
### `string.hpp`

[`to_xstring()`](#to_xstring)

----------------------------------------

<a name="to_xstring"></a>
~~~C++
template <typename CharT, typename T>
auto to_xstring(const T& x);
~~~

Calls either `to_string(x)` or `to_wstring(x)` based on `CharT`. Lookups in both
namespace `std` and that of `T` (by ADL). By providing a uniform name, this
function template facilitates writing generic code.

----------------------------------------
