# [CPPU](https://github.com/Lingxi-Li/CPP_Utility) Reference Manual

Handy trinkets that make C++ programming happier~

## Headers

[`algorithm.hpp`](#algorithm_hpp)
[`string.hpp`](#string_hpp)

----------------------------------------

<a name="algorithm_hpp"></a>
### `algorithm.hpp`

[`swap()`](#swap)

----------------------------------------

<a name="swap"></a>
~~~C++
template <typename T>
void swap(T& x, T& y);
~~~

Introspective swap. Performs `x.swap(y)` if possible. Otherwise, performs
`swap(x, y)` and lookups in both namespace `std` and that of `T`. If `T` is
array type, applies the above operation to each pair of elements.

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

Calls either `to_string(x)` or `to_wstring(x)` based on `CharT`. Lookups in
namespace `std` and that of `T` (by ADL). By providing a uniform name, this
function template facilitates writing generic code.

----------------------------------------
