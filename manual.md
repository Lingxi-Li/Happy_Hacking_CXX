# [CPPU](https://github.com/Lingxi-Li/CPP_Utility) Reference Manual

Handy trinkets that make C++ programming happier~

## Headers

[`algorithm.hpp`](#algorithm_hpp)
[`functional.hpp`](#functional_hpp)
[`string.hpp`](#string_hpp)

----------------------------------------

<a name="algorithm_hpp"></a>
### `algorithm.hpp`

[`iswap()`](#iswap)

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
