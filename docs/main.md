# `byp-cpp`

![test](https://img.shields.io/badge/Tests-Passing-32CD32)
[![clang-format](https://img.shields.io/badge/code%20style-clang--format-blue)](https://clang.llvm.org/docs/ClangFormat.html)
[![doxygen](https://img.shields.io/badge/documentation-doxygen-blue)](https://www.doxygen.nl/)


`byp-cpp` (Basic Yaml Parser for C++) is a parser for a
simplified [dialect](@ref BasicYAML) of the YAML markup
language.

The library is designed to be lightweight and easy to install,
manage and use, while providing a reasonably wide and robust
range of capabilities for users requiring basic YAML
functionalities (parsing of single values, vectors, and
tables). High performance is not one of the main goals of the
library, unless achievable without compromising simplicity of
design and maintainability.

We recommend the very complete and thorough
[yaml-cpp](https://github.com/jbeder/yaml-cpp) open source
library for additional functionality not included in our YAML
dialect.




## Dependencies and Setup

The library itself does not have any dependencies beyond the
C++ standard library and `g++` version 8 or higher (in general,
C++17-compatible). The command

```
$ make build
```

compiles the library statically as `libbyp-cpp.a` in the
`build/` directory.

The command

```
$ make clean
```

resets the build environment.

Use the `-std=c++17` flag when compiling the calling code with
`g++`.




## Usage

To parse files, create a `byp::parser` object, initialized with
the path of the file to parse, and call its `read()` method to
parse values associated to a specific key in the file.

```cpp
#include "byp.hpp"

byp::parser loader(<file path>);

// Assuming <key>: <value>, where <value>
// is compatible with <type>, is present in the parsed file
<type> val = loader.read<<type>>(<key>);
```

Parsable types are:

- Booleans (`bool`);
- Several signed integral types (`short`, `int`, `long`, `long
  long`);
- Several unsigned integral types (`unsigned short`, `unsigned
  int`, `unsigned long`, `unsigned long long`);
- Several floating-point types (`float`, `double`, `long
  double`);
- Strings (`std::string`);
- 1D vectors, `std::vector<T>`, where `T` is one of the types
  above (except `bool`).
- 2D vectors, `std::vector<std::vector<T>>`, where `T` is one
  of the types above (except `bool`).

The library also allows direct access to the `byp::convert()`
function, which attempts to convert its `std::string` argument
to an instance of the type of choice.

```cpp
#include <byp.hpp>

<type> val = byp::convert<<type>>(<string>);
```




## Testing

Tests can be ran launching the command

```
$ make test
```

When successfully completed, the output of this command should
have the form

```
<compilation logs>

Beginning testing

cd build/ ; ./01.test-basic
  <testing logs>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test completed successfully

...

All tests completed successfully
```




## Documentation

Building the documentation requires
[doxygen](https://www.doxygen.nl/). The command

```
$ make docs
```

re-generates the documentation in html format in the `html/`
directory. [index.html](html/index.html) is the corresponding
main page.

The [dialect](@ref BasicYAML) page contains information on the
specifications of the YAML dialect parsed by the library.
