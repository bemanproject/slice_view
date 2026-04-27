# beman.slice_view: Slice Range Adaptor

<!--
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
-->

<!-- markdownlint-disable-next-line line-length -->
![Library Status](https://raw.githubusercontent.com/bemanproject/beman/refs/heads/main/images/badges/beman_badge-beman_library_under_development.svg) ![Continuous Integration Tests](https://github.com/bemanproject/slice_view/actions/workflows/ci_tests.yml/badge.svg) ![Lint Check (pre-commit)](https://github.com/bemanproject/slice_view/actions/workflows/pre-commit-check.yml/badge.svg) [![Coverage](https://coveralls.io/repos/github/bemanproject/slice_view/badge.svg?branch=main)](https://coveralls.io/github/bemanproject/slice_view?branch=main) ![Standard Target](https://github.com/bemanproject/beman/blob/main/images/badges/cpp29.svg) [![Compiler Explorer Example](https://img.shields.io/badge/Try%20it%20on%20Compiler%20Explorer-grey?logo=compilerexplorer&logoColor=67c52a)](https://godbolt.org/z/o3aYd7jzT)

`beman.slice_view` is a minimal C++ library conforming to [The Beman Standard](https://github.com/bemanproject/beman/blob/main/docs/beman_standard.md).

**Implements**: Slice Range Adaptor proposed in [Standard Library Concepts (P3216R0)](https://wg21.link/P3216R0).

**Status**: [Under development and not yet ready for production use.](https://github.com/bemanproject/beman/blob/main/docs/beman_library_maturity_model.md#under-development-and-not-yet-ready-for-production-use)

## License

`beman.slice_view` is licensed under the Apache License v2.0 with LLVM Exceptions.

## Usage

`slice` provides a means of extracting a contiguous subrange from a sequence by specifying a start and end index.

```cpp
#include <beman/slice_view/slice_view.hpp>
#include <iostream>
#include <string_view>

namespace exe = beman::slice_view;

int main()
{
    std::string_view text = "Hello, world!";
    auto s = text | exe::views::slice(7, 12);  // world

    for (char c : s)
        std::cout << c;

    std::cout << '\n';

    return 0;
}
```

Full runnable examples can be found in [`examples/`](examples/).

## Dependencies

### Build Environment

This project requires at least the following to build:

* A C++ compiler that conforms to the C++20 standard or greater
* CMake 3.30 or later
* (Test Only) GoogleTest

You can disable building tests by setting CMake option `BEMAN_SLICE_VIEW_BUILD_TESTS` to
`OFF` when configuring the project.

### Supported Platforms

| Compiler   | Version | C++ Standards | Standard Library  |
|------------|---------|---------------|-------------------|
| GCC        | 15-13   | C++26-C++20   | libstdc++         |
| GCC        | 12-11   | C++23, C++20  | libstdc++         |
| Clang      | 22-19   | C++26-C++20   | libstdc++, libc++ |
| Clang      | 18      | C++26-C++20   | libc++            |
| Clang      | 18      | C++23, C++20  | libstdc++         |
| Clang      | 17      | C++26-C++20   | libc++            |
| Clang      | 17      | C++20         | libstdc++         |
| AppleClang | latest  | C++26-C++20   | libc++            |
| MSVC       | latest  | C++23         | MSVC STL          |

## Development

See the [Contributing Guidelines](CONTRIBUTING.md).

## Integrate beman.slice_view into your project

### Build

You can build slice_view using a CMake workflow preset:

```bash
cmake --workflow --preset gcc-release
```

To list available workflow presets, you can invoke:

```bash
cmake --list-presets=workflow
```

For details on building beman.slice_view without using a CMake preset, refer to the
[Contributing Guidelines](CONTRIBUTING.md).

### Installation

To install beman.slice_view globally after building with the `gcc-release` preset, you can
run:

```bash
sudo cmake --install build/gcc-release
```

Alternatively, to install to a prefix, for example `/opt/beman`, you can run:

```bash
sudo cmake --install build/gcc-release --prefix /opt/beman
```

This will generate the following directory structure:

```txt
/opt/beman
├── include
│   └── beman
│       └── slice_view
│           ├── slice_view.hpp
│           └── detail
│               └── concepts.hpp
└── lib
    └── cmake
        └── beman.slice_view
            ├── beman.slice_view-config-version.cmake
            ├── beman.slice_view-config.cmake
            └── beman.slice_view-targets.cmake
```

### CMake Configuration

If you installed beman.slice_view to a prefix, you can specify that prefix to your CMake
project using `CMAKE_PREFIX_PATH`; for example, `-DCMAKE_PREFIX_PATH=/opt/beman`.

You need to bring in the `beman.slice_view` package to define the `beman::slice_view` CMake
target:

```cmake
find_package(beman.slice_view REQUIRED)
```

You will then need to add `beman::slice_view` to the link libraries of any libraries or
executables that include `beman.slice_view` headers.

```cmake
target_link_libraries(yourlib PUBLIC beman::slice_view)
```

### Using beman.slice_view

To use `beman.slice_view` in your C++ project,
include an appropriate `beman.slice_view` header from your source code.

```c++
#include <beman/slice_view/slice_view.hpp>
```

> [!NOTE]
>
> `beman.slice_view` headers are to be included with the `beman/slice_view/` prefix.
> Altering include search paths to spell the include target another way (e.g.
> `#include <slice_view.hpp>`) is unsupported.
