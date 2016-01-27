# Happy Hacking CXX Library (HHXX)

*Hackish trinkets and extensions to modern C++*

The following two examples should give you a general idea of what HHXX is all about.

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

Truth is it works for objects of any dimensions, even scalars!
Credit goes to @Arcoth (you rock!).

**B. Why should I use `hhxx::iswap(x, y)` to swap `x` and `y`?**

Simply speaking, `hhxx::iswap(x, y)` swaps `x` and `y` in the most specialized
way possible. It first tries to perform `x.swap(y)`. If the expression turns
out to be ill-formed, then tries to perform `swap(x, y)` with
[Argument Dependent Lookup](http://en.cppreference.com/w/cpp/language/adl) (ADL)
enabled. If ADL failed, then as a last resort, performs `std::swap(x, y)`. So,
stay with [`hhxx::iswap()`](https://github.com/Lingxi-Li/Happy_Hacking_CXX/blob/master/manual.md#iswap)
and be happy ever since :smile_cat:

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
