// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#ifndef BEMAN_SLICE_VIEW_DETAIL_CONCEPT_HPP
#define BEMAN_SLICE_VIEW_DETAIL_CONCEPT_HPP

#include <concepts>
#include <iterator>
#include <ranges>
#include <type_traits>

namespace beman::slice_view::views {
    namespace detail {

        // trait templates
        template<template<typename...> class Template, typename T>
        struct is_specialization_of : std::false_type {};

        template<template<typename...> class Template, typename... Args>
        struct is_specialization_of<Template, Template<Args...>>
            : std::true_type {};

        // is empty
        template <typename T>
        concept is_empty_view =
        is_specialization_of<
            std::ranges::empty_view,
            std::remove_cvref_t<T>
        >::value;

        // is repeat
        template <typename T>
        concept is_repeat_view =
        is_specialization_of<
            std::ranges::repeat_view,
            std::remove_cvref_t<T>
        >::value;

        // is iota
        template <typename T>
        concept is_iota_view =
        is_specialization_of<
            std::ranges::iota_view,
            std::remove_cvref_t<T>
        >::value;

        // is subrange
        template <typename T>
        concept is_subrange =
        is_specialization_of<
            std::ranges::subrange,
            std::remove_cvref_t<T>
        >::value;

        // is basic string view
        template <typename T>
        concept is_subrange =
        is_specialization_of<
            std::basic_string_view,
            std::remove_cvref_t<T>
        >::value;

        // is span
        template <typename T>
        concept is_subrange =
        is_specialization_of<
            std::span,
            std::remove_cvref_t<T>
        >::value;

    } // namespace detail
}

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

#endif // BEMAN_SLICE_VIEW_DETAIL_CONCEPT_HPP