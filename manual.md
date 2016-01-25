# [CPPU](https://github.com/Lingxi-Li/CPP_Utility) Reference Manual

Trinkets and extensions to modern C++

## Headers

[`algorithm.hpp`](#algorithm_hpp)
[`functional.hpp`](#functional_hpp)
[`meta.hpp`](#meta_hpp)
[`string.hpp`](#string_hpp)

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
template <typename T, typename... Ts>
const T& max(const T& x, const T& y, const Ts&... zs);
~~~

Returns the maximum of `x`, `y`, and `zs...`.

----------------------------------------

<a name="min"></a>
~~~C++
template <typename T, typename... Ts>
const T& min(const T& x, const T& y, const Ts&... zs);
~~~

Returns the minimum of `x`, `y`, and `zs...`.

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

----------------------------------------

<a name="enable_if_well_formed_t"></a>
~~~C++
template <typename, typename T = void>
using enable_if_well_formed_t = T;
~~~

Given `enable_if_well_formed_t<decltype(expr), T>`, gets `T` if `expr` is
well-formed.

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
