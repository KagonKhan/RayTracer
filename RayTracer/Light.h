#pragma once
#include "Light.h"
#include "Point.h"
#include "Objects.h"
#include "Color.h"

template <typename T>
struct Light {
    Point<T> pos;
    Color<T> intensity;

    constexpr Color<T> Lighting(Material m, HitObject obj, Point p, Vector eye, Vector norm, bool shadowed = false) noexcept = 0;
};


template <typename T>
struct PointLight : public Light<T> {
    inline constexpr PointLight(Point<T> p, Color<T> i) : pos(p), intensity(i) noexcept { }

    constexpr Color<T> Lighting(Material<T> m, HitObject<T> obj, Point<T> p, Vector<T> eye, Vector<T> norm, bool shadowed = false) const noexcept override {
        Color<T> eff_color = (m.pattern != null) ? m.pattern.GetOnObject(p, obj) : m.color;
        eff_color *= intensity;

        Color<T> ambient = eff_color * m.ambient;

        Vector<T> lightV = MatMaths.Norm(pos - p);

        Color<T> dif;
        Color<T> spec;

        double light_dot_normal = MatMaths.Dot(lightV, norm);
        if (light_dot_normal < 0 || shadowed) {
            dif = Color.Black;
            spec = Color.Black;
        }
        else {
            dif = eff_color * m.diffuse * light_dot_normal;

            Vector<T> reflectv = Vector.Reflect(-lightV, norm);
            double reflect_dot_eye = MatMaths.Dot(reflectv, eye);

            if (reflect_dot_eye <= 0)
                spec = Color<T>::Black;
            else {
                double factor = Math.Pow(reflect_dot_eye, m.shininess);
                spec = intensity * m.specular * factor;

            }

        }
        Color<T> c = ambient + dif + spec;
        return c;
    }
};
