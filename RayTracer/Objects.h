#pragma once
#include "Materials.h"
#include "Matrix.h"
#include "Vector.h"
#include "World.h"



template <typename T>
struct HitObject
{
public:
    inline static int currID{ 0 };
    int ID;

    Material<T> material;
    Mat4<float> Transformation{ I<float> };

protected:
    void HitObject() {
        ID = currID++;
    }

    virtual Vector LocalNormalAt(Point p) = 0;
    virtual std::vector<Intersection> LocalIntersectionsWith(Ray ray) = 0;


    Vector NormalAt(Point p) {
        Mat4<float> inv = Transformation.Inversed();
        Point local_point = inv * p;
        Vector local_normal = LocalNormalAt(local_point);
        Vector world_normal = inv.Transposed() * local_normal;
        world_normal.W = 0;

        return world_normal.Normalized();
    }

    std::vector<Intersection> IntersectionsWith(Ray ray)
    {
        Ray r = ray.Transformed(Transformation.Inversed());

        return LocalIntersectionsWith(r);
    }
};

template<typename T>
struct TestObject : HitObject<T> {
    Ray saved_ray;

protected:
    std::vector<Intersection> LocalIntersectionsWith(Ray ray) override {
        saved_ray = ray;
        return new List<Intersection>();
    }

    Vector LocalNormalAt(Point p) override
    {
        Vector norm = (p - Point(0, 0, 0));
        norm.W = 0;
        return norm.Normalized();
    }
};

template<typename T>
struct Sphere : HitObject<T>
{

protected:
    std::vector<Intersection> LocalIntersectionsWith(Ray ray) override {

        Vector<T> sphereToRay = ray.origin - Point(0, 0, 0);

        double a = ray.direction.Dot(ray.direction);
        double b = 2 * ray.direction.Dot(sphereToRay);
        double c = sphereToRay.Dot(sphereToRay) - 1;

        double delta = b * b - 4 * a * c;

        if (delta < 0)
            return new List<Intersection>();
        else
        {
            double t1 = (-b - Math.Sqrt(delta)) / (2 * a);
            double t2 = (-b + Math.Sqrt(delta)) / (2 * a);

            return new std::vector<Intersection>{ {this, t1 }, { this, t2 } };
        }
    }


    Vector LocalNormalAt(Point p) override
    {
        Vector norm = (p - new Point(0, 0, 0));
        norm.W = 0;
        return norm.Normalized();
    }
};

template<typename T>
struct Plane : HitObject<T>
{

protected:
    std::vector<Intersection> LocalIntersectionsWith(Ray ray) override
    {
        if (Math.Abs(ray.direction.Y) < MatMaths.eps)
            return std::vector<Intersection>();

        double t = -ray.origin.Y / ray.direction.Y;

        return std::vector<Intersection>() { Intersection(*this, t) };

    }
    Vector LocalNormalAt(Point p) override
    {
        return new Vector(0, 1, 0);
    }
};

template <typename T>
struct Cube : HitObject<T>
{
protected:
    std::vector<Intersection> LocalIntersectionsWith(Ray ray) override
    {
        double[xtmin, xtmax] = CheckAxis(ray.origin.X, ray.direction.X);
        double[ytmin, ytmax] = CheckAxis(ray.origin.Y, ray.direction.Y);
        double[ztmin, ztmax] = CheckAxis(ray.origin.Z, ray.direction.Z);

        double tmin = MatMaths.Max(xtmin, ytmin, ztmin);
        double tmax = MatMaths.Min(xtmax, ytmax, ztmax);

        if (tmin > tmax)
            return std::vector<Intersection>();
        else
            return std::vector<Intersection>() { Intersection(*this, tmin), Intersection(*this, tmax) };

    }

    Vector LocalNormalAt(Point p) override
    {
        Point abs = p.AsAbs();
        double max = MatMaths.Max(abs.X, abs.Y, abs.Z);

        if (max == abs.X)
            return Vector(p.X, 0, 0);
        if (max == abs.Y)
            return Vector(0, p.X, 0);
        else
            return Vector(0, 0, p.Z);
    }


private:
    std::pair<double, double> CheckAxis(double origin, double direction) {
        double min_numerator = -1 - origin;
        double max_numerator = 1 - origin;

        direction = 1.0 / direction;
        double tmin = min_numerator * direction;
        double tmax = max_numerator * direction;


        if (tmin > tmax)
            return { tmax, tmin };
        else
            return { tmin, tmax };

    }
};


template <typename T>
struct Cylinder : HitObject<T>
{
private:
    bool closed;
    double ymin;
    double ymax;


public:
    Cylinder(bool closed = false, double min = double.NegativeInfinity, double max = double.PositiveInfinity)
    {
        this.closed = closed;
        ymin = min;
        ymax = max;
    }



protected:
    std::vector<Intersection> LocalIntersectionsWith(Ray ray) override
    {
        double a = std::pow(ray.direction.X, 2) + std::pow(ray.direction.Z, 2);

        if (std::abs(a) < std::numeric_limits<T>::epsilon)
            return new();

        double b = 2 * ray.origin.X * ray.direction.X + 2 * ray.origin.Z * ray.direction.Z;
        double c = std::pow(ray.origin.X, 2) + std::pow(ray.origin.Z, 2) - 1;
        double d = b * b - 4 * a * c;

        if (d < 0)
            return {};


        double t0 = (-b - std::sqrt(d)) / (2 * a);
        double t1 = (-b + std::sqrt(d)) / (2 * a);

        if (t0 > t1) std::swap(t0, t1);

        std::vector<Intersection> retVal;

        double y0 = ray.origin.Y + t0 * ray.direction.Y;
        if (ymin < y0 && y0 < ymax)
            retVal.emplace_back(*this, t0);

        double y1 = ray.origin.Y + t1 * ray.direction.Y;
        if (ymin < y1 && y1 < ymax)
            retVal.emplace_back(*this, t1);

        IntersectEnds(ray, retVal);


        return retVal;
    }
    Vector LocalNormalAt(Point p) override
    {
        double dist = Math.Pow(p.X, 2) + Math.Pow(p.Z, 2);

        if (dist < 1 && p.Y >= ymax - std::numeric_limits<T>::epsilon)
            return Vector(0, 1, 0);

        if (dist < 1 && p.Y <= ymin + std::numeric_limits<T>::epsilon)
            return Vector(0, -1, 0);

        return Vector(p.X, 0, p.Z);
    }


private:
    bool CheckEnds(Ray r, double t)
    {
        double x = r.origin.X + t * r.direction.X;
        double z = r.origin.Z + t * r.direction.Z;

        return (std::pow(x, 2) + std::pow(z, 2)) <= 1;
    }
    void IntersectEnds(Ray r, std::vector<Intersection>& xs)
    {
        if (!closed || r.direction.Y <= std::numeric_limits<T>::epsilon)
            return;

        double t = (ymin - r.origin.Y) / r.direction.Y;
        if (CheckEnds(r, t))
            xs.emplace_back(*this, t);

        t = (ymax - r.origin.Y) / r.direction.Y;
        if (CheckEnds(r, t))
            xs.emplace_back(*this, t);

    }
};

//public class Cone : HitObject
//{
//    private bool closed;
//    private double ymin;
//    private double ymax;
//
//    public Cone(bool closed = false, double min = double.NegativeInfinity, double max = double.PositiveInfinity) : base()
//    {
//        this.closed = closed;
//        ymin = min;
//        ymax = max;
//    }
//    protected override List<Intersection> LocalIntersectionsWith(in Ray ray)
//    {
//        ray.direction.Normalize();
//        double a = Math.Pow(ray.direction.X, 2) -
//            Math.Pow(ray.direction.Y, 2) +
//            Math.Pow(ray.direction.Z, 2);
//
//        double b = 2.0 * ray.origin.X * ray.direction.X -
//            2.0 * ray.origin.Y * ray.direction.Y +
//            2.0 * ray.origin.Z * ray.direction.Z;
//
//        double c = Math.Pow(ray.origin.X, 2) -
//            Math.Pow(ray.origin.Y, 2) +
//            Math.Pow(ray.origin.Z, 2);
//
//        double d = b * b - 4.0 * a * c;
//
//        if (Math.Abs(a) < MatMaths.eps && Math.Abs(b) < MatMaths.eps)
//            return new();
//
//
//
//        if (d < 0)
//            return new();
//
//        if (Math.Abs(a) < MatMaths.eps) {
//            double t = -c / (2 * b);
//            return new(){
//                new(this, t)
//            };
//        }
//        double t0 = (-b - Math.Sqrt(d)) / (2 * a);
//        double t1 = (-b + Math.Sqrt(d)) / (2 * a);
//
//        if (t0 > t1)
//            (t0, t1) = (t1, t0);
//
//        List<Intersection> retVal = new();
//
//        double y0 = ray.origin.Y + t0 * ray.direction.Y;
//        if (ymin < y0 && y0 < ymax)
//            retVal.Add(new(this, t0));
//
//        double y1 = ray.origin.Y + t1 * ray.direction.Y;
//        if (ymin < y1 && y1 < ymax)
//            retVal.Add(new(this, t1));
//
//        IntersectEnds(ray, ref retVal);
//
//
//        return retVal;
//    }
//    protected override Vector LocalNormalAt(in Point p)
//    {
//        double dist = Math.Pow(p.X, 2) + Math.Pow(p.Z, 2);
//
//        if (dist < 1 && p.Y >= ymax - MatMaths.eps)
//            return new Vector(0, 1, 0);
//
//        if (dist < 1 && p.Y <= ymin + MatMaths.eps)
//            return new Vector(0, -1, 0);
//
//        double y = Math.Sqrt(Math.Pow(p.X, 2) + Math.Pow(p.Z, 2));
//
//        return new Vector(p.X, (p.Y < 0 ? y : -y), p.Z);
//    }
//
//
//    private bool CheckEnds(in Ray r, double t)
//    {
//        double x = r.origin.X + t * r.direction.X;
//        double y = r.origin.Y + t * r.direction.Y;
//        double z = r.origin.Z + t * r.direction.Z;
//
//        return (Math.Pow(x, 2) + Math.Pow(z, 2)) <= Math.Abs(y);
//    }
//    private void IntersectEnds(in Ray r, ref List<Intersection> xs)
//    {
//        if (!closed || r.direction.Y <= MatMaths.eps)
//            return;
//
//        double t = (ymin - r.origin.Y) / r.direction.Y;
//        if (CheckEnds(r, t))
//            xs.Add(new(this, t));
//
//        t = (ymax - r.origin.Y) / r.direction.Y;
//        if (CheckEnds(r, t))
//            xs.Add(new(this, t));
//
//    }
//}
