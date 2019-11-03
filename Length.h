#pragma once

#include "ratio_utils.h"
#include "traits_utils.h"

#include <ostream>
#include <string>

namespace observable
{

template <typename Representation, typename Ratio = traits::unit_ratio>
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

    representation_type value() const
    {
        return this->Value_;
    }

private:
    Representation Value_;
};

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
constexpr auto length_cast(const Length<FromRepresentation, FromRatio>& from) noexcept
{
    auto v = conversion_factor<ToRatio, FromRatio>() * static_cast<ToRepresentation>(from.value());
    return Length<ToRepresentation, ToRatio>(v);
}

template <
    typename ToRatio,
    typename FromRepresentation,
    typename FromRatio
>
constexpr auto length_cast(const Length<FromRepresentation, FromRatio>& from) noexcept
{
    auto v = conversion_factor<ToRatio, FromRatio>() * from.value();
    return Length<decltype(v), ToRatio>(v);
}

}
