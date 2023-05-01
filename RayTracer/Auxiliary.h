#pragma once
#include "Vector.h"
#include "Matrix.h"
#include <optional>

template <typename T>
struct Ray
{
     Point<T> origin;
     Vector<T> direction;

    constexpr Point<T> positionedAt(T t) const noexcept {
        return direction * t + origin;
    }

    constexpr Ray<T> Transformed(Matrix<T, 4> const& transformation) const noexcept {
        return { transformation * origin, transformation * direction };
    }
};


template<typename HitObject, typename T>
struct Intersection {
    HitObject const& obj; // TODO: reference instead of copy?
    T t; // maybe hold a vector here, if it wont leak to runtime

    constexpr Intersection(HitObject const& obj, T t) noexcept : obj(obj), t(t) {
    }


    /*
    constexpr Computations Compute(in Ray r, List<Intersection> xs) const noexcept {

        Point pos = r.position(t);
        Vector norm = obj.NormalAt(pos);
        bool inside;

        if (norm.Dot(-r.direction) < 0)
        {
            inside = true;
            norm = -norm;
        }
        else
            inside = false;

        Computations retVal = new Computations(t, obj, pos, -r.direction.Normalized(), norm.Normalized(), inside);



        if (xs == null)
            return retVal;



        List<HitObject> containers = new List<HitObject>();

        for (int i = 0; i < xs.Count; i++)
        {
            if (this == xs[i])
            {
                if (containers.Count == 0)
                    retVal.n1 = 1.0;
                else
                    retVal.n1 = containers.Last().material.refraction;
            }

            if (containers.Contains(xs[i].obj))
                containers.Remove(xs[i].obj);
            else
                containers.Add(xs[i].obj);

            if (this == xs[i])
            {
                if (containers.Count == 0)
                    retVal.n2 = 1.0;
                else
                    retVal.n2 = containers.Last().material.refraction;
                break;
            }
        }

        return retVal;
    }*/
};


template <typename HitObject, typename T>
constexpr bool operator==(Intersection<HitObject, T> const& lhs, Intersection<HitObject, T> const& rhs) noexcept {
    return  lhs.t == rhs.t;
}

#include <vector>
template<typename HitObject, typename T, template<typename, typename> typename... Intersections>
constexpr std::optional<Intersection<HitObject, T>> Hit(Intersections<HitObject, T>... xs) noexcept {
    if (sizeof...(xs) == 0) return std::nullopt;

    std::vector<Intersection<HitObject, T>> vals{ std::move(xs)... };
    
    auto comp = [](auto const& a, auto const& b) {
        return a.t < b.t;
    };

    std::ranges::sort(vals, comp);

    for(Intersection<HitObject, T> const& x : vals) {
        if (x.t > 0.0) {
            return x;
        }
    }

    return std::nullopt;
}



//
//template <typename T>
//struct Computations
//{
//    T t;
//    HitObject obj;
//    Point<T> point, over_point, under_point;
//    Vector<T> eye, normal, reflect;
//    bool inside;
//    T n1{ 0 }, n2{ 0 };
//
//    public Computations(T t, HitObject obj, Point p, Vector eye, Vector norm, bool inside) const noexcept
//        : t(t), obj(obj), point(p), eye(eye), normal(norm), inside(inside), over_point(p + normal * MatMaths.eps), under_point(p - normal * (MatMaths.eps)) {
//        reflect = Vector.Reflect(-eye, normal);
//    }
//
//
//    /* public double Schlick() {
//         double cos = eye.Dot(normal);
//
//         if (n1 > n2)
//         {
//             double n = n1 / n2;
//             double sin_2t = n * n * (1 - cos * cos);
//
//             if (sin_2t > 1.0)
//                 return 1.0;
//
//             double cos_t = Math.Sqrt(1.0 - sin_2t);
//             cos = cos_t;
//         }
//
//         double r0 = Math.Pow((n1 - n2) / (n1 + n2), 2);
//         return r0 + (1 - r0) * Math.Pow(1 - cos, 5);
//     }*/
//};
//
