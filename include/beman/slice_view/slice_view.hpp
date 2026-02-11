// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#ifndef BEMAN_SLICE_VIEW_HPP
#define BEMAN_SLICE_VIEW_HPP

#include <ranges>
#include <iterator>
#include <concepts>

namespace beman::slice_view {

namespace detail {
    template <typename r>
    concept simple_view_ref =
                std::same_as<std::ranges::iterator_t<T>,
                std::ranges::iterator_t<const T>> &&
                std::same_as<std::ranges::sentinel_t<T>,
                std::ranges::sentinel_t<const T>>;

    template <typename rng>
    concept simple_view =
                std::ranges::view<rng> &&
                std::ranges::range<const rng> &&
                simple_view_ref<rng>;

} // namespace detail

}

#endif // BEMAN_SLICE_VIEW_HPP