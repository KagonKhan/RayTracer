#pragma once
#include "Point.h"
#include "Vector.h"
#include "Matrix.h"
#include <optional>
#include "Objects.h"

template <typename T>
struct Ray
{
    Point<T> origin;
    Vector<T> direction;

    constexpr Ray(Point<T> const& origin, Vector<T> const& direction) noexcept
        : origin(origin), direction(direction) { }

    constexpr Point<T> position(T t) const noexcept {
        return direction * t + origin;
    }

    constexpr Ray<T> Transformed(Matrix<T, 4> transformation) const noexcept {
        return { transformation * origin, transformation * direction };
    }
};

template <typename T>
struct Computations
{
    T t;
    HitObject obj;
    Point<T> point, over_point, under_point;
    Vector<T> eye, normal, reflect;
    bool inside;
    T n1{ 0 }, n2{ 0 };

    public Computations(T t, HitObject obj, Point p, Vector eye, Vector norm, bool inside) const noexcept
        : t(t), obj(obj), point(p), eye(eye), normal(norm), inside(inside), over_point(p + normal * MatMaths.eps), under_point(p - normal * (MatMaths.eps)) {
        reflect = Vector.Reflect(-eye, normal);
    }


    /* public double Schlick() {
         double cos = eye.Dot(normal);

         if (n1 > n2)
         {
             double n = n1 / n2;
             double sin_2t = n * n * (1 - cos * cos);

             if (sin_2t > 1.0)
                 return 1.0;

             double cos_t = Math.Sqrt(1.0 - sin_2t);
             cos = cos_t;
         }

         double r0 = Math.Pow((n1 - n2) / (n1 + n2), 2);
         return r0 + (1 - r0) * Math.Pow(1 - cos, 5);
     }*/
};


template<typename T>
class Intersection {
    std::optional<HitObject> obj;
    T t;

    constexpr Intersection(HitObject obj, T t) noexcept {
        this.obj = obj;
        this.t = t;
    }

    constexpr static Intersection Hit(List<Intersection> xs) const noexcept {
        if (xs == null) return null;


        xs.Sort((Intersection a, Intersection b) = > MatMaths.SpaceshipOp(a.t, b.t));

        for (int i = 0; i < xs.Count; i++)
            if (xs[i].t > 0d)
                return xs[i];

        return null;
    }

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
    }
};

#include <vector>
#include <memory>
#include "Objects.h"
#include "Light.h"


template<typename T>
class World {
    const int depth = 5;

    // Possibly a dictionary with IDs
    std::vector<std::unique_ptr<HitObject>> objects;
    std::vector<std::unique_ptr<Light>> lights;

    constexpr World(std::vector<std::unique_ptr<HitObject>> objects) noexcept : objects(std::move(objects)) {   }

    constexpr World() noexcept {
        PointLight<T>* light = new PointLight<T>(Point<T>{-10, 10, -10}, Color<T>{1, 1, 1});
        Sphere<T>* s1 = new Sphere();
        Sphere<T>* s2 = new Sphere();

        s1.material.color = new Color(0.8f, 1.0f, 0.6f);
        s1.material.diffuse = 0.7f;
        s1.material.specular = 0.2f;

        s2.Transformation = MatMaths.Scaling(0.5, 0.5, 0.5);


        lights.Add(light);
        objects.AddLast(s1);
        objects.AddLast(s2);
    }


    constexpr std::vector<Intersection> Intersect(Ray r) const noexcept {
        std::vector<Intersection> retVal;
        for(auto item : objects) {
            std::vector<Intersection> xs = item.IntersectionsWith(r);
            if (xs.Count != 0)
                retVal.AddRange(xs);
        }

        retVal.Sort((Intersection a, Intersection b) = > MatMaths.SpaceshipOp(a.t, b.t));
        return retVal;
    }

    constexpr Color Shading(in Computations comp, int remaining) const noexcept {
        Color retVal = Color.Black;

        
        for (int lightIndex = 0; auto light : lights) {
            bool shaded = IsShadowed(comp.over_point, lightIndex);
            retVal += light.Lighting(comp.obj.material, comp.obj, comp.point, comp.eye, comp.normal, shaded);

            lightIndex++;
        }

        Color<T> reflected = ReflectiveShading(comp, remaining);
        Color<T> refracted = RefractiveShading(comp, remaining);

        Material<T> mat = comp.obj.material;

        if (mat.reflective > 0 && mat.transparency > 0) {
            double reflectance = comp.Schlick();
            return retVal + (reflected * reflectance) + (refracted * (1 - reflectance));
        }

        return retVal + reflected + refracted;
    }

    /*public Color ReflectiveShading(in Computations comp, int remaining)
    {
        if (comp.obj.material.reflective == 0 || remaining <= 0)
            return new Color(0, 0, 0);


        Ray reflect_ray = new Ray(comp.over_point, comp.reflect);
        Color color = Coloring(reflect_ray, remaining - 1);

        return color * comp.obj.material.reflective;
    }
    public Color RefractiveShading(in Computations comp, int remaining)
    {

        if (comp.obj.material.transparency == 0 || remaining <= 0)
            return new Color(0, 0, 0);


        double ratio = comp.n1 / comp.n2;
        double cos_i = MatMaths.Dot(comp.eye, comp.normal);
        double sin_2t = ratio * ratio * (1.0 - cos_i * cos_i);

        if (sin_2t > 1)
            return new Color(0, 0, 0);

        double cos_t = Math.Sqrt(1.0 - sin_2t);
        Vector dir = comp.normal * (ratio * cos_i - cos_t) - comp.eye * ratio;

        Ray ref_ray = new Ray(comp.under_point, dir);

        return Coloring(ref_ray, remaining - 1) * comp.obj.material.transparency;
    }

    public Color Coloring(in Ray r, int remaining = depth)
    {
        List<Intersection> xs = Intersect(r);
        Intersection hit = Intersection.Hit(xs);


        if (hit == null)
        {
            return Color.Black;
        }
        else {
            Computations comp = hit.Compute(r, xs);
            return Shading(comp, remaining);
        }
    }


    public bool IsShadowed(in Point p, int lightIndex)
    {
        Vector v = lights[lightIndex].pos - p;

        double distance = v.Magnitude();
        Vector direction = v.Normalized();

        Ray r = new Ray(p, direction);

        List<Intersection> xs = Intersect(r);
        Intersection h = Intersection.Hit(xs);

        if (h != null && h.t < distance)
            return true;
        else
            return false;
    }*/
};
