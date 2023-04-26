#include "pch.h"

#include "../RayTracer/Vector.h"
TEST(TupleTest, PointCreationTest) {
	Point p(4, -4, 3);
	std::array expected{ 4, -4, 3, 1 };

	for (int i = 0; i < expected.size(); ++i) {
		ASSERT_EQ(expected[i], p[i]);
	}
}

TEST(TupleTest, VectorCreationTest) {
	Vector v(4, -4, 3);
	std::array expected{ 4, -4, 3, 0 };

	for (int i = 0; i < expected.size(); ++i) {
		ASSERT_EQ(expected[i], v[i]);
	}
}


TEST(TupleTest, TupleAdditionTest) {
	Tuple t1(3, -2, 5, 1);
	Tuple t2(-2, 3, 1, 0);
	Tuple expected(1, 1, 6, 1);


	ASSERT_EQ(expected, t1+t2);
}


TEST(TupleTest, PointSubtractionTest) {
	Point p1(3, 2, 1);
	Point p2(5, 6, 7);
	Vector expected(-2, -4, -6);


	ASSERT_EQ(expected, p1-p2);
}


TEST(TupleTest, PointVectorSubtractionTest) {
	Point p(3, 2, 1);
	Vector v(5, 6, 7);
	Point expected(-2, -4, -6);


	ASSERT_EQ(expected, p-v);
}


TEST(TupleTest, VectorSubtractionTest) {
	Vector v1(3, 2, 1);
	Vector v2(5, 6, 7);
	Vector expected(-2, -4, -6);


	ASSERT_EQ(expected, v1 - v2);
}

TEST(TupleTest, VectorSubtraction2Test) {
	Vector v1 { 0, 0, 0 };
	Vector v2 { 1, -2, 3 };
	Vector expected { -1, 2, -3 };


	ASSERT_EQ(expected, v1 - v2);
}

TEST(TupleTest, VectorSubtraction3Test) {
	Vector v { 1, -2, 3 };
	Vector expected { -1, 2, -3 };


	ASSERT_EQ(expected, -v);
}


TEST(TupleTest, TupleScalarMultiplicationTest) {
	Tuple t{ 1, -2, 3, -4};
	Tuple expected{ 3.5, -7.0, 10.5, -14.0 };


	ASSERT_EQ(expected, t * 3.5);
}

TEST(TupleTest, TupleScalarMultiplication2Test) {
	Tuple t{ 1, -2, 3, -4};
	Tuple expected{ 0.5, -1.0, 1.5, -2.0 };


	ASSERT_EQ(expected, t * 0.5);
}

TEST(TupleTest, TupleScalarDivisionTest) {
	Tuple t{ 1, -2, 3, -4 };
	Tuple expected{ 0.5, -1.0, 1.5, -2.0 };


	ASSERT_EQ(expected, t / 2.0);
}

TEST(TupleTest, VectorMagnitudeTest) {
	int expected{ 1 };


	ASSERT_EQ(expected, Vector(1, 0, 0).magnitude());
	ASSERT_EQ(expected, Vector(0, 1, 0).magnitude());
	ASSERT_EQ(expected, Vector(0, 0, 1).magnitude());
}

TEST(TupleTest, VectorMagnitude2Test) {
	ASSERT_EQ(std::sqrt(14.0), Vector(1.0, 2.0, 3.0).magnitude());
	ASSERT_EQ(std::sqrt(14.0), Vector(-1.0, -2.0, -3.0).magnitude());
}


TEST(TupleTest, VectorNormalizationTest) {
	auto res = Vector(1.0, 2.0, 3.0).normalized();
	ASSERT_EQ(Vector(1, 0, 0), Vector(4, 0, 0).normalized());
	ASSERT_EQ(Vector(0, 1, 0), Vector(0, 4, 0).normalized());
	ASSERT_EQ(Vector(0, 0, 1), Vector(0, 0, 4).normalized());
	ASSERT_EQ(Vector(0.26726, 0.53452, 0.80178), res);
}