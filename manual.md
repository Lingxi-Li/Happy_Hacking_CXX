# [HHXX](https://github.com/Lingxi-Li/Happy_Hacking_CXX) Reference Manual

*Hackish trinkets and extensions to modern C++*

## Headers

[`aggregate_wrapper.hpp`](#aggregate_wrapper)
[`algorithm.hpp`](#algorithm_hpp)
[`functional.hpp`](#functional_hpp)
[`multi_view.hpp`](#multi_view)
[`meta.hpp`](#meta_hpp)
[`string.hpp`](#string_hpp)

----------------------------------------

<a name="aggregate_wrapper"></a>
~~~C++
/// Primary template for wrapping non-array aggregate type `T`.
template <typename T>
class aggregate_wrapper : public T {
public:
  using aggregate_type = T;

  /// Forwarding constructor that enables the `()` initialization syntax and
  /// in-place construction. The wrapped aggregate is list-initialized using
  /// the forwarded arguments. Enabled only when the aggregate is initializable
  /// from the arguments. When no argument is provided, value-initialization is
  /// performed.
  template <typename... Ts>
  aggregate_wrapper(Ts&&... xs);
};

/// Specialized template for wrapping array type `T[n]`.
template <typename T, std::size_t n>
class aggregate_wrapper<T[n]> {
public:
  using aggregate_type = T[n];

  template <typename... Ts>
  aggregate_wrapper(Ts&&... xs);
  
  /// You can't initialize an array directly from another. The constructor
  /// default initializes the wrapped array, and then copies/moves each element
  /// from `arr` to it.
  
  aggregate_wrapper(const aggregate_type& arr);
  aggregate_wrapper(aggregate_type&& arr);

  /// Provides transparent access to the wrapped array.
  
  operator T* ();
  operator const T* () const;

  /// Returns the size of the wrapped array.
  std::size_t size() const;
};

/// Makes an `aggregate_wrapper` that wraps `x`.
template <typename T>
auto wrap_aggregate(T&& x);
~~~

Since aggregates do not support initialization using the `()` syntax, they
cannot be in-place constructed with the `emplace*` methods. Wrap them to
support the `()` initialization syntax and enable in-place construction.

While a default initialized aggregate may have an indeterminate value, this
wrapper class ensures that the wrapped aggregate always has a determinate value.

----------------------------------------

<a name="algorithm_hpp"></a>
### `algorithm.hpp`

[`for_each()`](#for_each)
[`iswap()`](#iswap)
[`max()`](#max)
[`min()`](#min)

----------------------------------------

<a name="for_each"></a>
~~~C++
template <typename T, typename F>
void for_each(T& obj, F f);
~~~

Applies `f` to each element of `obj`. `obj` may be a scalar, a linear
one-dimensional object, or a multi-dimensional object. As an example, the code

~~~C++
int arr[5][5][5] = ...
for (auto& slice : arr) {
  for (auto& row : slice) {
    for (auto& col : row) {
      f(col);
    }
  }
}
~~~

could be rewritten as

~~~C++
hhxx::for_each(arr, f);
~~~

**Advanced Use:** `f` may accept a multi-dimensional object. In that case,
instead of going all the way down to scalar (element) level, `for_each()` stops
at the right dimension and applies `f` there. For example,

~~~C++
int arr[5][5][5] = ...
auto f = [](int (&row)[5]) { ... };
hhxx::for_each(arr, f);
~~~

is equivalent to

~~~C++
for (auto& slice : arr) {
  for (auto& row : slice) {
    f(row);
  }
}
~~~

----------------------------------------

<a name="iswap"></a>
~~~C++
template <typename T>
void iswap(T& x, T& y);
~~~

**I**ntrospective **swap**. Swaps `x` and `y` in the most specialized way possible.
It performs `x.swap(y)` if possible. Otherwise, performs `swap(x, y)`, looking
up `swap()` in both namespace `std` and that of `T` (by ADL). If `T` is an array
or `std::array` type, applies the above operation to each pair of elements `x[i]`
and `y[i]`, and invokes introspective swap recursively when necessary.

----------------------------------------

<a name="max"></a>
~~~C++
template <template <typename> class Pred = std::less,
          typename T, typename... Ts>
const T& max(const T& x, const Ts&... ys);
~~~

Returns the maximum of `x`, `ys...`, using `Pred<T>{}` as the less-than predicate.

----------------------------------------

<a name="min"></a>
~~~C++
template <template <typename> class Pred = std::less,
          typename T, typename... Ts>
const T& min(const T& x, const Ts&... ys);
~~~

Returns the minimum of `x`, `ys...`, using `Pred<T>{}` as the less-than predicate.

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

Extended `std::function`, capable of disambiguating overloaded function according
to the specified signature `R(Args...)`. Constructing and assigning from overloaded
functions no longer require help from the user. For example, the following code
does not compile

~~~C++
void func(char);
void func(int);
void gunc(char);
void gunc(int);
std::function<void(char)> f = func;
f = gunc;
~~~

It does compile, however, after replacing `std::function` with `hhxx::function`.

----------------------------------------

<a name="multi_view"></a>
~~~C++
template <typename Iterator>
class multi_view {
public:
  /// Maximum number of dimensions supported.
  static constexpr std::size_t max_dim = 10;

  /// `base` is an iterator addressing the first element of a one-dimensional
  /// object. `extents...` specifies the extent of each dimension of the
  /// multi-dimensional view. So, `sizeof...(extents)` is the number of dimensions.
  template <typename... Ts>
  multi_view(Iterator base, Ts... extents);

  /// Accesses an element. If `sizeof...(indices)` is smaller than the number
  /// of dimensions, remaining indices are zero filled. If `sizeof...(indices)`
  /// is larger than the number of dimensions, extra indices are ignored. At
  /// least one index must be provided.
  template <typename... Ts>
  auto operator ()(Ts... indices) const;
};
~~~

Provides a multi-dimensional view of a one-dimensional linear object. The
linear object can then be accessed like a multi-dimensional one. `Iterator`
specifies the iterator type of the linear object. For example,

~~~C++
std::vector<int> vec{ 1, 2, 3, 4 };
hhxx::multi_view<decltype(vec.begin())> view2x2(vec.begin(), 2, 2);
assert(view2x2(0, 0), 1);
assert(view2x2(0, 1), 2);
assert(view2x2(1, 0), 3);
assert(view2x2(1, 1), 4);
assert(view2x2(1), 3);
assert(view2x2(1, 0, 100), 3);
~~~

----------------------------------------

<a name="meta_hpp"></a>
### `meta.hpp`

[`enable_if_well_formed_t`](#enable_if_well_formed_t)
[`multi_t`](#multi_t)
[`multi_array_t`](#multi_array_t)

[`make_multi()`](#make_multi)

----------------------------------------

<a name="enable_if_well_formed_t"></a>
~~~C++
template <typename, typename T = void>
using enable_if_well_formed_t = T;
~~~

Counterpart to `std::enable_if_t`. Instead of checking a value be true,
this one checks an expression be well-formed. Specifically,
`enable_if_well_formed_t<decltype(expr), T>` gets you `T` if `expr` is well-formed.
In the case `T` is `void`, you could equivalently write `decltype((void)(expr))`.

----------------------------------------

<a name="multi_t"></a>
~~~C++
template <template <typename...> class T, typename Base, std::size_t n>
using multi_t = ...;
~~~

Provides easy syntax for specifying multi-dimensional types. `T` specifies the
container template. `Base` specifies the element type. `n` specifies the
number of dimensions. So, it's like `T<Base>` raised to `n`-dimensions. For example,
`multi_t<std::vector, int, 2>` is equivalent to `std::vector<std::vector<int>>`.

----------------------------------------

<a name="multi_array_t"></a>
~~~C++
template <typename T, std::size_t... ns>
using multi_array_t = ...;
~~~

Provides easy syntax for specifying multi-dimensional `std::array` type. `T`
specifies the element type, `ns...` specifies the extent of each dimension. So
`sizeof...(ns)` is the number of dimensions. For example,
`multi_array_t<int, 2, 3>` is equivalent to `std::array<std::array<int, 3>, 2>`.

----------------------------------------

<a name="make_multi"></a>
~~~C++
template <template <typename...> class T, typename Base, typename... Ts>
auto make_multi(const Base& init_val, Ts... ns);
~~~

Creates a dynamic multi-dimensional object. `T` specifies the container template.
`Base` specifies the element type and can be automatically deduced from `init_val`.
Each element of the constructed multi-dimensional object is initialized to
`init_val`. `ns...` specifies the extent of each dimension. So, `sizeof...(ns)`
is the number of dimensions. For example, `make_multi<std::vector>(7, 2, 3)`
creates a 2x3 multi-dimensional object of type `std::vector<std::vector<int>>`
with each element initialized to 7.

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

Calls either `to_string(x)` or `to_wstring(x)` based on `CharT`. Looking up
`to_string()`/`to_wstring()` in both namespace `std` and that of `T` (by ADL).
By providing a uniform name, this function template facilitates writing generic code.

----------------------------------------
