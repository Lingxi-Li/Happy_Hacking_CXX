# CPP Utility Library (CPPU)

Handy trinkets that make C++ programming happier~

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
/..............root directory
    cppu/......library header directory
    test/......unit tests directory
    LICENSE
    README.md
~~~

<a name="build"></a>
## Build Instructions

Currently, CPPU is header-only. Add the directory containing `cppu` to include
path and you are ready to go. To build the unit tests, you need to link with
gtest (`gtest` and `gtest_main`).

<a name="license"></a>
## License

[BSD 3-Clause License](https://opensource.org/licenses/BSD-3-Clause)
