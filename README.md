# CPP Utility Library (CPPU)

Trinkets and extensions to modern C++

The following two examples should give you a general idea of what CPPU is all about.

**A. Why should I use `cppu::iswap(x, y)`?**

`cppu::iswap(x, y)` first tries to perform `x.swap(y)`. If the expression turns
out to be ill-formed, then tries to perform `swap(x, y)` with
[Argument Dependent Lookup](http://en.cppreference.com/w/cpp/language/adl) (ADL)
enabled. If ADL failed, then as a last resort, performs `std::swap(x, y)`. So,
stay with [`cppu::iswap()`](https://github.com/Lingxi-Li/CPP_Utility/blob/master/manual.md#iswap)
and be happy ever since :smile_cat:

**B. What does `cppu::make_multi<std::vector>(7, 3, 3, 3)` do?**

Want to create a 3x3x3 multi-dimensional object of type
`std::vector<std::vector<std::vector<int>>>` and initialize each element to 7?
Well, this simple expression does it for you. BTW, you really don't want to
write things like `std::vector<std::vector<std::vector<int>>>`. Do you? So, stay
with [`cppu::multi_t`](https://github.com/Lingxi-Li/CPP_Utility/blob/master/manual.md#multi_t)
and write `cppu::multi_t<std::vector, int, 3>`. CPPU also has a similar thing
for `std::array`. Check out [`cppu::multi_array_t`](https://github.com/Lingxi-Li/CPP_Utility/blob/master/manual.md#multi_array_t).

Feel interested and want to see what CPPU has to offer? There is a reference
[manual](https://github.com/Lingxi-Li/CPP_Utility/blob/master/manual.md)
prepared just for you. So check it out.

Got some shiny trinkets yourself? Please do share it with us. We welcome you to
join the party and play together~ :tada:

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
cppu/.........library header directory
test/.........unit tests directory
manual.md.....reference manual
README.md
LICENSE
~~~

<a name="build"></a>
## Build Instructions

Currently, CPPU is header-only. Add the directory containing `cppu` to include
path and you are ready to go. To build the unit tests, you need to link with
gtest (`gtest` and `gtest_main`).

<a name="license"></a>
## License

[BSD 3-Clause License](https://opensource.org/licenses/BSD-3-Clause)
