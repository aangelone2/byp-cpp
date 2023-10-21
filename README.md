# `byp-cpp`

![test](https://img.shields.io/badge/Tests-Passing-32CD32)
[![clang-format](https://img.shields.io/badge/code%20style-clang--format-blue)](https://clang.llvm.org/docs/ClangFormat.html)
[![doxygen](https://img.shields.io/badge/documentation-doxygen-blue)](https://www.doxygen.nl/)


`byp-cpp` (Basic Yaml Parser for C++) is a parser for a
simplified dialect of the YAML markup language.

The library is designed to be easy to install, to manage and to
use, while providing a reasonably wide and robust range of
capabilities for users requiring basic YAML functionalities
(parsing of single values, vectors and tables).

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

compiles the library statically as `libbypcpp.a` in the
`build/` directory. Test can be ran by launching the command

```
$ make test
```




## Usage

To parse files, create a `byp_loader` object, initialized with
the path of the file to parse, and call its `read()` method to
parse values associated to a specific key in the file.

```cpp
#include "byp.hpp"

byp_loader loader(<file path>);

// Assuming <key>: <value>, where <value>
// is compatible with <type>, is present in the parsed file
<type> val = loader.read<<type>>(<key>);
```

Parsable types are:

- Several builtin C++ types (`bool`, `int`, `size_t`, `double`,
  `std::string`).
- 1D vectors, `std::vector<T>`, where `T` is one of the types
  above (except `bool`).
- 2D vectors, `std::vector<std::vector<T>>`, where `T` is one
  of the types above (except `bool`).




## Documentation

The command

```
$ make docs
```

re-generates the documentation in html format in the `html/`
directory. [index.html](html/index.html) is the corresponding
main page.




## Todo
- [ ] Manage duplicate keys
- [ ] Replace inout parameters in `convert()` with return-type
  templates
