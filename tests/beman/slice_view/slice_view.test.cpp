// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <beman/slice_view/slice_view.hpp>

#include <gtest/gtest.h>

#include <algorithm>
#include <functional>

namespace exe = beman::slice_view;

TEST(slice_view_, simple_test) {
    auto ints = std::ranges::views::iota(0);
    auto fifties = exe::views::slice(ints, 50, 60);
    std::printf("{} ", fifties);  // prints [50, 51, 52, 53, 54, 55, 56, 57, 58, 59]
}
