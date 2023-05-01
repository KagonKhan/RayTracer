#include "pch.h"


#include "../RayTracer/Auxiliary.h"


TEST(RayTests, RayCreationTest) {
	Ray<int> r{ .origin = {1, 2, 3}, .direction = {4, 5, 6} };

	ASSERT_EQ(Point( 1,2,3 ), r.origin);
	ASSERT_EQ(Vector( 4,5,6 ), r.direction);
}

TEST(RayTests, RayPositionedAtTest) {
	Ray<double> r{ .origin = {2, 3, 4}, .direction = {1, 0, 0} };

	ASSERT_EQ(Point<double>(2, 3, 4), r.positionedAt(0));
	ASSERT_EQ(Point<double>(3, 3, 4), r.positionedAt(1));
	ASSERT_EQ(Point<double>(1, 3, 4), r.positionedAt(-1));
	ASSERT_EQ(Point<double>(4.5, 3, 4), r.positionedAt(2.5));
}

TEST(RayTests, RayTranslationTest) {
	Ray<double> r{ .origin = {1, 2, 3}, .direction = {0, 1, 0} };
	auto translation = I<double>.Translated(3, 4, 5);

	auto result = r.Transformed(translation);

	ASSERT_EQ(Point<double>(4, 6, 8), result.origin);
	ASSERT_EQ(Vector<double>(0, 1, 0), result.direction);
}

TEST(RayTests, RayScalingTest) {
	Ray<double> r{ .origin = {1, 2, 3}, .direction = {0, 1, 0} };
	auto translation = I<double>.Scaled(2, 3, 4);

	auto result = r.Transformed(translation);

	ASSERT_EQ(Point<double>(2, 6, 12), result.origin);
	ASSERT_EQ(Vector<double>(0, 3, 0), result.direction);
}




#include "../RayTracer/Objects.h"


TEST(HitObjectTests, SphereCreationTest) {
	HitObject<double, Sphere<double>> o{ Sphere<double>{} };

	ASSERT_EQ(I<double>, o.transformation);
}

TEST(HitObjectTests, SphereTransformTest) {
	HitObject<double, Sphere<double>> o{ Sphere<double>{} };
	o.transformation = I<double>.Translated(2, 3, 4);

	ASSERT_EQ(I<double>.Translated(2, 3, 4), o.transformation);
}

TEST(HitObjectTests, SphereTransformedHitTest) {
	Ray<double> r{ .origin{0, 0, -5}, .direction{0, 0, 1} };

	HitObject<double, Sphere<double>> o{ Sphere<double>{} };
	o.transformation = I<double>.Scaled(2, 2, 2);

	auto xs = o.IntersectionsWith(r);

	ASSERT_TRUE(xs.has_value());
	ASSERT_EQ(3.0, xs.value().first.t);
	ASSERT_EQ(7.0, xs.value().second.t);
}

TEST(HitObjectTests, SphereTransformedHit2Test) {
	Ray<double> r{ .origin{0, 0, -5}, .direction{0, 0, 1} };

	HitObject<double, Sphere<double>> o{ Sphere<double>{} };
	o.transformation = I<double>.Translated(5, 0, 0);

	auto xs = o.IntersectionsWith(r);

	ASSERT_FALSE(xs.has_value());
}




TEST(IntersectionTests, IntersectionTest) {
	Ray<double> r{ .origin{0, 0, -5}, .direction{0, 0, 1} };
	HitObject<double, Sphere<double>> o{ Sphere<double>{} };

	auto xs = o.IntersectionsWith(r);

	ASSERT_TRUE(xs.has_value());
	ASSERT_EQ(4.0, xs.value().first.t);
	ASSERT_EQ(6.0, xs.value().second.t);
}

TEST(IntersectionTests, Intersection2Test) {
	Ray<double> r{ .origin{0, 1, -5}, .direction{0, 0, 1} };
	HitObject<double, Sphere<double>> o{ Sphere<double>{} };
	auto xs = o.IntersectionsWith(r);


	ASSERT_TRUE(xs.has_value());
	ASSERT_EQ(5.0, xs.value().first.t);
	ASSERT_EQ(5.0, xs.value().second.t);
}

TEST(IntersectionTests, Intersection3Test) {
	Ray<double> r{ .origin{0, 2, -5}, .direction{0, 0, 1} };
	HitObject<double, Sphere<double>> o{ Sphere<double>{} };
	auto xs = o.IntersectionsWith(r);

	ASSERT_FALSE(xs.has_value());
}

TEST(IntersectionTests, Intersection4Test) {
	Ray<double> r{ .origin{0, 0, 0}, .direction{0, 0, 1} };
	HitObject<double, Sphere<double>> o{ Sphere<double>{} };
	auto xs = o.IntersectionsWith(r);


	ASSERT_TRUE(xs.has_value());
	ASSERT_EQ(-1.0, xs.value().first.t);
	ASSERT_EQ(1.0, xs.value().second.t);
}

TEST(IntersectionTests, Intersection5Test) {
	Ray<double> r{ .origin{0, 0, 5}, .direction{0, 0, 1} };
	HitObject<double, Sphere<double>> o{ Sphere<double>{} };
	auto xs = o.IntersectionsWith(r);


	ASSERT_TRUE(xs.has_value());
	ASSERT_EQ(-6.0, xs.value().first.t);
	ASSERT_EQ(-4.0, xs.value().second.t);
}


TEST(IntersectionTests, IntersectionSortingTest) {
	auto s = Sphere<double>();
	Intersection i1(s, 5);
	Intersection i2(s, 7);
	Intersection i3(s, -3);
	Intersection i4(s, 2);
	auto xs = Hit(i1, i2, i3, i4).value();


	ASSERT_EQ(i4, xs);
}

TEST(IntersectionTests, IntersectionSorting2Test) {
	auto s = Sphere<double>();
	Intersection i1(s, 1);
	Intersection i2(s, 2);
	auto xs = Hit(i1, i2).value();

	ASSERT_EQ(i1, xs);
}

TEST(IntersectionTests, IntersectionSorting3Test) {
	auto s = Sphere<double>();
	Intersection i1(s, -1);
	Intersection i2(s, 1);
	auto xs = Hit(i1, i2).value();

	ASSERT_EQ(i2, xs);
}

TEST(IntersectionTests, IntersectionSorting4Test) {
	auto s = Sphere<double>();
	Intersection i1(s, -2);
	Intersection i2(s, -1);
	auto xs = Hit(i1, i2);

	ASSERT_FALSE(xs.has_value());
}

