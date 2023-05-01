//#pragma once
//#include "Point.h"
//#include "Vector.h"
//#include "Matrix.h"
//#include <optional>
//#include "Objects.h"
//
//
//#include <vector>
//#include <memory>
//#include "Objects.h"
//#include "Light.h"
//
//
//template<typename T>
//class World {
//    const int depth = 5;
//
//    // Possibly a dictionary with IDs
//    std::vector<std::unique_ptr<HitObject>> objects;
//    std::vector<std::unique_ptr<Light>> lights;
//
//    constexpr World(std::vector<std::unique_ptr<HitObject>> objects) noexcept : objects(std::move(objects)) {   }
//
//    constexpr World() noexcept {
//        PointLight<T>* light = new PointLight<T>(Point<T>{-10, 10, -10}, Color<T>{1, 1, 1});
//        Sphere<T>* s1 = new Sphere();
//        Sphere<T>* s2 = new Sphere();
//
//        s1.material.color = new Color(0.8f, 1.0f, 0.6f);
//        s1.material.diffuse = 0.7f;
//        s1.material.specular = 0.2f;
//
//        s2.Transformation = MatMaths.Scaling(0.5, 0.5, 0.5);
//
//
//        lights.Add(light);
//        objects.AddLast(s1);
//        objects.AddLast(s2);
//    }
//
//
//    constexpr std::vector<Intersection> Intersect(Ray r) const noexcept {
//        std::vector<Intersection> retVal;
//        for(auto item : objects) {
//            std::vector<Intersection> xs = item.IntersectionsWith(r);
//            if (xs.Count != 0)
//                retVal.AddRange(xs);
//        }
//
//        retVal.Sort((Intersection a, Intersection b) = > MatMaths.SpaceshipOp(a.t, b.t));
//        return retVal;
//    }
//
//    constexpr Color Shading(in Computations comp, int remaining) const noexcept {
//        Color retVal = Color.Black;
//
//        
//        for (int lightIndex = 0; auto light : lights) {
//            bool shaded = IsShadowed(comp.over_point, lightIndex);
//            retVal += light.Lighting(comp.obj.material, comp.obj, comp.point, comp.eye, comp.normal, shaded);
//
//            lightIndex++;
//        }
//
//        Color<T> reflected = ReflectiveShading(comp, remaining);
//        Color<T> refracted = RefractiveShading(comp, remaining);
//
//        Material<T> mat = comp.obj.material;
//
//        if (mat.reflective > 0 && mat.transparency > 0) {
//            double reflectance = comp.Schlick();
//            return retVal + (reflected * reflectance) + (refracted * (1 - reflectance));
//        }
//
//        return retVal + reflected + refracted;
//    }
//
//    /*public Color ReflectiveShading(in Computations comp, int remaining)
//    {
//        if (comp.obj.material.reflective == 0 || remaining <= 0)
//            return new Color(0, 0, 0);
//
//
//        Ray reflect_ray = new Ray(comp.over_point, comp.reflect);
//        Color color = Coloring(reflect_ray, remaining - 1);
//
//        return color * comp.obj.material.reflective;
//    }
//    public Color RefractiveShading(in Computations comp, int remaining)
//    {
//
//        if (comp.obj.material.transparency == 0 || remaining <= 0)
//            return new Color(0, 0, 0);
//
//
//        double ratio = comp.n1 / comp.n2;
//        double cos_i = MatMaths.Dot(comp.eye, comp.normal);
//        double sin_2t = ratio * ratio * (1.0 - cos_i * cos_i);
//
//        if (sin_2t > 1)
//            return new Color(0, 0, 0);
//
//        double cos_t = Math.Sqrt(1.0 - sin_2t);
//        Vector dir = comp.normal * (ratio * cos_i - cos_t) - comp.eye * ratio;
//
//        Ray ref_ray = new Ray(comp.under_point, dir);
//
//        return Coloring(ref_ray, remaining - 1) * comp.obj.material.transparency;
//    }
//
//    public Color Coloring(in Ray r, int remaining = depth)
//    {
//        List<Intersection> xs = Intersect(r);
//        Intersection hit = Intersection.Hit(xs);
//
//
//        if (hit == null)
//        {
//            return Color.Black;
//        }
//        else {
//            Computations comp = hit.Compute(r, xs);
//            return Shading(comp, remaining);
//        }
//    }
//
//
//    public bool IsShadowed(in Point p, int lightIndex)
//    {
//        Vector v = lights[lightIndex].pos - p;
//
//        double distance = v.Magnitude();
//        Vector direction = v.Normalized();
//
//        Ray r = new Ray(p, direction);
//
//        List<Intersection> xs = Intersect(r);
//        Intersection h = Intersection.Hit(xs);
//
//        if (h != null && h.t < distance)
//            return true;
//        else
//            return false;
//    }*/
//};
