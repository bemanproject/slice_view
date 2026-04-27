// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <beman/slice_view/slice_view.hpp>

#include <gtest/gtest.h>

#include <cassert>
#include <iostream>
#include <list>
#include <ranges>
#include <vector>

namespace exe = beman::slice_view;

TEST(slice_view_, test_simple_slice) {
    std::list l{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto      result = exe::views::slice(l, 5, 7);

    std::list expected{6, 7};
    assert(std::ranges::equal(result, expected));
}

TEST(slice_view_, test_pipe_syntax) {
    std::list l{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto      result = l | exe::views::slice(5, 7);

    std::list expected{6, 7};
    assert(std::ranges::equal(result, expected));
}

TEST(slice_view, test_empty_slice_start) {
    std::vector<int> v      = {1, 2, 3, 4, 5};
    auto             result = exe::views::slice(v, 0, 0);
    assert(std::ranges::empty(result));
}

TEST(slice_view, test_empty_slice_middle) {
    std::vector<int> v      = {1, 2, 3, 4, 5};
    auto             result = exe::views::slice(v, 3, 3);
    assert(std::ranges::empty(result));
}

TEST(slice_view, test_full_range) {
    std::vector<int> v      = {1, 2, 3, 4, 5};
    auto             result = exe::views::slice(v, 0, v.size());
    assert(std::ranges::equal(result, v));
}

TEST(slice_view, test_end_out_of_range) {
    std::vector<int> v        = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto             result   = exe::views::slice(v, 6, 11); // end > v.size
    std::vector<int> expected = {7, 8, 9};
    assert(std::ranges::equal(result, expected));
}

TEST(slice_view, test_start_out_of_range) {
    std::vector<int> v      = {1, 2, 3, 4, 5};
    auto             result = exe::views::slice(v, 6, 11); // start > v.size
    assert(std::ranges::empty(result));
}

TEST(slice_view, test_end_less_than_start) {
    std::vector<int> v      = {1, 2, 3, 4, 5};
    auto             result = exe::views::slice(v, 3, 1); // end < start
    assert(std::ranges::empty(result));
}

TEST(slice_view, test_const_correctness) {
    const std::vector<int> v{0, 1, 2, 3};

    auto s = exe::views::slice(v, 1, 3);

    assert(std::ranges::range<decltype(s)>);
    assert(std::ranges::range<const decltype(s)>);
}

TEST(slice_view, test_composibility) {
    const std::vector<int> v{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto                   result =
        v | std::views::transform([](int x) { return x * 2; }) | exe::views::slice(1, 4) | std::views::reverse;

    std::vector<int> expected = {6, 4, 2};
    assert(std::ranges::equal(result, expected));
}

// TEST(slice_view, test_fuzz_compare) {
//     for (int i = 0; i < 1000; ++i)
//     {
//         auto v = random_vector();
//         auto [a,b] = random_bounds();

//         auto s = exe::views::slice(v, a, b);

//         auto expected = v | std::views::drop(a) | std::views::take(b - a);

//         assert(equal(s, expected));
//     }
// }
