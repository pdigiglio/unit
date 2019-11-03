#include <iostream>

#include "Length.h"
#include "traits_utils.h"

int main()
{
    const auto l = observable::make_length<std::kilo>(35);

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
