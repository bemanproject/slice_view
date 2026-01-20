# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

find_package(GTest REQUIRED)

add_executable(beman.slice_view.tests.identity)
target_sources(beman.slice_view.tests.identity PRIVATE identity.test.cpp)
target_link_libraries(
    beman.slice_view.tests.identity
    PRIVATE beman::slice_view GTest::gtest GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(beman.slice_view.tests.identity)
