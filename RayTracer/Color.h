#pragma once
#include <array>
#include <algorithm>
template <typename T>
class Color {
private:
    std::array<T, 3> data;

public:
    constexpr Color() noexcept : data{ 0, 0, 0 } { }
    constexpr Color(T r = 0, T g = 0, T b = 0) noexcept : data{ r, g, b } { }

    constexpr friend std::ostream& operator<<(std::ostream& os, const Color& p) noexcept {
        os << "( " << p.data[0] << ", " << p.data[1] << ", " << p.data[2] << " )";
        return os;
    }

    constexpr Color<T> operator +(Color<T> const& rhs) const noexcept {
        return { data[0] + rhs.data[0], data[1] + rhs.data[1], data[2] + rhs.data[2] };
    }
    constexpr Color<T> operator -(Color<T> const& rhs) const noexcept {
        return { data[0] - rhs.data[0], data[1] - rhs.data[1], data[2] - rhs.data[2] };
    }

    constexpr Color<T> operator *(double scalar) const noexcept {
        return { data[0] * scalar, data[1] * scalar, data[2] * scalar };
    }

    constexpr Color<T> operator *(Color<T> const& rhs) const noexcept {
        return { data[0] * rhs.data[0], data[1] * rhs.data[1], data[2] * rhs.data[2] };
    }

    constexpr Color<T> clamped() const noexcept {
        return { std::clamp(data[0], 0, 255), std::clamp(data[1], 0, 255), std::clamp(data[2], 0, 255) };
    }

    constexpr auto operator<=>(Color<T> const&) const noexcept = default;

    inline static constexpr Color Black{ 0, 0, 0 };
    inline static constexpr Color White{ 255, 255, 255 };
    inline static constexpr Color Red{ 255, 0, 0 };
    inline static constexpr Color Lime{ 0, 255, 0 };
    inline static constexpr Color Blue{ 0, 0, 255 };
    inline static constexpr Color Yellow{ 255, 255, 0 };
    inline static constexpr Color Cyan{ 0, 255, 255 };
    inline static constexpr Color Magenta{ 255, 0, 255 };
    inline static constexpr Color Silver{ 192, 192, 192 };
    inline static constexpr Color Gray{ 128, 128, 128 };
    inline static constexpr Color Maroon{ 128, 0, 0 };
    inline static constexpr Color Olive{ 128, 128, 0 };
    inline static constexpr Color Green{ 0, 128, 0 };
    inline static constexpr Color Purple{ 128, 0, 128 };
    inline static constexpr Color Teal{ 0, 128, 128 };
    inline static constexpr Color Navy{ 0, 0, 128 };
};