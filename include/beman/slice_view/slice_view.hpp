// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#ifndef BEMAN_SLICE_VIEW_HPP
#define BEMAN_SLICE_VIEW_HPP

#include <beman/slice_view/detail/concepts.hpp>
#include <ranges>
#include <iterator>
#include <concepts>

namespace beman::slice_view {
template <std::ranges::view V>
class slice_view 
    : public std::ranges::view_interface<slice_view<V>> {

    V base_ = V();
    std::ranges::range_difference_t<V> from_ = 0;
    std::ranges::range_difference_t<V> to_ = 0;

    class sentinel {
        private:
            std::ranges::sentinel_t<V> end_ = std::ranges::end(base_);
        public:
            sentinel() = default;
            constexpr explicit sentinel(std::ranges::sentinel_t<V> end) : end_(end) { }

            constexpr std::ranges::sentinel_t<V> base() const {
                return end_;
            }

            friend constexpr bool operator==(const std::counted_iterator<std::ranges::iterator_t<V>>& x, const sentinel& y) {
                return x.count() == 0 || x.base() == y.end_;
            }
    };

    public:
        /* Default constructor */
        slice_view()
            requires std::default_initializable<V> 
        = default;

        /**
         * Construct from `base`, `from`, and `to`.
         */
        constexpr explicit slice_view(
            V base, 
            std::ranges::range_difference_t<V> from, 
            std::ranges::range_difference_t<V> to)
        : base_(std::move(base)), from_(from), to_(to) { }
        
        /**
         * Returns a constant reference to underlying view, copy the base.
         */
        constexpr V base() const&
            requires std::copy_constructible<V>
        {
            return base_;
        }

        /**
         * Returns an rvalue reference to the underlying view, move the base.
         */
        constexpr V base() && {
            return std::move(base_);
        }

        /**
         * Returns an iterator for the beginning of the view.
         */
        constexpr auto begin()
        requires(!(detail::simple_view<V> 
            && std::ranges::random_access_range<const V> 
            && std::ranges::sized_range<const V>))
        {
            if constexpr (std::ranges::sized_range<V>) {
                if constexpr (std::ranges::random_access_range<V>)
                    return std::ranges::begin(base_) + std::min(from_, std::ranges::distance(base_));
                else {
                    auto n = std::ranges::distance(base_);
                    return counted_iterator(std::ranges::next(std::ranges::begin(base_), std::min(from_, n)),
                                            std::min(to_, n) - std::min(from_, n));
                }
            } else if constexpr (std::sized_sentinel_for<std::ranges::sentinel_t<V>, 
            std::ranges::iterator_t<V>>) {
                auto it = std::ranges::begin(base_);
                auto n = std::ranges::end(base_) - it;
                return counted_iterator(std::ranges::next(std::move(it), std::min(from_, n)),
                                        std::min(to_, n) - std::min(from_, n));
            } else {
                return counted_iterator(std::ranges::next(std::ranges::begin(base_), 
                                            from_, std::ranges::end(base_)), 
                                            to_ - from_);
            }
        }

        /**
         * Returns a `const` iterator for the beginning of the view.
         */
        constexpr auto
        begin() const
            requires std::ranges::random_access_range<const V> 
                && std::ranges::sized_range<const V>
        {
            return std::ranges::begin(base_) + std::min(from_, std::ranges::distance(base_));
        }

        /**
         * Returns a sentinel for the end of the view.
         */
        constexpr auto end()
            requires(!(detail::simple_view<V> 
                && std::ranges::random_access_range<const V> 
                && std::ranges::sized_range<const V>))
        {
            if constexpr (std::ranges::sized_range<V>) {
                if constexpr (std::ranges::random_access_range<V>)
                    return std::ranges::begin(base_) + std::min(to_, std::ranges::distance(base_));
                else
                    return std::default_sentinel;
            } else if constexpr (std::sized_sentinel_for<
                    std::ranges::sentinel_t<V>,
                    std::ranges::iterator_t<V>
                >)
                return std::default_sentinel;
            else
                return sentinel(std::ranges::end(base_));
        }

        /**
         * Returns a `const` iterator for the end of the view.
         */
        constexpr auto end() const
            requires(std::ranges::random_access_range<const V> 
                && std::ranges::sized_range<const V>)
        {
            return std::ranges::begin(base_) + std::min(to_, std::ranges::distance(base_));
        }

        /**
         * Returns the number of elements in view
         */
        constexpr auto size()
            requires std::ranges::sized_range<V>
        {
            auto n = std::ranges::distance(base_);
            return static_cast<std::ranges::range_size_t<V>>(std::min(to_, n) - std::min(from_, n));
        }

        /**
         * Returns the number of elements in view
         */
        constexpr auto size() const
            requires std::ranges::sized_range<const V>
        {
            auto n = std::ranges::distance(base_);
            return static_cast<std::ranges::range_size_t<const V>>(std::min(to_, n) - std::min(from_, n));
        }
};

/**
 * Deduction guide for constructing a slice_view from a `viewable_range`
 */
template<class R>
slice_view(R&&, std::ranges::range_difference_t<R>, std::ranges::range_difference_t<R>) -> slice_view<std::ranges::views::all_t<R> >;

namespace views {
    namespace detail {
        struct slice_impl : std::ranges::range_adaptor_closure<slice_impl> {
            template<std::ranges::viewable_range R, class D = std::ranges::range_difference_t<R>>
            requires requires { slice_view(std::declval<R>(), std::declval<D>(), std::declval<D>()); }
            constexpr auto
            operator()(R&& r, std::type_identity_t<D> n, std::type_identity_t<D> m) const {
                using T = std::remove_cvref_t<R>;
                if constexpr (is_empty_view<T> || is_repeat_view<T> || is_span_v<T> || is_basic_string_view<T>)
                    return std::forward<R>(r) | std::ranges::views::drop(n) | std::ranges::views::take(m - n);
                else if constexpr ((is_iota_view<T> || is_subrange_v<T>) &&
                                std::ranges::random_access_range<T> && std::ranges::sized_range<T>)
                    return std::forward<R>(r) | std::ranges::views::drop(n) | std::ranges::views::take(m - n);
                else
                    return slice_view(std::forward<R>(r), n, m);
            }
        };
    }

    inline constexpr detail::slice_impl slice;
}

}

#endif // BEMAN_SLICE_VIEW_HPP