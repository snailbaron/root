#pragma once

#include <utility>

template <class U, class V>
struct sum_type {
    using type = decltype(std::declval<U>() + std::declval<V>());
};
template <class U, class V>
using sum_type_t = typename sum_type<U, V>::type;

template <class U, class V>
struct diff_type {
    using type = decltype(std::declval<U>() - std::declval<V>());
};
template <class U, class V>
using diff_type_t = typename diff_type<U, V>::type;

template <class U, class V>
struct mul_type {
    using type = decltype(std::declval<U>() * std::declval<V>());
};
template <class U, class V>
using mul_type_t = typename mul_type<U, V>::type;

template <class U, class V>
struct div_type {
    using type = decltype(std::declval<U>() / std::declval<V>());
};
template <class U, class V>
using div_type_t = typename div_type<U, V>::type;

