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


#include "../RayTracer/Objects.h"
TEST(IntersectionTests, IntersectionTest) {
	Ray<double> r{ .origin{0, 0, -5}, .direction{0, 0, 1} };
	Sphere<double> s;
	Object<Sphere<double>, double> o{ s };

	auto xs = o.IntersectionsWith(r);

	ASSERT_TRUE(xs.has_value());
	ASSERT_EQ(4.0, xs.value().first.t);
	ASSERT_EQ(6.0, xs.value().second.t);
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

TEST(IntersectionTests, Intersection2Test) {
	Ray<double> r{ .origin{0, 1, -5}, .direction{0, 0, 1} };
	Sphere<double> s;
	Object<Sphere<double>, double> o{ s };
	auto xs = o.IntersectionsWith(r);


	ASSERT_TRUE(xs.has_value());
	ASSERT_EQ(5.0, xs.value().first.t);
	ASSERT_EQ(5.0, xs.value().second.t);
}

TEST(IntersectionTests, Intersection3Test) {
	Ray<double> r{ .origin{0, 2, -5}, .direction{0, 0, 1} };
	Sphere<double> s;
	Object<Sphere<double>, double> o{ s };
	auto xs = o.IntersectionsWith(r);

	ASSERT_FALSE(xs.has_value());
}

TEST(IntersectionTests, Intersection4Test) {
	Ray<double> r{ .origin{0, 0, 0}, .direction{0, 0, 1} };
	Sphere<double> s;
	Object<Sphere<double>, double> o{ s };
	auto xs = o.IntersectionsWith(r);


	ASSERT_TRUE(xs.has_value());
	ASSERT_EQ(-1.0, xs.value().first.t);
	ASSERT_EQ(1.0, xs.value().second.t);
}

TEST(IntersectionTests, Intersection5Test) {
	Ray<double> r{ .origin{0, 0, 5}, .direction{0, 0, 1} };
	Sphere<double> s;
	Object<Sphere<double>, double> o{ s };
	auto xs = o.IntersectionsWith(r);


	ASSERT_TRUE(xs.has_value());
	ASSERT_EQ(-6.0, xs.value().first.t);
	ASSERT_EQ(-4.0, xs.value().second.t);
}