#pragma once
#include <array>
#include <iostream>
#include <type_traits>

template < template <typename...> class base, typename derived>
struct is_base_of_template_impl
{
    template<typename... Ts>
    static constexpr std::true_type  test(const base<Ts...>*);
    static constexpr std::false_type test(...);
    using type = decltype(test(std::declval<derived*>()));
};

template < template <typename...> class base, typename derived>
using is_base_of_template = typename is_base_of_template_impl<base, derived>::type;

template <typename T>
concept Scalar = std::is_scalar_v<T>;

template <typename T> 
struct Tuple {
    std::array<T, 4> data{};

    constexpr Tuple() = default;
    constexpr Tuple(T x, T y, T z, T w) noexcept : data{ x, y, z, w } { }

    constexpr auto operator<=>(Tuple<T> const&) const noexcept = default;
    constexpr T const& operator[](int index) const { return data[index]; }


    constexpr Tuple<T> operator +(Tuple<T> const& rhs) const noexcept {
        return { data[0] + rhs.data[0], data[1] + rhs.data[1], data[2] + rhs.data[2], data[3] + rhs.data[3] };
    }
    constexpr Tuple<T> operator -(Tuple<T> const& rhs) const noexcept {
        return { data[0] - rhs.data[0], data[1] - rhs.data[1], data[2] - rhs.data[2], data[3] - rhs.data[3] };
    }
    constexpr Tuple<T> operator -() const noexcept {
        return { -data[0], -data[1], -data[2], -data[3] };
    }

    template <Scalar S>
    constexpr Tuple<std::common_type_t<T, S>> operator *(S scalar) const noexcept {
        return { data[0] * scalar, data[1] * scalar, data[2] * scalar, data[3] * scalar };
    }
    template <Scalar S>
    constexpr Tuple<std::common_type_t<T, S>> operator /(S scalar) const noexcept {
        return { data[0] / scalar, data[1] / scalar, data[2] / scalar, data[3] / scalar };
    }

    constexpr Tuple<T> abs() const noexcept {
        return { std::abs(data[0]), std::abs(data[1]), std::abs(data[2]), std::abs(data[3]) };
    }
};

template <typename T>
struct Vector : public Tuple<T> {
    using Tuple<T>::data;

	constexpr Vector() noexcept : Tuple<T>( ) { }
	constexpr Vector(Tuple<T> t) noexcept : Tuple<T>( t ) { }
	constexpr Vector(T x, T y, T z, T w = 0) noexcept : Tuple<T>( x, y, z, w ) { }


    constexpr T magnitude() const noexcept {
        return std::sqrt(data[0] * data[0] + data[1] * data[1] + data[2] * data[2] + data[3] * data[3]);
    }
    constexpr Vector normalized() const noexcept {
        return *this / magnitude();
    }

    constexpr auto dot(Vector<T> const& b) const noexcept {
        return data[0] * b[0] + data[1] * b[1] + data[2] * b[2] + data[3] * b[3];
    }
    constexpr Vector<T> cross(Vector<T> const& b) const noexcept {
        return {
            data[1] * b[2] - data[2] * b[1],
            data[2] * b[0] - data[0] * b[2],
            data[0] * b[1] - data[1] * b[0]
        };
    }

    constexpr Vector<T> reflect(Vector<T> const& norm) const noexcept {
        return *this - norm * (2 * dot(norm));
    }
};


template <typename T>
struct Point : Tuple<T> {
    using Tuple<T>::data;

    constexpr Point() noexcept : Tuple<T>(0, 0, 0, 1) { }
    constexpr Point(Tuple<T> t) noexcept : Tuple<T>(t) { }
    constexpr Point(T x, T y, T z, T w = 1) noexcept : Tuple<T>( x, y, z, w ) { }

    constexpr Vector<T> operator- (Point<T> const& rhs) const noexcept {
        return { data[0] - rhs.data[0], data[1] - rhs.data[1], data[2] - rhs.data[2], data[3] - rhs.data[3] };
    }
    constexpr Vector<T> operator+ (Point<T> const& rhs) const noexcept {
        return { data[0] + rhs.data[0], data[1] + rhs.data[1], data[2] + rhs.data[2], data[3] + rhs.data[3] };
    }

    constexpr Point<T> operator +(Vector<T> const& rhs) const noexcept {
        return { data[0] + rhs.data[0], data[1] + rhs.data[1], data[2] + rhs.data[2], data[3] + rhs.data[3] };
    }
    constexpr Point<T> operator -(Vector<T> const& rhs) const noexcept {
        return { data[0] - rhs.data[0], data[1] - rhs.data[1], data[2] - rhs.data[2], data[3] - rhs.data[3] };
    }
};


#include <algorithm>
template <typename T>
class Color : public Tuple<T>{
public:
    using Tuple<T>::data;

    constexpr Color() noexcept : Tuple<T>() { }
    constexpr Color(Tuple<T> t) noexcept : Tuple<T>(t) { }
    constexpr Color(T r, T g, T b) noexcept : Tuple<T>(r, g, b, 0) { }

    inline constexpr friend std::ostream& operator<<(std::ostream& os, const Color& p) noexcept {
        os << "( " << p.data[0] << ", " << p.data[1] << ", " << p.data[2] << " )";
        return os;
    }

    constexpr Color operator *(Color const& rhs) const noexcept {
        return { data[0] * rhs.data[0], data[1] * rhs.data[1], data[2] * rhs.data[2] };
    }
    template <Scalar S>
    constexpr Color<std::common_type_t<T, S>> operator *(S scalar) const noexcept {
        return { data[0] * scalar, data[1] * scalar, data[2] * scalar };
    }

    constexpr T red()   const noexcept { return data[0]; }
    constexpr T green() const noexcept { return data[1]; }
    constexpr T blue()  const noexcept { return data[2]; }

    inline constexpr Color clamped() const noexcept {
        return { std::clamp(data[0], 0, 255), std::clamp(data[1], 0, 255), std::clamp(data[2], 0, 255) };
    }
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

template <typename T>
concept TupleLike = is_base_of_template<Tuple, T>::value;


template<TupleLike T>
constexpr std::ostream& operator<<(std::ostream& os, const T& t) noexcept {
    os << "( " << t.data[0] << ", " << t.data[1] << ", " << t.data[2] << ", " << t.data[3] << " )";
    return os;
}

template <typename T>
inline constexpr bool operator==(Color<T> const& lhs, Color<T> const& rhs) {
    if (&lhs == &rhs) return true;
    
    constexpr auto eps = std::numeric_limits<T>::epsilon();
    return ( std::abs(lhs[0] - rhs[0]) <= eps &&
             std::abs(lhs[1] - rhs[1]) <= eps &&
             std::abs(lhs[2] - rhs[2]) <= eps &&
             std::abs(lhs[3] - rhs[3]) <= eps);
}