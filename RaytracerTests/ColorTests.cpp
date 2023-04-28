#include "pch.h"

#include "../RayTracer/Vector.h"
#include <ranges>

TEST(TupleTest, ColorCreationTest) {
	Color c(-0.5, 0.4, 1.7);

	ASSERT_EQ(-0.5, c.red());
	ASSERT_EQ(0.4, c.green());
	ASSERT_EQ(1.7, c.blue());
}

TEST(TupleTest, ColorSubtractionTest) {
	Color c1(0.9, 0.6, 0.75);
	Color c2(0.7, 0.1, 0.25);

	ASSERT_EQ(Color(0.2, 0.5, 0.5), Color(c1 - c2));
}

TEST(TupleTest, ColorMultiplicationTest) {
	Color c1(1.0, 0.2, 0.4);
	Color c2(0.9, 1.0, 0.1);

	ASSERT_EQ(Color(0.9, 0.2, 0.04), Color(c1 * c2));
}

TEST(TupleTest, ColorMultiplicationScalarTest) {
	Color c(0.2, 0.3, 0.4);
	ASSERT_EQ(Color(0.4, 0.6, 0.8), c * 2.0);
}