#pragma once

#include "traits_utils.h"

/// @brief Evaluate a ratio without casting its numerator and denominator.
/// @return The evaluated ratio (type: `intmax_t`).
template <typename Ratio>
constexpr auto ratio_evaluate_impl(std::true_type) noexcept { return Ratio::num / Ratio::den; }

/// @brief Evaluate a ratio casting its numerator to `double`.
/// @return The evaluated ratio (type: `double`).
template <typename Ratio>
constexpr auto ratio_evaluate_impl(std::false_type) noexcept { return static_cast<double>(Ratio::num) / Ratio::den; }

/// @brief Evaluate a ratio.
/// @tparam Ratio The ratio to evaluate.
/// @return The value of `Ratio::num / Ratio::den` (type: either `double` or `intmax_t`).
template <typename Ratio>
constexpr auto ratio_evaluate() noexcept { return ratio_evaluate_impl<Ratio>(traits::ratio_integer_t<Ratio>{}); }

/// @brief Get the unit prefix.
/// @tparam Ratio The ratio whose prefix to get.
template <typename Ratio>
std::string get_unit_prefix_string()
{
    using std::to_string;
    return "(" + to_string(Ratio::num) + "/" + to_string(Ratio::den) + ")";
}

/// @brief Get the unit prefix (`std::milli` specialization).
/// @tparam Ratio The ratio whose prefix to get.
/// @return "m".
template <>
std::string get_unit_prefix_string<std::milli>()
{
    return "m";
}

/// @brief Get the unit prefix (`std::centi` specialization).
/// @tparam Ratio The ratio whose prefix to get.
/// @return "c".
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
