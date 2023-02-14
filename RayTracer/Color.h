#pragma once
#include <array>
#include <algorithm>

template <typename T>
class Color {
private:
    std::array<T, 3> data;

public:
    using namespace Constants;

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
};





namespace Constants {
    template <typename T> inline static constexpr Color<T> Black{ 0, 0, 0 };
    template <typename T> inline static constexpr Color<T> White{ 255, 255, 255 };
    template <typename T> inline static constexpr Color<T> Red{ 255, 0, 0 };
    template <typename T> inline static constexpr Color<T> Lime{ 0, 255, 0 };
    template <typename T> inline static constexpr Color<T> Blue{ 0, 0, 255 };
    template <typename T> inline static constexpr Color<T> Yellow{ 255, 255, 0 };
    template <typename T> inline static constexpr Color<T> Cyan{ 0, 255, 255 };
    template <typename T> inline static constexpr Color<T> Magenta{ 255, 0, 255 };
    template <typename T> inline static constexpr Color<T> Silver{ 192, 192, 192 };
    template <typename T> inline static constexpr Color<T> Gray{ 128, 128, 128 };
    template <typename T> inline static constexpr Color<T> Maroon{ 128, 0, 0 };
    template <typename T> inline static constexpr Color<T> Olive{ 128, 128, 0 };
    template <typename T> inline static constexpr Color<T> Green{ 0, 128, 0 };
    template <typename T> inline static constexpr Color<T> Purple{ 128, 0, 128 };
    template <typename T> inline static constexpr Color<T> Teal{ 0, 128, 128 };
    template <typename T> inline static constexpr Color<T> Navy{ 0, 0, 128 };
}