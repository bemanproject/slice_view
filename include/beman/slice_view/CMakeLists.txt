# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

target_sources(
    beman.slice_view
    PUBLIC FILE_SET HEADERS FILES slice_view.hpp detail/concepts.hpp
)
