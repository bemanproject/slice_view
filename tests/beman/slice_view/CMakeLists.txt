# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

find_package(GTest REQUIRED)

add_executable(beman.slice_view.tests.slice)
target_sources(beman.slice_view.tests.slice PRIVATE slice_view.test.cpp)
target_link_libraries(
    beman.slice_view.tests.slice
    PRIVATE beman::slice_view GTest::gtest GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(beman.slice_view.tests.slice)
