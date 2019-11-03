#include <iostream>

#include "Length.h"
#include "traits_utils.h"

////using unit_ratio = std::ratio<1, 1>;
////
////template <intmax_t Num, intmax_t Den>
////struct is_divisible final
////{
////    using type = std::integral_constant<bool, Num == (Num / Den) * Den>;
////};
////
////template<intmax_t Num, intmax_t Den>
////using is_divisible_t = typename is_divisible<Num, Den>::type;
////
////template<intmax_t Num, intmax_t Den>
////constexpr auto is_divisible_v = is_divisible_t<Num, Den>::value;
////
////template <typename Ratio>
////struct ratio_integer
////{
////    using type = is_divisible_t<Ratio::num, Ratio::den>;
////};
////
////template<typename Ratio>
////using ratio_integer_t = typename ratio_integer<Ratio>::type;
////
////template<typename Ratio>
////constexpr auto ratio_integer_v = ratio_integer_t<Ratio>::value;
//
//template <typename Ratio>
//constexpr auto ratio_evaluate_impl(std::true_type) noexcept { return Ratio::num / Ratio::den; }
//
//template <typename Ratio>
//constexpr auto ratio_evaluate_impl(std::false_type) noexcept { return static_cast<double>(Ratio::num) / Ratio::den; }
//
//template <typename Ratio>
//constexpr auto ratio_evaluate() noexcept { return ratio_evaluate_impl<Ratio>(ratio_integer_t<Ratio>{}); }
//
//template <typename ToRatio, typename FromRatio = unit_ratio>
//constexpr auto conversion_factor() noexcept
//{
//    return ratio_evaluate<std::ratio_divide<FromRatio, ToRatio>>();
//}
//
////template <typename Representation, typename Ratio = unit_ratio>
////class Length final
////{
////public:
////    using representation_type = Representation;
////
////    explicit Length(Representation value)
////        :
////            Value_(value)
////    { }
////
////    Length(const Length&) = default;
////    Length(Length&&) = default;
////
////    Length& operator=(const Length&) = default;
////    Length& operator=(Length&&) = default;
////
////    ~Length() = default;
////
////    Representation value() const
////    {
////        return this->Value_;
////    }
////
////private:
////    Representation Value_;
////};
//
//
//template <typename Ratio>
//std::string get_unit_prefix_string()
//{
//    using std::to_string;
//    return "(" + to_string(Ratio::num) + "/" + to_string(Ratio::den) + ")";
//}
//
//template <>
//std::string get_unit_prefix_string<std::ratio<1, 1>>()
//{
//    return "";
//}
//
//template <>
//std::string get_unit_prefix_string<std::deca>()
//{
//    return "da";
//}
//
//template <>
//std::string get_unit_prefix_string<std::hecto>()
//{
//    return "h";
//}
//
//template <>
//std::string get_unit_prefix_string<std::kilo>()
//{
//    return "k";
//}
//
////template <typename Representation, typename Ratio>
////std::string to_string(const Length<Representation, Ratio>& l)
////{
////    using std::to_string;
////    return to_string(l.value()) + " " + get_unit_prefix_string<Ratio>() + "m";
////}
////
////template <typename Representation, typename Ratio>
////std::ostream& operator<<(std::ostream& os, const Length<Representation, Ratio>& l)
////{
////    return os << to_string(l);
////}
//
//template <
//    typename ToRepresentation,
//    typename ToRatio,
//    typename FromRepresentation,
//    typename FromRatio
//>
//constexpr auto length_cast(const Length<FromRepresentation, FromRatio>& from) noexcept -> Length<ToRepresentation, ToRatio>
//{
//    auto v = conversion_factor<ToRatio, FromRatio>() * static_cast<ToRepresentation>(from.value());
//    return Length<ToRepresentation, ToRatio>(v);
//}
//
////template <
////    typename ToRatio,
////    typename FromRepresentation,
////    typename FromRatio
////>
////constexpr auto length_cast_impl(const Length<FromRepresentation, FromRatio>& from, std::true_type) noexcept
////{
////    using to_representation = (1 < 2) ? double : FromRepresentation;
////
////    auto v = conversion_factor<ToRatio, FromRatio>() * static_cast<to_representation>(from.value());
////    return Length<to_representation, ToRatio>(v);
////}
////
//
////template <typename FromRepresentation>
////constexpr auto to_representation_cast(const FromRepresentation v, std::true_type) noexcept { return static_cast<double>(v); }
////
////template <typename FromRepresentation>
////constexpr auto to_representation_cast(const FromRepresentation v, std::false_type) noexcept { return v; }
//
//template <
//    typename ToRatio,
//    typename FromRepresentation,
//    typename FromRatio
//>
//constexpr auto length_cast(const Length<FromRepresentation, FromRatio>& from) noexcept
//{
//    //using to_representation = FromRepresentation;
//    //auto v = to_representation(from.value(), std::ratio_greater<ToRatio, FromRatio>);
//    auto v = conversion_factor<ToRatio, FromRatio>() * from.value();
//    return Length<decltype(v), ToRatio>(v);
//}

int main()
{
    const observable::Length<int, std::kilo> l(35);

    std::cout << "-- Casts that auto-select representation type \n";
    std::cout << l << " == " << observable::length_cast<std::milli>(l) << "\n";
    std::cout << l << " == " << observable::length_cast<std::centi>(l) << "\n";
    std::cout << l << " == " << observable::length_cast<std::deci>(l) << "\n";
    std::cout << l << " == " << observable::length_cast<traits::unit_ratio>(l) << "\n";
    std::cout << l << " == " << observable::length_cast<std::ratio_multiply<std::deca,  traits::unit_ratio>>(l) << "\n";
    std::cout << l << " == " << observable::length_cast<std::ratio_multiply<std::hecto, traits::unit_ratio>>(l) << "\n";
    std::cout << l << " == " << observable::length_cast<std::kilo>(l) << "\n";
    std::cout << l << " == " << observable::length_cast<std::ratio_multiply<std::deca,  std::kilo>>(l) << "\n";
    std::cout << l << " == " << observable::length_cast<std::ratio_multiply<std::hecto, std::kilo>>(l) << "\n";
    std::cout << l << " == " << observable::length_cast<std::mega>(l) << "\n";

    std::cout << "-- Casts with explicit representation type \n";
    std::cout << l << " == " << observable::length_cast<float, std::milli>(l) << "\n";
    std::cout << l << " == " << observable::length_cast<float, std::centi>(l) << "\n";
    std::cout << l << " == " << observable::length_cast<float, std::deci>(l) << "\n";
    std::cout << l << " == " << observable::length_cast<float, traits::unit_ratio>(l) << "\n";
    std::cout << l << " == " << observable::length_cast<float, std::ratio_multiply<std::deca,  traits::unit_ratio>>(l) << "\n";
    std::cout << l << " == " << observable::length_cast<float, std::ratio_multiply<std::hecto, traits::unit_ratio>>(l) << "\n";
    std::cout << l << " == " << observable::length_cast<float, std::kilo>(l) << "\n";
    std::cout << l << " == " << observable::length_cast<float, std::ratio_multiply<std::deca,  std::kilo>>(l) << "\n";
    std::cout << l << " == " << observable::length_cast<float, std::ratio_multiply<std::hecto, std::kilo>>(l) << "\n";
    std::cout << l << " == " << observable::length_cast<float, std::mega>(l) << "\n";

    std::cout << "-- Compile-time divisibility checks\n";
    std::cout << "is_divisible<[num=]2, [den=]3> ? " << traits::is_divisible_v<2, 3> << "\n";
    std::cout << "is_divisible<[num=]3, [den=]3> ? " << traits::is_divisible_v<3, 3> << "\n";
    std::cout << "is_divisible<[num=]7, [den=]3> ? " << traits::is_divisible_v<7, 3> << "\n";
    std::cout << "is_divisible<[num=]9, [den=]3> ? " << traits::is_divisible_v<9, 3> << "\n";

    return 0;
}
