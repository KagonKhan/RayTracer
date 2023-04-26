#pragma once
#include "Color.h"
#include "Matrix.h"
#include "Objects.h"

template <typename T>
struct Pattern {
    Color<T> a, b;
    Matrix<T, 4> Transformation{ I<T> };

    constexpr Color<T> Get(Point<T> p) const noexcept {};

    static Color<T> GetOnObject(Point<T> p, HitObject<T> obj) {
        Point<T> obj_p = obj.Transformation.Inversed() * p;
        Point<T> pat_p = this.Transformation.Inversed() * obj_p;

        return Get(pat_p);
    }
};


template <typename T>
struct Material {
    T ambient{ 0.1 }, diffuse{ 0.9 }, specular{ 0.9 }, shininess{ 200 };
    Color<T> color{ 1, 1, 1 };
    std::optional<Pattern<T>> pattern{ std::nullopt };

    T reflective, transparency{ 0.0 }, refraction{ 1.0 };

    constexpr Material() noexcept = default;

    constexpr Material(T amb, T dif, T spe, T shi, Color<T> col, T reflect = 0.0, T trans = 0.0, T refr = 1.0) noexcept
        : ambient(amb), diffuse(dif), specular(spe), shininess(shi), color(col), pattern(std::nullopt), reflective(reflect), transparency(trans), refraction(refr) {
    }

    static constexpr Material Glass() const noexcept {
        Material<T> material;
        material.transparency = 1.0;
        material.refraction = 1.5;
        return material;
    }
};


template <typename T>
class TestPattern : public Pattern<T> {
public:
    constexpr TestPattern() noexcept = default;

    constexpr Color<T> Get(Point<T> point) const noexcept {
        return Color(point.X, point.Y, point.Z);
    }
};


template <typename T>
class SolidColorPattern : public Pattern<T> {
public:
    constexpr Color<T> Get(Point<T> point) const noexcept {
        return color;
    }

    Color<T> color;

    inline constexpr SolidColorPattern(Color c) noexcept {
        color = c;
    }
    inline constexpr SolidColorPattern(double r, double g, double b) noexcept {
        color = Color(r, g, b);
    }

};


template <typename T>
class StripePattern : public Pattern<T> {
public:
    public StripePattern(Color<T> a, Color<T> b) {
        this.a = a;
        this.b = b;
    }

    inline constexpr Color<T> Get(Point<T> point) const noexcept {
        Point tp = this.Transformation.Inversed() * point;
        return std::floor(tp.X) % 2 == 0 ? a : b;
    }
};

template <typename T>
class GradientPattern : public Pattern<T> {
public:
    public GradientPattern(Color<T> a, Color<T> b) {
        this.a = a;
        this.b = b;
    }

    inline constexpr Color<T> Get(Point<T> point) const noexcept {
        return a + (b - a) * (point.X - std::floor(point.X));
    }
};

template <typename T>
class MirroredGradient : public Pattern<T> {
public:
    public MirroredGradient(Color<T> a, Color<T> b) {
        this.a = a;
        this.b = b;
        Transformation = Matrix<float, 4>::I.Scaled(2, 1, 1);
    }

    inline constexpr Color<T> Get(Point<T> point) const noexcept {
        if (std::abs(point.X - std::floor(point.X)) < 0.5)
            return a + (b - a) * (2 * point.X - std::floor(2 * point.X));
        else
            return b + (a - b) * (2 * point.X - std::floor(2 * point.X));
    }
};

template <typename T>
class RingPattern : public Pattern<T> {
public:
    public RingPattern(Color<T> a, Color<T> b) {
        this.a = a;
        this.b = b;
    }
    inline constexpr Color<T> Get(Point<T> point) const noexcept {
        return std::floor(std::sqrt(point.X * point.X + point.Z * point.Z)) % 2 == 0 ? a : b;
    }
};

template <typename T>
class CheckeredPattern : public Pattern<T> {
public:
    public CheckeredPattern(Color<T> a,Color<T> b) {
        this.a = a;
        this.b = b;
    }

    inline constexpr Color<T> Get(Point<T> point) const noexcept {
        Point blend = this.Transformation.Inversed() * point;
        return (std::floor(blend.X) + std::floor(blend.Y) + std::floor(blend.Z)) % 2 == 0 ? a : b;
    }
};

template <typename T>
struct Checkered2DPattern : public Pattern<T> {
public:
    public Checkered2DPattern(Color<T> a, Color<T> b) {
        this.a = a;
        this.b = b;
    }

    inline constexpr Color<T> Get(Point<T> point) const noexcept {
        Point<T> blend = this.Transformation.Inversed() * point;
        return (std::floor(blend.X) + std::floor(blend.Z)) % 2 == 0 ? a : b;
    }
};


template <typename T>
struct RadialGradientPattern : public Pattern<T> {
public:
    constexpr RadialGradientPattern(Color<T> a, Color<T> b) noexcept {
        this.a = a;
        this.b = b;
    }
    constexpr Color<T> Get(Point<T> point) const noexcept {
        double dist = std::sqrt(point.X * point.X + point.Z * point.Z);
        return a + (b - a) * (dist - std::floor(dist));
    }
};


template <typename T>
struct NestedPattern : public Pattern<T> {
public:
    Pattern<T> a, b;
    double t;
    inline constexpr NestedPattern(Pattern<T> a, Pattern<T> b, double t = 0.5) noexcept {
        this.a = a;
        this.b = b;
        this.t = t;
    }

    inline constexpr Color<T> Get(Point<T> point) const noexcept {
        Point blend = this.Transformation.Inversed() * point;
        return a.Get(blend) * (1.0 - t) + b.Get(blend) * t;
    }
};

