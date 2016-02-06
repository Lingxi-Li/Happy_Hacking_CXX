# [HHXX](https://github.com/Lingxi-Li/Happy_Hacking_CXX) Reference Manual

*Hackish trinkets and extensions to modern C++*

## Headers

[`aggregate_wrapper.hpp`](#aggregate_wrapper)
[`algorithm.hpp`](#algorithm_hpp)
[`bit.hpp`](#bit_hpp)
[`functional.hpp`](#functional_hpp)
[`macro.hpp`](#macro_hpp)
[`multi_view.hpp`](#multi_view)
[`mutable_heap.hpp`](#mutable_heap)
[`meta.hpp`](#meta_hpp)
[`scope_guard.hpp`](#scope_guard)
[`string.hpp`](#string_hpp)
[`union_find_set.hpp`](#union_find_set)

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
  constexpr aggregate_wrapper(Ts&&... xs);
};

/// Specialized template for wrapping array type `T[n]`.
template <typename T, std::size_t n>
class aggregate_wrapper<T[n]> {
public:
  using aggregate_type = T[n];

  template <typename... Ts>
  constexpr aggregate_wrapper(Ts&&... xs);
  
  /// You can't initialize an array directly from another. The constructor
  /// default initializes the wrapped array, and then copies/moves each element
  /// from `arr` to it.
  
  constexpr aggregate_wrapper(const aggregate_type& arr);
  constexpr aggregate_wrapper(aggregate_type&& arr);

  /// Provides transparent access to the wrapped array.
  
  operator T* ();
  operator const T* () const;

  /// Returns size of the wrapped array.
  static constexpr auto size();
};

/// Makes an `aggregate_wrapper` that wraps `x`.
template <typename T>
constexpr auto wrap_aggregate(T&& x);
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
[`sample()`](#sample)
[`tick_count()`](#tick_count)

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
at the right dimension and applies `f` there.

Example:

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

<a name="max"></a>
~~~C++
template <template <typename> class Pred = std::less,
          typename T, typename... Ts>
const T& max(const T& x, const Ts&... ys);
~~~

Returns the maximum of `x`, `ys...`, using `Pred<T>{}` as the less-than predicate.

<a name="min"></a>
~~~C++
template <template <typename> class Pred = std::less,
          typename T, typename... Ts>
const T& min(const T& x, const Ts&... ys);
~~~

Returns the minimum of `x`, `ys...`, using `Pred<T>{}` as the less-than predicate.

<a name="sample"></a>
~~~C++
template <typename OutIt, typename RAND = std::minstd_rand,
          typename Uint = typename RAND::result_type>
void sample(std::size_t n, std::size_t m, OutIt it, RAND&& rand =
            RAND(static_cast<Uint>(tick_count())));
~~~

Randomly selects `m` elements from `{0, 1, 2, ..., (n - 1)}` using the
pseudo-random number generator `rand`, and copies the result to the range
specified by `it`. Since each element in a set of size `n` can be identified
using a unique index from `{0, 1, 2, ..., (n - 1)}`, this function template
can be used to select a random subset of a given size. `rand` would be
invoked `min{m, (n - m)}` times. The space complexity is `O(n)`.

<a name="tick_count"></a>
~~~C++
template <typename Clock = std::chrono::high_resolution_clock>
auto tick_count();
~~~

Shorthand for `Clock::now().time_since_epoch().count()`. Return value can be
used to seed pseudo-random number generators. If you intend to use
`std::random_device` for this purpose, mind that the performance of many
implementations of `std::random_device` degrades sharply once the entropy pool
is exhausted.

----------------------------------------

<a name="bit_hpp"></a>
### `bit.hpp`

The index is zero-based, starting from the least significant bit.
MSB is short for most significant bit, and corresponds to the sign bit
for singed types.

[`num_bits()`](#num_bits)
[`msb_idx()`](#msb_idx)
[`bit_flag()`](#bit_flag)
[`msb_flag()`](#msb_flag)
[`test_bit()`](#test_bit)
[`test_msb()`](#test_msb)
[`set_bit()`](#set_bit)
[`set_msb()`](#set_msb)
[`clear_bit()`](#clear_bit)
[`clear_msb()`](#clear_msb)
[`flip_bit()`](#flip_bit)
[`flip_msb()`](#flip_msb)
[`num_bits_set()`](#num_bits_set)

<a name="num_bits"></a>
~~~C++
template <typename T>
constexpr unsigned num_bits(T = 0);
~~~

Returns the number of bits used to represent type `T`.

<a name="msb_idx"></a>
~~~C++
template <typename T>
constexpr unsigned msb_idx(T = 0);
~~~

Returns index of the MSB of type `T`.

<a name="bit_flag"></a>
~~~C++
template <typename T>
constexpr T bit_flag(unsigned idx);
~~~

Returns a value of type `T` with a single bit set at index `idx`.

<a name="msb_flag"></a>
~~~C++
template <typename T>
constexpr T msb_flag();
~~~

Returns a value of type `T` with the MSB set only.

<a name="test_bit"></a>
~~~C++
template <typename T>
constexpr bool test_bit(T x, unsigned idx);
~~~

Tests if the bit at index `idx` of `x` is set.

<a name="test_msb"></a>
~~~C++
template <typename T>
constexpr bool test_msb(T x);
~~~

Tests if the MSB of `x` is set.

<a name="set_bit"></a>
~~~C++
template <typename T>
constexpr T set_bit(T x, unsigned idx);
~~~

Sets the bit at index `idx` of `x` and returns the result.

<a name="set_msb"></a>
~~~C++
template <typename T>
constexpr T set_msb(T x);
~~~

Sets the MSB of `x` and returns the result.

<a name="clear_bit"></a>
~~~C++
template <typename T>
constexpr T clear_bit(T x, unsigned idx);
~~~

Clears the bit at index `idx` of `x` and returns the result.

<a name="clear_msb"></a>
~~~C++
template <typename T>
constexpr T clear_msb(T x);
~~~

Clears the MSB of `x` and returns the result.

<a name="flip_bit"></a>
~~~C++
template <typename T>
constexpr T flip_bit(T x, unsigned idx);
~~~

Flips the bit at index `idx` of `x` and returns the result.

<a name="flip_msb"></a>
~~~C++
template <typename T>
constexpr T flip_msb(T x);
~~~

Flips the MSB of `x` and returns the result.

<a name="num_bits_set"></a>
~~~C++
template <typename T>
unsigned num_bits_set(T x);
~~~

Returns the number of bits set in `x`.

----------------------------------------

<a name="functional_hpp"></a>
### `functional.hpp`

[`function`](#function)

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

<a name="macro_hpp"></a>
### `macro.hpp`

[`HHXX_STR()`](#hhxx_str)
[`HHXX_JOIN2()/HHXX_JOIN3()`](#hhxx_join)
[`HHXX_UNIQUE_NAME()`](#hhxx_unique_name)

<a name="hhxx_str"></a>
~~~C++
#define HHXX_STR(...) ...
~~~

Expands and stringifies.

<a name="hhxx_join"></a>
~~~C++
#define HHXX_JOIN2(a, ...) ...
#define HHXX_JOIN3(a, b, ...) ...
~~~

Expands and concatenates.

<a name="hhxx_unique_name"></a>
~~~C++
#define HHXX_UNIQUE_NAME(prefix) ...
~~~

Expands to `prefix_at_line_<__LINE__>`.

----------------------------------------

<a name="multi_view"></a>
~~~C++
template <typename Iterator>
class multi_view {
public:
  /// Maximum number of dimensions supported.
  static constexpr std::size_t max_dim = 10;

  /// `base` is an iterator denoting a one-dimensional linear range. `extents...`
  /// specifies the extent of each dimension of the multi-dimensional view.
  /// So, `sizeof...(extents)` is the number of dimensions.
  template <typename... Ts>
  multi_view(Iterator base, Ts... extents);

  /// Returns a begin iterator of the sub-object at `indices...`. An empty set of
  /// `indices` returns a begin iterator of the multi-dimensional object itself.
  template <typename... Ts>
  auto begin(Ts... indices) const;

  /// Returns an end iterator of the sub-object at `indices...`. An empty set of
  /// `indices` returns an end iterator of the multi-dimensional object itself.
  template <typename... Ts>
  auto end(Ts... indices) const;

  /// Accesses the element at `indices...`. If `sizeof...(indices)` is smaller
  /// than the number of dimensions, missing indices are zero filled.
  template <typename... Ts>
  auto operator ()(Ts... indices) const;
};

/// Makes a `multi_view` of the range beginning at `base` with dimension extents
/// `extents...`.
template <typename Iterator, typename... Ts>
auto make_multi_view(Iterator base, Ts... extents);
~~~

Provides a multi-dimensional view of a one-dimensional linear range. The
linear range can then be accessed in a multi-dimensional fashion. `Iterator`
specifies the iterator type used to denote the linear range.

Example:

~~~C++
std::vector<int> vec{ 1, 2, 3, 4 };
// viewd as { {1, 2}, {3, 4} }
auto view2x2 = hhxx::make_multi_view(vec.begin(), 2, 2);
assert(view2x2(0, 0), 1);
assert(view2x2(0, 1), 2);
assert(view2x2(1, 0), 3);
assert(view2x2(1, 1), 4);
assert(view2x2(), 1);  // equivalent to view2x2(0, 0)
assert(view2x2(1), 3); // equivalent to view2x2(1, 0)
// addresses { {1, 2}, {3, 4} }
assert(std::distance(view2x2.begin(), view2x2.end()), 4);
// addresses {3, 4}
assert(std::distance(view2x2.begin(1), view2x2.end(1), 2);
// addresses 4
assert(std::distance(view2x2.begin(1, 1), view2x2.end(1, 1), 1);
int storage[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
// viewed as { { {1, 2}, {3, 4} }, 
               { {5, 6}, {7, 8} } }
auto view2x2x2 = hhxx::make_multi_view(storage, 2, 2, 2);
// addresses {5, 6}
assert(std::distance(view2x2x2.begin(1, 0), view2x2x2.end(1, 0)) == 2);
~~~

----------------------------------------

<a name="mutable_heap"></a>
~~~C++
template <class Less = std::less<std::uintptr_t>>
class mutable_heap {
public:
  using key_type = std::uintptr_t;
  using pos_type = std::size_t;

  /// Constructs a mutable heap using `less` as the less-than comparator.
  explicit mutable_heap(Less less = Less{});

  /// Constructs a mutable heap over the objects referenced by keys
  /// `[first, last)` using `less` as the less-than comparator. All elements in
  /// `[first, last)` should be distinct.
  template <class ForwardIt>
  mutable_heap(ForwardIt first, ForwardIt last, Less less = Less{});
  
  /// Constructs a mutable heap over the objects referenced by keys
  /// in `list` using `less` as the less-than comparator. All elements in `list`
  /// should be distinct.
  explicit mutable_heap(std::initializer_list<std::uintptr_t> list,
                        Less less = Less{});

  /// Returns root of the heap.
  key_type top() const;

  /// Takes and returns root of the heap.
  key_type pop();

  /// Add the object referenced by `key` to the heap. If it's already in the
  /// heap, its position in the heap is updated if necessary.
  void push(key_type key);

  /// Same as `push()`.
  void emplace(key_type key);

  /// Empties the heap.
  void clear();

  /// Returns the number of elements in the heap.
  auto size() const;

  /// Returns whether the heap is empty.
  bool empty() const;

  /// Reserves storage for `cap` elements.
  void reserve(pos_type cap);
};
~~~

Binary max-heap with mutable priorities. `Less` is the less-than comparator
type that compares the priorities of objects referenced by key type `std::uintptr_t`.

----------------------------------------

<a name="meta_hpp"></a>
### `meta.hpp`

[`enable_if_well_formed_t`](#enable_if_well_formed_t)
[`multi_t`](#multi_t)
[`multi_array_t`](#multi_array_t)

[`make_multi()`](#make_multi)
[`size()`](#size)

<a name="enable_if_well_formed_t"></a>
~~~C++
template <typename, typename T = void>
using enable_if_well_formed_t = T;
~~~

Counterpart to `std::enable_if_t`. Instead of checking a value be true,
this one checks an expression be well-formed. Specifically,
`enable_if_well_formed_t<decltype(expr), T>` gets you `T` if `expr` is well-formed.
In the case `T` is `void`, you could equivalently write `decltype((void)(expr))`.

<a name="multi_t"></a>
~~~C++
template <template <typename...> class T, typename Base, std::size_t n>
using multi_t = ...;
~~~

Provides easy syntax for specifying multi-dimensional types. `T` specifies the
container template. `Base` specifies the element type. `n` specifies the
number of dimensions. So, it's like `T<Base>` raised to `n`-dimensions. For example,
`multi_t<std::vector, int, 2>` is equivalent to `std::vector<std::vector<int>>`.

<a name="multi_array_t"></a>
~~~C++
template <typename T, std::size_t... ns>
using multi_array_t = ...;
~~~

Provides easy syntax for specifying multi-dimensional `std::array` type. `T`
specifies the element type, `ns...` specifies the extent of each dimension. So
`sizeof...(ns)` is the number of dimensions. For example,
`multi_array_t<int, 2, 3>` is equivalent to `std::array<std::array<int, 3>, 2>`.

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

<a name="size"></a>
~~~C++
template <typename T>
auto size(const T& x);
~~~

Returns `x.size()` is the expression is well-formed. For array types `X[n]`, returns `n`.

Example:

~~~C++
int arr[2] = {};
std::vector<int> vec(3);
assert(hhxx::size(arr) == 2);
assert(hhxx::size(vec) == 3);
~~~

----------------------------------------

<a name="scope_guard"></a>
~~~C++
/// Executes the function object as defined by `__VA_ARGS__` upon exiting the
/// enclosing scope. Given multiple such statements, the executions are
/// performed in reverse order of their statements in code.
#define HHXX_ON_SCOPE_EXIT_F(...) ...
#define HHXX_ON_SCOPE_EXIT(...) HHXX_ON_SCOPE_EXIT_F([&] { __VA_ARGS__ })

/// Invokes function object `f` upon destruction. The behavior can be disarmed.
template <typename F>
class scope_guard {
public:
  explicit scope_guard(F f);
  /// `other` is disarmed after move.
  scope_guard(scope_guard&& other);
  
  scope_guard(const scope_guard&) = delete;
  scope_guard& operator =(const scope_guard&) = delete;
  scope_guard& operator =(scope_guard&&) = delete;
  
  void disarm();
};

/// Creates a `scope_guard` from `f`.
template <typename F>
auto make_scope_guard(F f);
~~~

Mainly used to implement [RAII](http://en.cppreference.com/w/cpp/language/raii)
with C-style API.

Example:

~~~C++
int i = 0;
{
  HHXX_ON_SCOPE_EXIT_F([&] {
    assert(++i == 3);
  });
  auto guard3 = hhxx::make_scope_guard([&] {
    assert(++i == 3);
  });  
  auto guard2 = hhxx::make_scope_guard([&] {
    assert(++i == 2);
  });
  HHXX_ON_SCOPE_EXIT(
    assert(++i == 1);
  );
  guard3.disarm();
}
assert(i == 3);
~~~

----------------------------------------

<a name="string_hpp"></a>
### `string.hpp`

[`to_xstring()`](#to_xstring)

<a name="to_xstring"></a>
~~~C++
template <typename CharT, typename T>
auto to_xstring(const T& x);
~~~

Calls either `to_string(x)` or `to_wstring(x)` based on `CharT`. Looking up
`to_string()`/`to_wstring()` in both namespace `std` and that of `T` (by ADL).
By providing a uniform name, this function template facilitates writing generic code.

----------------------------------------

<a name="union_find_set"></a>
~~~C++
class union_find_set {
public:
  /// Type of keys used to reference elements and sets.
  using key_type = std::uintptr_t;

  /// Returns the largest set containing `key`.
  key_type find(key_type key);

  /// Merges the largest sets containing `a` and `b` respectively, and returns
  /// the resulting union set.
  key_type unite(key_type a, key_type b);

  /// Resets to initial state where each element is in a set of its own
  /// referenced by the same key.
  void reset();
};
~~~

Disjoint sets data structure. Elements and sets are referenced by keys of type
`std::uintptr_t`. In the initial state, each element `x` within `[0, UINTPTR_MAX]`
is in a set of its own referenced by the same key `x`.
