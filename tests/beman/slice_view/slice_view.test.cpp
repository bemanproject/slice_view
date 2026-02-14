// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <beman/slice_view/slice_view.hpp>

#include <gtest/gtest.h>

#include <list>
#include <sstream>

namespace exe = beman::slice_view;

TEST(slice_view_, simple_test_list) {
    std::list l{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto twos = exe::views::slice(l, 5, 7);

    std::list tmp{6, 7};

    for (int i: twos) {
        assert(i == tmp.front());
        tmp.pop_front();
    }
}
