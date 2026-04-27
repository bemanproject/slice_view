// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <beman/slice_view/slice_view.hpp>
#include <iostream>
#include <string_view>

namespace exe = beman::slice_view;

int main() {
    std::string_view text = "Hello, world!";
    auto             s    = text | exe::views::slice(7, 12); // world

    for (char c : s)
        std::cout << c;

    std::cout << '\n';

    return 0;
}
