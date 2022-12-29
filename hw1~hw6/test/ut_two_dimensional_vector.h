#include <iostream>
#include "../src/two_dimensional_vector.h"

class TwoDimensionalVectorTest : public ::testing::Test
{
protected:
    Point *A, *B, *C, *D, *E, *F, *G, *H, *Z;

    void SetUp() override
    {
        A = new Point(-8.42, 3.42);
        B = new Point(-3.38, 4.3);
        C = new Point(-3.62, 2.44);
        D = new Point(-11.4686, 1.7425);
        E = new Point(-7.9470, 1.0235);
        F = new Point(-10, 5);
        G = new Point(-10.15137, 3.11769);
        H = new Point(-2.8046, 1.0046);
        Z = new Point(0, 0);
    }

    void TearDown() override
    {
        delete A;
        delete B;
        delete C;
        delete D;
        delete E;
        delete F;
        delete G;
        delete H;
        delete Z;
    }
};

TEST_F(TwoDimensionalVectorTest, ConstructorNoException)
{
    ASSERT_NO_THROW(TwoDimensionalVector(*A, *B));
    ASSERT_NO_THROW(TwoDimensionalVector(*Z, *Z));
}

TEST_F(TwoDimensionalVectorTest, AShouldBeCorrect)
{
    TwoDimensionalVector vec(*A, *B);
    ASSERT_EQ(Point(-8.42, 3.42), vec.a());
}

TEST_F(TwoDimensionalVectorTest, BShouldBeCorrect)
{
    TwoDimensionalVector vec(*A, *Z);
    ASSERT_EQ(Point(0.0, 0.0), vec.b());
}

TEST_F(TwoDimensionalVectorTest, LengthShouldBeCorrect)
{
    TwoDimensionalVector vec1(*A, *B);
    ASSERT_NEAR(5.1162, vec1.length(), 0.001);
}

TEST_F(TwoDimensionalVectorTest, DotProductWithRightAngleShouldBeZero)
{
    TwoDimensionalVector u(*A, *B);
    TwoDimensionalVector n(*B, *H);
    ASSERT_NEAR(0, u.dot(n), 0.001);
}

TEST_F(TwoDimensionalVectorTest, DotProductWithAcuteAngleShouldBePositive)
{
    // same
    TwoDimensionalVector u(*A, *B);
    TwoDimensionalVector uSame(*A, *B);
    ASSERT_NEAR(26.176, u.dot(uSame), 0.001);
    ASSERT_TRUE(u.dot(uSame) > 0);
    // parallel
    TwoDimensionalVector v(*A, *C);
    TwoDimensionalVector w(*D, *E);
    ASSERT_NEAR(17.608, v.dot(w), 0.001);
    ASSERT_TRUE(v.dot(w) > 0);
    // acute angle (21.44 deg.)
    ASSERT_NEAR(23.3296, u.dot(v), 0.001);
    ASSERT_TRUE(u.dot(v) > 0);
}

TEST_F(TwoDimensionalVectorTest, DotProductWithObtuseAngleShouldBeNegative)
{
    // flat (180 deg.)
    TwoDimensionalVector u(*A, *B);
    TwoDimensionalVector e(*A, *G);
    ASSERT_NEAR(-8.9921, u.dot(e), 0.001);
    ASSERT_TRUE(u.dot(e) < 0);
    // obtuse angle (125.10 deg)
    TwoDimensionalVector d(*A, *F);
    ASSERT_NEAR(-6.5728, u.dot(d), 0.001);
    ASSERT_TRUE(u.dot(d) < 0);
}

TEST_F(TwoDimensionalVectorTest, CrossProductOfTwoParallelVectorsShouldBeZero)
{
    // same
    TwoDimensionalVector v(*A, *C);
    TwoDimensionalVector vSame(*A, *C);
    ASSERT_NEAR(0.0, v.cross(vSame), 0.001);
    // parallel
    TwoDimensionalVector w(*D, *E);
    ASSERT_NEAR(0.0, v.cross(w), 0.001);
    // flat (180 deg.)
    TwoDimensionalVector u(*A, *B);
    TwoDimensionalVector e(*A, *G);
    ASSERT_NEAR(0.0, u.cross(e), 0.001);
}

TEST_F(TwoDimensionalVectorTest, CrossProductOfTwoVectorsWithCounterclockwiseShouldBePositive)
{
    // acute angle
    TwoDimensionalVector u(*A, *B);
    TwoDimensionalVector v(*A, *C);
    ASSERT_TRUE(v.cross(u) > 0);
    ASSERT_NEAR(9.1632, v.cross(u), 0.001);
    // right angle
    TwoDimensionalVector n(*B, *H);
    ASSERT_TRUE(n.cross(u) > 0);
    ASSERT_NEAR(17.1147, n.cross(u), 0.001);
    // obtuse angle (125.10 deg.)
    TwoDimensionalVector d(*A, *F);
    ASSERT_TRUE(v.cross(d) > 0);
    ASSERT_NEAR(6.0356, v.cross(d), 0.001);
}

TEST_F(TwoDimensionalVectorTest, CrossProductOfTwoVectorsWithClockwiseShouldBeNegative)
{
    // acute angle (54.90 deg.)
    TwoDimensionalVector d(*A, *F);
    TwoDimensionalVector e(*A, *G);
    ASSERT_TRUE(e.cross(d) < 0);
    ASSERT_NEAR(-3.2132, e.cross(d), 0.001);
    // right angle
    TwoDimensionalVector n(*B, *H);
    ASSERT_TRUE(n.cross(e) < 0);
    ASSERT_NEAR(-5.8793, n.cross(e), 0.001);
    // obtuse angle (125.10 deg.)
    TwoDimensionalVector u(*A, *B);
    ASSERT_TRUE(d.cross(u) < 0);
    ASSERT_NEAR(-9.3536, d.cross(u), 0.001);
}

TEST_F(TwoDimensionalVectorTest, InfoShouldBeCorrect)
{
    TwoDimensionalVector u(*A, *B);
    ASSERT_EQ("Vector ((-8.42, 3.42), (-3.38, 4.30))", u.info());
}