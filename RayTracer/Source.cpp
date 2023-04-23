#include <chrono>


#include "Canvas.h"
#include "World.h"
#include "Camera.h"
#include "Matrix.h"


static World<double> w;
static Camera<double, Size{1920, 1080}> c;

static public Color RenderRealTime()
{
    return Canvas.ClampR(c.RenderRealTime(w) * 255);
}

static public Color RenderRealTime(int y, int x)
{
    return Canvas.ClampR(c.RenderRealTime(y, x, w) * 255);
}


public static void Main()
{
    InitRealTime(7680 / 16, 4320 / 16);

    System.Diagnostics.Stopwatch watch = System.Diagnostics.Stopwatch.StartNew();
    canvas = c.RenderToCanvas(w);
    watch.Stop();

    long elapsedMs = watch.ElapsedMilliseconds;
    Console.WriteLine(elapsedMs);


    watch = System.Diagnostics.Stopwatch.StartNew();
    //canvas.ToPPM();
    watch.Stop();

    elapsedMs = watch.ElapsedMilliseconds;
    Console.WriteLine(elapsedMs);


}
    }
static public void InitRealTime(int width, int height)
{
    var wall_material = new Material();
    wall_material.pattern = new StripePattern(new Color(0.45, 0.45, 0.45), new Color(0.55, 0.55, 0.55));
    wall_material.pattern.Transformation = Mat4.I.RotatedY(1.5708).Scaled(0.25, 0.25, 0.25);
    wall_material.ambient = 0;
    wall_material.diffuse = 0.4f;
    wall_material.specular = 0;
    wall_material.reflective = 0.3;


    Plane floor = new Plane();
    floor.Transformation = MatMaths.I.RotatedY(0.31415);
    floor.material.pattern = new Checkered2DPattern(new Color(0.35, 0.35, 0.35), new Color(0.65, 0.65, 0.65));
    floor.material.specular = 0;
    floor.material.reflective = 0.4;

    Plane ceiling = new Plane();
    ceiling.Transformation = MatMaths.I.Translated(0, 5, 0);
    ceiling.material.color = new Color(0.8, 0.8, 0.8);
    ceiling.material.ambient = 0.3f;
    ceiling.material.specular = 0;


    Plane left_wall = new Plane();
    left_wall.Transformation = MatMaths.I.Translated(-5, 0, 0).RotatedZ(1.5708).RotatedY(1.5708);
    left_wall.material = wall_material;

    Plane right_wall = new Plane();
    right_wall.Transformation = MatMaths.I.Translated(5, 0, 0).RotatedZ(1.5708).RotatedY(1.5708);
    right_wall.material = wall_material;


    Plane front_wall = new Plane();
    front_wall.Transformation = MatMaths.I.Translated(0, 0, 5).RotatedX(1.5708);
    front_wall.material = wall_material;

    Plane back_wall = new Plane();
    back_wall.Transformation = MatMaths.I.Translated(0, 0, -5).RotatedX(1.5708);
    back_wall.material = wall_material;


    #region spheres
        Cone s1 = new Cone(true, -1, 0);
    s1.Transformation = Mat4.I.Translated(4.6, 0.4, 1).Scaled(0.4, 0.4, 0.4);
    s1.material = new Material();
    s1.material.color = new Color(0.8, 0.5, 0.3);
    s1.material.shininess = 50f;

    Cone s2 = new Cone(true, -1, 0);
    s2.Transformation = Mat4.I.Translated(4.7, 0.3, 0.4).Scaled(0.3, 0.3, 0.3);
    s2.material = new Material();
    s2.material.color = new Color(0.9, 0.4, 0.5);
    s2.material.shininess = 50f;

    Cone s3 = new Cone(true, -1, 0);
    s3.Transformation = Mat4.I.Translated(-1, 0.5, 4.5).Scaled(0.5, 0.5, 0.5);
    s3.material = new Material();
    s3.material.color = new Color(0.4, 0.9, 0.6);
    s3.material.shininess = 50f;

    Cone s4 = new Cone(true, 0, 1);
    s4.Transformation = Mat4.I.Translated(-1.7, 0.3, 4.7).Scaled(0.3, 0.3, 0.3);
    s4.material = new Material();
    s4.material.color = new Color(0.4, 0.6, 0.9);
    s4.material.shininess = 50f;


    Cone s5 = new Cone(true, 0, 1);
    s5.Transformation = Mat4.I.Translated(-0.6, 1, 0.6);
    s5.material = new Material();
    s5.material.color = new Color(1, 0.3, 0.2);
    s5.material.shininess = 5f;
    s5.material.specular = 0.4f;

    Cone s6 = new Cone(true, -1, 0);
    s6.Transformation = Mat4.I.Translated(0.6, 1.0, -0.6).Scaled(0.7, 0.7, 0.7);
    s6.material = new Material();
    s6.material.color = new Color(0, 0, 0.2);
    s6.material.ambient = 0.0f;
    s6.material.diffuse = 0.4f;
    s6.material.specular = 0.9f;
    s6.material.shininess = 300f;
    s6.material.reflective = 0.9;
    s6.material.transparency = 0.9;
    s6.material.refraction = 1.5;


    Cone s7 = new Cone(true, 0, 1);
    s7.Transformation = Mat4.I.Translated(-0.7, 1.0, -0.8).Scaled(0.5, 0.5, 0.5);
    s7.material = new Material();
    s7.material.color = new Color(0, 0.2, 0);
    s7.material.ambient = 0.0f;
    s7.material.diffuse = 0.4f;
    s7.material.specular = 0.9f;
    s7.material.shininess = 300f;
    s7.material.reflective = 0.9;
    s7.material.transparency = 0.9;
    s7.material.refraction = 1.5;
    #endregion

        c = new Camera(width, height, 1.152);
    c.Transformation = MatMaths.ViewTransform(new Point(-2.6, 1.5, -3.9), new Point(-0.6, 1, -0.8), new Vector(0, 1, 0));

    w = new World(floor, ceiling, front_wall, back_wall, left_wall, right_wall, s1, s2, s3, s6, s7);
    w.lights.Add(new PointLight(new Point(-4.9, 4.9, -1), new Color(1, 1, 1)));
}




int main() {
	//constexpr Point<float> p;
	//constexpr Point<float> px{ 1.f, 0.f, 0.f };

	//Vector<float> res{ p - px };

	//std::cout << res;
	//std::cout << std::endl;

	//std::cout << px.abs();

	//std::cout << "\n";
	//std::cout << res.magnitude();

		
		//3.2 seconds pure
		// 16ms constexpr
	auto t1 = std::chrono::high_resolution_clock::now();

	for (unsigned long long i = 0; i < 400'000'000; ++i) {
		constexpr Matrix<double, 4> m{ -5.0, 2.0,  6.0, -8.0,
							  1.0, -5.0,  1.0,  8.0,
							  7.0,  7.0, -6.0, -7.0,
							  1.0, -3.0,  7.0,  4.0 };
		constexpr auto mI = m.Inversed();

		/*constexpr Matrix<double, 4> mIE{0.21805,  0.45113,  0.24060, -0.04511,
							  -0.80827, -1.45677, -0.44361,  0.52068,
							  -0.07895, -0.22368, -0.05263,  0.19737,
							  -0.52256, -0.81391, -0.30075,  0.30639 };
							  */
		constexpr auto I = m * mI;
		if (I == mI) {
			std::cout << "lol. Lmao even.";
		}
	}


	auto t2 = std::chrono::high_resolution_clock::now();
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

}