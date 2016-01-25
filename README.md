# CPP Utility Library (CPPU)

Trinkets and extensions to modern C++

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
