# Vec
**Vec is a basic C++20 vector math library, implemented for fun and for learning.**

![CMake build and test status](https://github.com/embeddr/vec/actions/workflows/cmake.yml/badge.svg)

### Summary
Vec is a header-only class template library that provides 2D, 3D, and 4D vectors and matrices, as
well as typical operations associated with each. Higher dimensions and non-square matrices are
beyond the intended scope of this project and are not supported. Vectors and matrices provided by
Vec can be templated on `float`, `double`, and `long double` types. Support for a custom fixed-point
arithmetic type may be added in the future.

While Vec was designed with reasonable practices and efficiency in mind, it is not optimized for
performance, nor is it intended to compete with the plethora of serious, general-purpose linear
algebra libraries freely available elsewhere. It does not utilize features like SIMD or expression 
templates to maximize performance. This project is instead focused on providing a simple, intuitive 
implementation of basic vector math capabilities that can be used to build games and other
applications involving 3D math.

### Goals
Some of my personal goals for this project are:
* **Learn about 3D math fundamentals**. Get more comfortable with vectors, matrices,
  transformations, homogeneous coordinates, quaternions, etc. in a programming context.
* **Explore various features of modern C++**. I've been restricted to an old C++11 toolchain at 
  my job, so I want to learn about some of the newer features of C++14/17/20 via this project.
* **Utilize the standard library where possible**. I was a C programmer long before I started 
  writing C++, and one area of C++ I've been slow to adopt is the standard library's numerous
  containers and algorithms. I make extra effort to use them here, purely for practice.
* **Attempt to provide a fully `constexpr` implementation**. C++14 greatly expanded the
  usability of `constexpr`, and C++20 provides `constexpr` standard algorithms. Surprisingly,
  the last missing piece is basic math operations like `sqrt()`. I'm providing `constexpr`
  implementations for some of these operations, though some are still missing.

### Requirements / Dependencies

Vec is built using modern C++ features up to and including several provided by C++20. As of this 
time, this library has only been tested with **GCC version 10**, though comparably recent 
versions of Clang and MSVC are hopefully compatible.

Unit tests for Vec use [doctest](https://github.com/onqtam/doctest), which is included as a 
submodule in this repository. If you want to run unit tests locally, be sure to update submodules 
after cloning this repo:
```bash
git submodule update --init
```

### Examples
See the included [target hit detection example](examples/target_hit_detection.cpp) for a
demonstration of basic vector arithmetic. Additional examples may be added in the future. I've also
used this library in a [basic raytracer application](https://github.com/embeddr/raytracer-cpp).

### Known Limitations
* Cannot generate `constexpr` rotation matrices due to lack of `constexpr`implementations of basic
  trigonometric functions like `sin()` and `cos()`. May implement these (or pull in a third-party
  implementation) in the future, as this isn't expected in standard C++ until C++23.