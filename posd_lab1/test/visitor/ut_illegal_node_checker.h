#include "../../src/shape.h"
#include "../../src/circle.h"
#include "../../src/triangle.h"
#include "../../src/triangle.h"
#include "../../src/compound_shape.h"
#include "../../src/visitor/illegal_node_checker.h"

class IllegalNodeCheckerTest : public ::testing::Test
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

TEST_F(IllegalNodeCheckerTest, LeafShapeShouldNotBeIllegal) {
    IllegalNodeChecker *checker = new IllegalNodeChecker();
    tri1->accept(checker);
    ASSERT_FALSE(checker->isIllegal());
    cir1->accept(checker);
    ASSERT_FALSE(checker->isIllegal());
    rect2->accept(checker);
    ASSERT_FALSE(checker->isIllegal());
    delete checker;
}

TEST_F(IllegalNodeCheckerTest, ACompoundShapeWithNoChildrenShouldBeIllegal) {
    Shape *ss[] = {};
    CompoundShape *cs = new CompoundShape(ss, 0);
    IllegalNodeChecker *checker = new IllegalNodeChecker();
    cs->accept(checker);
    ASSERT_TRUE(checker->isIllegal());
    delete checker;
}

TEST_F(IllegalNodeCheckerTest, ACompoundShapeWithALeafChildShouldNotBeIllegal) {
    Shape *ss[] = {tri2};
    CompoundShape *cs = new CompoundShape(ss, 1);
    IllegalNodeChecker *checker = new IllegalNodeChecker();
    cs->accept(checker);
    ASSERT_FALSE(checker->isIllegal());
    delete checker;
}

TEST_F(IllegalNodeCheckerTest, ACompoundShapeWithACompoundShapeChildShouldBeIllegal) {
    Shape *ss2[] = {rect1};
    CompoundShape *cs2 = new CompoundShape(ss2, 1);
    Shape *ss1[] = {cs2};
    CompoundShape *cs1 = new CompoundShape(ss1, 1);
    IllegalNodeChecker *checker = new IllegalNodeChecker();
    cs1->accept(checker);
    ASSERT_TRUE(checker->isIllegal());
    delete checker;
}

TEST_F(IllegalNodeCheckerTest, ACompoundShapeHavingTwoCompoundShapesShouldNotBeIllegal) {
    Shape *ss3[] = {rect1};
    CompoundShape *cs3 = new CompoundShape(ss3, 1);
    Shape *ss2[] = {cir1};
    CompoundShape *cs2 = new CompoundShape(ss2, 1);
    Shape *ss1[] = {cs2, cs3};
    CompoundShape *cs1 = new CompoundShape(ss1, 2);
    IllegalNodeChecker *checker = new IllegalNodeChecker();
    cs1->accept(checker);
    ASSERT_FALSE(checker->isIllegal());
    delete checker;
}