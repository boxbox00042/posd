#include "../../src/shape.h"
#include "../../src/circle.h"
#include "../../src/triangle.h"
#include "../../src/triangle.h"
#include "../../src/compound_shape.h"
#include "../../src/visitor/closest_shape_finder.h"

class ClosestShapeFinderTest : public ::testing::Test
{
protected:
    Point *A, *B, *C, *D,
        *E, *F, *G, *H,
        *J, *K, *L, *M,
        *N, *O;
    Shape *tri1, *tri2, *cir1, *rect1, *rect2;

    void SetUp()
    {
        A = new Point(4, -2);
        B = new Point(6, -4);
        C = new Point(6, -8);
        D = new Point(-1.5, -8);
        E = new Point(0, -8);
        F = new Point(0, -10);
        G = new Point(-2, -11);
        H = new Point(-1, -13);
        J = new Point(-6, -7);
        K = new Point(-7, -9);
        L = new Point(-4, -9);
        M = new Point(2, -5);
        N = new Point(2, -7);
        O = new Point(4, -7);

        tri1 = new Triangle(
            new TwoDimensionalVector(A, B),
            new TwoDimensionalVector(A, C));
        tri2 = new Triangle(
            new TwoDimensionalVector(J, K),
            new TwoDimensionalVector(J, L));
        cir1 = new Circle(
            new TwoDimensionalVector(D, E));
        rect1 = new Rectangle(
            new TwoDimensionalVector(M, N),
            new TwoDimensionalVector(N, O));
        rect2 = new Rectangle(
            new TwoDimensionalVector(F, G),
            new TwoDimensionalVector(G, H));
    }

    void TearDown()
    {
        delete A;
        delete B;
        delete C;
        delete D;
        delete E;
        delete F;
        delete G;
        delete H;
        delete J;
        delete K;
        delete L;
        delete M;
        delete O;
        delete N;
        delete tri1;
        delete tri2;
        delete cir1;
        delete rect1;
        delete rect2;
    }
};

TEST_F(ClosestShapeFinderTest, visitTriangle)
{
    ClosestShapeFinder *finder = new ClosestShapeFinder(cir1);
    tri1->accept(finder);
    ASSERT_EQ(tri1, finder->getClosestShape());
    ASSERT_EQ(nullptr, finder->getParent());
}

TEST_F(ClosestShapeFinderTest, visitCircle)
{
    ClosestShapeFinder *finder = new ClosestShapeFinder(tri1);
    cir1->accept(finder);
    ASSERT_EQ(cir1, finder->getClosestShape());
    ASSERT_EQ(nullptr, finder->getParent());
}

TEST_F(ClosestShapeFinderTest, visitRectangle)
{
    ClosestShapeFinder *finder = new ClosestShapeFinder(tri1);
    rect2->accept(finder);
    ASSERT_EQ(rect2, finder->getClosestShape());
    ASSERT_EQ(nullptr, finder->getParent());
}

TEST_F(ClosestShapeFinderTest, visitCompoundShape)
{
    Shape *ss[] = {cir1, tri1};
    Shape *cs = new CompoundShape(ss, 2);
    ClosestShapeFinder *finder = new ClosestShapeFinder(rect2);
    cs->accept(finder);
    ASSERT_EQ(cir1, finder->getClosestShape());
    ASSERT_EQ(cs, finder->getParent());
}

TEST_F(ClosestShapeFinderTest, getClosestShapeShouldBeCorrectWithTwoLevelTree)
{
    Shape *ss3[] = {rect1, tri1};
    Shape *cs3 = new CompoundShape(ss3, 2);
    Shape *ss2[] = {tri2, cir1};
    Shape *cs2 = new CompoundShape(ss2, 2);
    Shape *ss1[] = {cs2, cs3};
    Shape *cs1 = new CompoundShape(ss1, 2);
    ClosestShapeFinder *finder = new ClosestShapeFinder(rect2);
    cs1->accept(finder);
    ASSERT_EQ(cir1, finder->getClosestShape());
    ASSERT_EQ(cs2, finder->getParent());
}

TEST_F(ClosestShapeFinderTest, getClosestShapeShouldBeCorrectWithThreeLevelTree)
{
    Shape *ss3[] = {cir1, rect1};
    Shape *cs3 = new CompoundShape(ss3, 2);
    Shape *ss2[] = {cs3, rect2};
    Shape *cs2 = new CompoundShape(ss2, 2);
    Shape *ss1[] = {tri2, cs2};
    Shape *cs1 = new CompoundShape(ss1, 2);
    ClosestShapeFinder *finder = new ClosestShapeFinder(tri1);
    cs1->accept(finder);
    ASSERT_EQ(rect1, finder->getClosestShape());
    ASSERT_EQ(cs3, finder->getParent());
}