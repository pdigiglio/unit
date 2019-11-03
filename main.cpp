#include <iostream>
#include <ratio>
#include <string>

using unit_ratio = std::ratio<1, 1>;

template <typename Ratio>
constexpr auto ratio_evaluate() noexcept { return static_cast<double>(Ratio::num) / Ratio::den; }

template <typename ToRatio, typename FromRatio = unit_ratio>
constexpr double conversion_factor() noexcept
{
    return ratio_evaluate<std::ratio_divide<FromRatio, ToRatio>>();
}

template <typename Representation, typename Ratio = unit_ratio>
class Length final
{
public:
    using representation_type = Representation;

    explicit Length(Representation value)
        :
            Value_(value)
    { }

    Length(const Length&) = default;
    Length(Length&&) = default;

    Length& operator=(const Length&) = default;
    Length& operator=(Length&&) = default;

    ~Length() = default;

    Representation value() const
    {
        return this->Value_;
    }

private:
    Representation Value_;
};


template <typename Ratio>
std::string get_unit_prefix_string()
{
    using std::to_string;
    return "(" + to_string(Ratio::num) + "/" + to_string(Ratio::den) + ")";
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

template <typename Representation, typename Ratio>
std::string to_string(const Length<Representation, Ratio>& l)
{
    using std::to_string;
    return to_string(l.value()) + " " + get_unit_prefix_string<Ratio>() + "m";
}

template <typename Representation, typename Ratio>
std::ostream& operator<<(std::ostream& os, const Length<Representation, Ratio>& l)
{
    return os << to_string(l);
}

template <
    typename ToRepresentation,
    typename ToRatio,
    typename FromRepresentation,
    typename FromRatio
>
constexpr auto length_cast(const Length<FromRepresentation, FromRatio>& from) noexcept -> Length<ToRepresentation, ToRatio>
{
    auto v = conversion_factor<ToRatio, FromRatio>() * static_cast<ToRepresentation>(from.value());
    return Length<ToRepresentation, ToRatio>(v);
}

int main()
{

    const Length<int, std::kilo> l(35);

    std::cout << l << " == " << length_cast<double,                                unit_ratio >(l) << "\n";
    std::cout << l << " == " << length_cast<double, std::ratio_multiply<std::deca, unit_ratio>>(l) << "\n";

    return 0;
}
