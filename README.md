# Happy Hacking CXX Library (HHXX)

*Hackish trinkets and extensions to modern C++*

The following three examples should give you a general idea of what HHXX is all about.

**A. Universal `for_each()`**

Guess you already know about [`std::for_each()`](http://en.cppreference.com/w/cpp/algorithm/for_each).
It doesn't help when things get high(-dimensional). Following is the best you
can do about a three-dimensional object using `std::for_each()`

~~~C++
for (auto& slice : obj_3d) {
  for (auto& row : slice) {
    std::for_each(std::begin(row), std::end(row), f);
  }
}
~~~

With [`hhxx::for_each()`](https://github.com/Lingxi-Li/Happy_Hacking_CXX/blob/master/manual.md#for_each),
you can simply 

~~~C++
hhxx::for_each(obj_3d, f);
~~~

Truth is it works for objects of any dimensions (even scalars!) and of any type
supporting [range-based for loop](http://en.cppreference.com/w/cpp/language/range-for)!

**B. Why should I use `hhxx::iswap(x, y)` to swap `x` and `y`?**

Simply speaking, `hhxx::iswap(x, y)` swaps `x` and `y` in the most specialized
way possible. It first tries to perform `x.swap(y)`. If the expression turns
out to be ill-formed, then tries to perform `swap(x, y)` with
[Argument Dependent Lookup](http://en.cppreference.com/w/cpp/language/adl) (ADL)
enabled. If ADL failed, then as a last resort, performs `std::swap(x, y)`. So,
stay with [`hhxx::iswap()`](https://github.com/Lingxi-Li/Happy_Hacking_CXX/blob/master/manual.md#iswap)
and be happy ever since :smile_cat:

**C. View a one-dimensional linear object as a multi-dimensional one**

Have you ever tried to dynamically allocate the storage using a one-dimensional
linear object, but access it as if it were a multi-dimensional one?
[`hhxx::make_multi_view()`](https://github.com/Lingxi-Li/Happy_Hacking_CXX/blob/master/manual.md#multi_view)
would come to your help. Our mutli view class template provides support for both
element access and iterators. It's dynamic, light-weight, with simple syntax.
[Talk is cheap. Show you the code](https://lkml.org/lkml/2000/8/25/132) :wink:

~~~C++
int storage[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
// viewed as { {1, 2, 3, 4}, {5, 6, 7, 8} }
auto view2x4 = hhxx::make_multi_view(storage, 2, 4);
assert(view2x4(1, 0) == 5);
// addresses { {1, 2, 3, 4}, {5, 6, 7, 8} }
assert(std::distance(view2x4.begin(), view2x4.end()) == 8);
// addresses {5, 6, 7, 8}
assert(std::distance(view2x4.begin(1), view2x4.end(1)) == 4);
// addresses 3
assert(std::distance(view2x4.begin(0, 2), view2x4.end(0, 2)) == 1);
// viewed as { { {1, 2}, {3, 4} }, 
//             { {5, 6}, {7, 8} } }
auto view2x2x2 = hhxx::make_multi_view(storage, 2, 2, 2);
// addresses {5, 6}
assert(std::distance(view2x2x2.begin(1, 0), view2x2x2.end(1, 0)) == 2);
...
~~~

Feel interested and want to see what else HHXX has to offer? There is a reference
[manual](https://github.com/Lingxi-Li/Happy_Hacking_CXX/blob/master/manual.md)
prepared just for you. So check it out.

Got some nice trinkets yourself? Please do share them with us. We invite
you to join the party and play together~ :tada:

- [Dependencies](#depend)
- [File Structure](#struct)
- [Build Instructions](#build)
- [License](#license)

<a name="depend"></a>
## Dependencies

- C++14
- [Google Test](https://github.com/google/googletest) (gtest) for unit tests

<a name="struct"></a>
## File Structure

~~~
hhxx/.........library header directory
test/.........unit tests directory
manual.md.....reference manual
README.md
LICENSE
~~~

<a name="build"></a>
## Build Instructions

Currently, HHXX is header-only. Add the directory containing `hhxx` to your
include path and you are ready to go. To build the unit tests, you need to link
with gtest (`gtest` and [`gtest_main`](https://github.com/google/googletest/blob/master/googletest/docs/Primer.md#writing-the-main-function)).

<a name="license"></a>
## License

[BSD 3-Clause License](https://opensource.org/licenses/BSD-3-Clause)
