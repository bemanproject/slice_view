# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

set(ALL_EXAMPLES slice_view_direct_usage)

message("Examples to be built: ${ALL_EXAMPLES}")

foreach(example ${ALL_EXAMPLES})
    add_executable(beman.slice_view.examples.${example})
    target_sources(beman.slice_view.examples.${example} PRIVATE ${example}.cpp)
    target_link_libraries(
        beman.slice_view.examples.${example}
        PRIVATE beman::slice_view
    )
endforeach()
