# Vec
Vec is a basic C++ vector math library, implemented for fun and learning.

This library is not optimized for performance, and is not intended to compete with the plethora of
serious vector math libraries already available. This project is instead focused on providing a
simple, intuitive implementation of basic vector math capabilities that can be used to build games
and other 3D math applications. 

Vec is a header-only template library that can represent arbitrary vector sizes. The current
implementation heavily utilizes standard library algorithms to manipulate vector elements. This
approach was chosen purely to gain familiarity with applying these algorithms in an actual project.
In the future, attempts to improve performance may require moving in a different direction.

**Note:** This README is still under construction.

### Requirements / Dependencies

Vec is built using modern C++20 features. As of this time, it has only been tested with **GCC 
version 10.2.0**.

Unit tests for vec use [doctest](https://github.com/onqtam/doctest), which is included as a 
submodule in this repository. Be sure to update submodules after cloning this repo:
```bash
git submodule update --init
```