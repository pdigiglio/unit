#pragma once

#include <ratio>
#include <type_traits>

namespace traits
{

    using unit_ratio = std::ratio<1, 1>;

    template <intmax_t Num, intmax_t Den>
    struct is_divisible final
    {
        using type = std::integral_constant<bool, Num == (Num / Den) * Den>;
    };

    template<intmax_t Num, intmax_t Den>
    using is_divisible_t = typename is_divisible<Num, Den>::type;

    template<intmax_t Num, intmax_t Den>
    constexpr auto is_divisible_v = is_divisible_t<Num, Den>::value;

    template <typename Ratio>
    struct ratio_integer
    {
        using type = is_divisible_t<Ratio::num, Ratio::den>;
    };

    template<typename Ratio>
    using ratio_integer_t = typename ratio_integer<Ratio>::type;

    template<typename Ratio>
    constexpr auto ratio_integer_v = ratio_integer_t<Ratio>::value;
}
