#pragma once

#include "ratio_utils.h"
#include "traits_utils.h"

#include <ostream>
#include <string>

namespace observable
{

/// @brief A length observable.
/// @tparam Representation The underlying length type.
/// @tparam Ratio The ratio (w.r.t. meter).
template <typename Representation, typename Ratio = traits::unit_ratio>
class Length final
{
public:
    using representation_type = Representation;

    /// @brief Constructor.
    /// @param value The length value.
    constexpr explicit Length(Representation value) noexcept 
        :
            Value_(value)
    { }

    /// @brief Copy constructor.
    Length(const Length&) = default;
    /// @brief Move constructor.
    Length(Length&&) = default;

    /// @brief Copy assignment operator.
    Length& operator=(const Length&) = default;
    /// @brief Copy assignment operator.
    Length& operator=(Length&&) = default;

    /// @brief Destructor.
    ~Length() = default;

    /// @brief Get the underlying value.
    constexpr representation_type value() const
    {
        return this->Value_;
    }

private:
    /// @brief the length value.
    Representation Value_;
};

template <typename Ratio, typename Representation>
constexpr auto make_length(Representation value) noexcept 
{
    return Length<Representation, Ratio>(value);
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

template <typename ToRatio, typename FromRatio = traits::unit_ratio>
constexpr auto conversion_factor() noexcept
{
    return ratio_evaluate<std::ratio_divide<FromRatio, ToRatio>>();
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

/// @brief Cast a length to a different unit of measure.
/// @param from The length to cast from.
/// @tparam ToRatio The ratio to cast `from` to.
/// @tparam FromRepresentation The representation type of `from`.
/// @tparam FromRatio The ratio type of `from`.
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
