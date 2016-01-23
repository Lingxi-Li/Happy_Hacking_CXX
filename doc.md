# [CPPU](https://github.com/Lingxi-Li/CPP_Utility) Reference Manual

Handy trinkets that make C++ programming happier~

## Headers

[`string.hpp`](#string_hpp)

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
