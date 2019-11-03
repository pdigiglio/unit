#pragma once

#include "traits_utils.h"

template <typename Ratio>
constexpr auto ratio_evaluate_impl(std::true_type) noexcept { return Ratio::num / Ratio::den; }

template <typename Ratio>
constexpr auto ratio_evaluate_impl(std::false_type) noexcept { return static_cast<double>(Ratio::num) / Ratio::den; }

template <typename Ratio>
constexpr auto ratio_evaluate() noexcept { return ratio_evaluate_impl<Ratio>(traits::ratio_integer_t<Ratio>{}); }

template <typename ToRatio, typename FromRatio = traits::unit_ratio>
constexpr auto conversion_factor() noexcept
{
    return ratio_evaluate<std::ratio_divide<FromRatio, ToRatio>>();
}

template <typename Ratio>
std::string get_unit_prefix_string()
{
    using std::to_string;
    return "(" + to_string(Ratio::num) + "/" + to_string(Ratio::den) + ")";
}

template <>
std::string get_unit_prefix_string<std::milli>()
{
    return "m";
}

template <>
std::string get_unit_prefix_string<std::centi>()
{
    return "c";
}

template <>
std::string get_unit_prefix_string<std::deci>()
{
    return "d";
}

template <>
std::string get_unit_prefix_string<std::ratio<1, 1>>()
{
    return "";
}

template <>
std::string get_unit_prefix_string<std::deca>()
{
    return "da";
}

template <>
std::string get_unit_prefix_string<std::hecto>()
{
    return "h";
}

template <>
std::string get_unit_prefix_string<std::kilo>()
{
    return "k";
}

template <>
std::string get_unit_prefix_string<std::mega>()
{
    return "M";
}
