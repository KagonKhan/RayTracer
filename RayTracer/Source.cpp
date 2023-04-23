#include <chrono>


#include "Canvas.h"
#include "World.h"
#include "Camera.h"
#include "Matrix.h"
#include "Materials.h"
#include "Objects.h"


using Type = double;

World<Type> world;
Camera<Type> camera{ defaultSize, 90 };

Color<Type> RenderRealTime() {
    return (camera.RenderRealTime(w) * 255).clamped();
}

Color<Type> RenderRealTime(int y, int x) {
    return (camera.RenderRealTime(y, x, w) * 255).clamped();
}

void InitRealTime() {
    Material<Type> wall_material;
    wall_material.pattern = StripePattern(Color(0.45, 0.45, 0.45), Color(0.55, 0.55, 0.55));
    wall_material.pattern.value().Transformation = I<Type>.RotatedY(1.5708).Scaled(0.25, 0.25, 0.25);
    wall_material.ambient = 0;
    wall_material.diffuse = 0.4f;
    wall_material.specular = 0;
    wall_material.reflective = 0.3;


    Plane<Type> floor;
    floor.Transformation = I<Type>.RotatedY(0.31415);
    floor.material.pattern = new Checkered2DPattern(new Color(0.35, 0.35, 0.35), new Color(0.65, 0.65, 0.65));
    floor.material.specular = 0;
    floor.material.reflective = 0.4;

    Plane<Type> ceiling;
    ceiling.Transformation = I<Type>.Translated(0, 5, 0);
    ceiling.material.color = new Color(0.8, 0.8, 0.8);
    ceiling.material.ambient = 0.3f;
    ceiling.material.specular = 0;


    Plane<Type> left_wall;
    left_wall.Transformation = I<Type>.Translated(-5, 0, 0).RotatedZ(1.5708).RotatedY(1.5708);
    left_wall.material = wall_material;

    Plane<Type> right_wall;
    right_wall.Transformation = I<Type>.Translated(5, 0, 0).RotatedZ(1.5708).RotatedY(1.5708);
    right_wall.material = wall_material;


    Plane<Type> front_wall;
    front_wall.Transformation = I<Type>.Translated(0, 0, 5).RotatedX(1.5708);
    front_wall.material = wall_material;

    Plane back_wall;
    back_wall.Transformation = I<Type>.Translated(0, 0, -5).RotatedX(1.5708);
    back_wall.material = wall_material;


    Cone s1(true, -1, 0);
    s1.Transformation = I<Type>.Translated(4.6, 0.4, 1).Scaled(0.4, 0.4, 0.4);
    s1.material = Material();
    s1.material.color = Color(0.8, 0.5, 0.3);
    s1.material.shininess = 50.f;

    Cone s2(true, -1, 0);
    s2.Transformation = I<Type>.Translated(4.7, 0.3, 0.4).Scaled(0.3, 0.3, 0.3);
    s2.material = Material();
    s2.material.color = Color(0.9, 0.4, 0.5);
    s2.material.shininess = 50.f;

    Cone s3(true, -1, 0);
    s3.Transformation = I<Type>.Translated(-1, 0.5, 4.5).Scaled(0.5, 0.5, 0.5);
    s3.material = Material();
    s3.material.color = Color(0.4, 0.9, 0.6);
    s3.material.shininess = 50.f;

    Cone s4(true, 0, 1);
    s4.Transformation = Mat4.I.Translated(-1.7, 0.3, 4.7).Scaled(0.3, 0.3, 0.3);
    s4.material = new Material();
    s4.material.color = new Color(0.4, 0.6, 0.9);
    s4.material.shininess = 50.f;


    Cone s5(true, 0, 1);
    s5.Transformation = I<Type>.Translated(-0.6, 1, 0.6);
    s5.material = Material();
    s5.material.color = Color(1, 0.3, 0.2);
    s5.material.shininess = 5.f;
    s5.material.specular = 0.4f;

    Cone s6(true, -1, 0);
    s6.Transformation = I<Type>.Translated(0.6, 1.0, -0.6).Scaled(0.7, 0.7, 0.7);
    s6.material = Material();
    s6.material.color = Color(0, 0, 0.2);
    s6.material.ambient = 0.0f;
    s6.material.diffuse = 0.4f;
    s6.material.specular = 0.9f;
    s6.material.shininess = 300.f;
    s6.material.reflective = 0.9;
    s6.material.transparency = 0.9;
    s6.material.refraction = 1.5;


    Cone s7(true, 0, 1);
    s7.Transformation = Mat4.I.Translated(-0.7, 1.0, -0.8).Scaled(0.5, 0.5, 0.5);
    s7.material = Material();
    s7.material.color = Color(0, 0.2, 0);
    s7.material.ambient = 0.0f;
    s7.material.diffuse = 0.4f;
    s7.material.specular = 0.9f;
    s7.material.shininess = 300.f;
    s7.material.reflective = 0.9;
    s7.material.transparency = 0.9;
    s7.material.refraction = 1.5;


    camera = Camera<Type>(1920, 1080, 1.152);
    camera.Transformation = ViewTransform(Point(-2.6, 1.5, -3.9), Point(-0.6, 1, -0.8), Vector(0, 1, 0));

    world = World(floor, ceiling, front_wall, back_wall, left_wall, right_wall, s1, s2, s3, s6, s7);
    world.lights.Add(PointLight(Point(-4.9, 4.9, -1), Color(1, 1, 1)));
}






int main() {
    InitRealTime();

    auto canvas = camera.RenderToCanvas(world);

    canvas.ToPPM();
}
