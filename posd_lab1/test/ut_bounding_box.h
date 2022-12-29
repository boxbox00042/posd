#include <vector>
#include <set>
#include "../src/rectangle.h"
#include "../src/triangle.h"
#include "../src/bounding_box.h"

class CollisionTest : public ::testing::Test
{
protected:
    Point *G, *F, *E, *D, *A, *B, *C, *H, *I, *J;
    Point *R, *S, *T, *U, *K, *M, *N, *O, *P, *Q;
    std::vector<Rectangle *> recs;
    std::vector<BoundingBox *> boxes;
    void SetUp() override
    {
        G = new Point(-3, 3);
        F = new Point(-1, 3);
        E = new Point(-3, 1);
        D = new Point(-1, 1);

        A = new Point(-1, -1);
        B = new Point(1, -1);
        C = new Point(1, 1);

        H = new Point(3, 1);
        I = new Point(3, 3);
        J = new Point(1, 3);

        R = new Point(-2, -1);
        S = new Point(-3, -2);
        T = new Point(-2, -3);
        U = new Point(-1, -2);

        K = new Point(0, -1);
        M = new Point(0, -3);
        N = new Point(1, -2);

        O = new Point(2, -1);
        P = new Point(2, -3);
        Q = new Point(3, -2);

        recs = {
            new Rectangle( // 0
                new TwoDimensionalVector(G, F),
                new TwoDimensionalVector(F, D)),
            new Rectangle( // 1
                new TwoDimensionalVector(D, C),
                new TwoDimensionalVector(D, A)),
            new Rectangle( // 2
                new TwoDimensionalVector(C, J),
                new TwoDimensionalVector(I, J)),
            new Rectangle( // 3
                new TwoDimensionalVector(R, S),
                new TwoDimensionalVector(S, T)),
            new Rectangle( // 4
                new TwoDimensionalVector(M, U),
                new TwoDimensionalVector(M, N)),
            new Rectangle( // 5
                new TwoDimensionalVector(Q, O),
                new TwoDimensionalVector(P, Q))};
        boxes = {
            new BoundingBox(recs[0]->getPoints()),
            new BoundingBox(recs[1]->getPoints()),
            new BoundingBox(recs[2]->getPoints()),
            new BoundingBox(recs[3]->getPoints()),
            new BoundingBox(recs[4]->getPoints()),
            new BoundingBox(recs[5]->getPoints()),
        };
    }
    void TearDown() override
    {
        delete G;
        delete F;
        delete E;
        delete D;

        delete A;
        delete B;
        delete C;

        delete H;
        delete I;
        delete J;

        delete R;
        delete S;
        delete T;
        delete U;

        delete K;
        delete M;
        delete N;

        delete O;
        delete P;
        delete Q;
    }
};

TEST_F(CollisionTest, CalMaximumPointShouldBeCorrect)
{
    BoundingBox bb1(
        std::set<const Point *>{G, F, D, E});
    ASSERT_TRUE(*(bb1.max()) == *F);
    BoundingBox bb2(
        std::set<const Point *>{A, B, C, D});
    ASSERT_TRUE(*(bb2.max()) == *C);
    BoundingBox bb3(
        std::set<const Point *>{R, S, T, U});
    ASSERT_TRUE(*(bb3.max()) == *A);
}

TEST_F(CollisionTest, CalMinimumPointShouldBeCorrect)
{
    BoundingBox bb1(
        std::set<const Point *>{G, F, D, E});
    ASSERT_TRUE(*(bb1.min()) == *E);
    BoundingBox bb2(
        std::set<const Point *>{A, B, C, D});
    ASSERT_TRUE(*(bb2.min()) == *A);
    BoundingBox bb3(
        std::set<const Point *>{R, S, T, U});
    ASSERT_TRUE(*(bb3.min()) == Point(-3, -3));
}

TEST_F(CollisionTest, BoundingBoxOfRectangleShouldBeCorrect)
{
    BoundingBox *box1 = new BoundingBox(recs[0]->getPoints());
    ASSERT_TRUE(*(box1->max()) == *F);
    ASSERT_TRUE(*(box1->min()) == *E);
    BoundingBox *box2 = new BoundingBox(recs[1]->getPoints());
    ASSERT_TRUE(*(box2->max()) == *C);
    ASSERT_TRUE(*(box2->min()) == *A);
    BoundingBox *box3 = new BoundingBox(recs[2]->getPoints());
    ASSERT_TRUE(*(box3->max()) == *I);
    ASSERT_TRUE(*(box3->min()) == *C);

    BoundingBox *box4 = new BoundingBox(recs[3]->getPoints());
    ASSERT_TRUE(*(box4->max()) == *A);
    ASSERT_TRUE(*(box4->min()) == Point(-3, -3));
    BoundingBox *box5 = new BoundingBox(recs[4]->getPoints());
    ASSERT_TRUE(*(box5->max()) == *B);
    ASSERT_TRUE(*(box5->min()) == Point(-1, -3));
    BoundingBox *box6 = new BoundingBox(recs[5]->getPoints());
    ASSERT_TRUE(*(box6->max()) == Point(3, -1));
    ASSERT_TRUE(*(box6->min()) == Point(1, -3));
}

TEST_F(CollisionTest, BoundingBoxOfCircleShouldBeCorrect)
{
    Circle *cir1 = new Circle(new TwoDimensionalVector(
        new Point(0, -2), N));
    BoundingBox *box1 = new BoundingBox(cir1->getPoints());
    ASSERT_TRUE(*(box1->max()) == *B);
    ASSERT_TRUE(*(box1->min()) == Point(-1, -3));

    Circle *cir2 = new Circle(new TwoDimensionalVector(
        new Point(0, 0), new Point(0, 1)));
    BoundingBox *box2 = new BoundingBox(cir2->getPoints());
    ASSERT_TRUE(*(box2->max()) == *C);
    ASSERT_TRUE(*(box2->min()) == *A);

    delete cir1;
    delete cir2;
}

TEST_F(CollisionTest, BoundingBoxOfTriangleShouldBeCorrect)
{
    Triangle *tri1 = new Triangle(
        new TwoDimensionalVector(U, K),
        new TwoDimensionalVector(K, B));
    BoundingBox *box1 = new BoundingBox(tri1->getPoints());
    ASSERT_TRUE(*(box1->max()) == *B);
    ASSERT_TRUE(*(box1->min()) == *U);

    Triangle *tri2 = new Triangle(
        new TwoDimensionalVector(F, J),
        new TwoDimensionalVector(J, K));
    BoundingBox *box2 = new BoundingBox(tri2->getPoints());
    ASSERT_TRUE(*(box2->max()) == *J);
    ASSERT_TRUE(*(box2->min()) == *A);

    delete tri1;
    delete tri2;
}

TEST_F(CollisionTest, TwoAdjacentRectanglesShouldCollide)
{
    ASSERT_TRUE(boxes[0]->collide(boxes[1]));

    ASSERT_TRUE(boxes[1]->collide(boxes[1]));
    ASSERT_TRUE(boxes[1]->collide(boxes[2]));
    ASSERT_TRUE(boxes[1]->collide(boxes[3]));
    ASSERT_TRUE(boxes[1]->collide(boxes[4]));
    ASSERT_TRUE(boxes[1]->collide(boxes[5]));

    ASSERT_TRUE(boxes[2]->collide(boxes[1]));

    ASSERT_TRUE(boxes[3]->collide(boxes[1]));
    ASSERT_TRUE(boxes[3]->collide(boxes[4]));

    ASSERT_TRUE(boxes[4]->collide(boxes[1]));
    ASSERT_TRUE(boxes[4]->collide(boxes[3]));
    ASSERT_TRUE(boxes[4]->collide(boxes[4]));
    ASSERT_TRUE(boxes[4]->collide(boxes[5]));

    ASSERT_TRUE(boxes[5]->collide(boxes[1]));
    ASSERT_TRUE(boxes[5]->collide(boxes[4]));
}

TEST_F(CollisionTest, TwoNonAdjacentRectanglesShouldNotCollide)
{
    ASSERT_FALSE(boxes[0]->collide(boxes[2]));
    ASSERT_FALSE(boxes[0]->collide(boxes[3]));
    ASSERT_FALSE(boxes[0]->collide(boxes[4]));
    ASSERT_FALSE(boxes[0]->collide(boxes[5]));

    ASSERT_FALSE(boxes[2]->collide(boxes[0]));
    ASSERT_FALSE(boxes[2]->collide(boxes[3]));
    ASSERT_FALSE(boxes[2]->collide(boxes[4]));
    ASSERT_FALSE(boxes[2]->collide(boxes[5]));

    ASSERT_FALSE(boxes[3]->collide(boxes[0]));
    ASSERT_FALSE(boxes[3]->collide(boxes[2]));
    ASSERT_FALSE(boxes[3]->collide(boxes[5]));

    ASSERT_FALSE(boxes[4]->collide(boxes[0]));
    ASSERT_FALSE(boxes[4]->collide(boxes[2]));

    ASSERT_FALSE(boxes[5]->collide(boxes[0]));
    ASSERT_FALSE(boxes[5]->collide(boxes[2]));
    ASSERT_FALSE(boxes[5]->collide(boxes[3]));
}

TEST_F(CollisionTest, TwoAdjacentTrianglesShouldCollide)
{
    Triangle *tri1 = new Triangle(
        new TwoDimensionalVector(F, J),
        new TwoDimensionalVector(J, K));
    Triangle *tri2 = new Triangle(
        new TwoDimensionalVector(H, C),
        new TwoDimensionalVector(C, B));
    BoundingBox *tri1_box = new BoundingBox(tri1->getPoints());
    BoundingBox *tri2_box = new BoundingBox(tri2->getPoints());
    ASSERT_TRUE(tri1_box->collide(tri2_box));
    ASSERT_TRUE(tri2_box->collide(tri1_box));
}

TEST_F(CollisionTest, TwoNonAdjacentTrianglesShouldNotCollide)
{
    Triangle *tri1 = new Triangle(
        new TwoDimensionalVector(F, J),
        new TwoDimensionalVector(J, K));
    Triangle *tri2 = new Triangle(
        new TwoDimensionalVector(N, P),
        new TwoDimensionalVector(Q, P));
    BoundingBox *tri1_box = new BoundingBox(tri1->getPoints());
    BoundingBox *tri2_box = new BoundingBox(tri2->getPoints());
    ASSERT_FALSE(tri1_box->collide(tri2_box));
    ASSERT_FALSE(tri2_box->collide(tri1_box));
}

TEST_F(CollisionTest, TwoAdjacentCirclesShouldCollide)
{
    Circle *cir1 = new Circle(
        new TwoDimensionalVector(K, B));
    Circle *cir2 = new Circle(
        new TwoDimensionalVector(N, P));
    BoundingBox *cir1_box = new BoundingBox(cir1->getPoints());
    BoundingBox *cir2_box = new BoundingBox(cir2->getPoints());
    ASSERT_TRUE(cir1_box->collide(cir2_box));
    ASSERT_TRUE(cir2_box->collide(cir1_box));
}

TEST_F(CollisionTest, TwoNonAdjacentCirclesShouldNotCollide)
{
    Circle *cir1 = new Circle(
        new TwoDimensionalVector(K, B));
    Circle *cir2 = new Circle(
        new TwoDimensionalVector(F, G));
    BoundingBox *cir1_box = new BoundingBox(cir1->getPoints());
    BoundingBox *cir2_box = new BoundingBox(cir2->getPoints());
    ASSERT_FALSE(cir1_box->collide(cir2_box));
    ASSERT_FALSE(cir2_box->collide(cir1_box));
}


// lab 1
TEST_F(CollisionTest, DistanceShouldBeCorrect) {
    ASSERT_NEAR(2.8284 + 2.8284, boxes[0]->distance(boxes[1]), 0.001);
    ASSERT_NEAR(2.8284 + 2.8284, boxes[1]->distance(boxes[2]), 0.001);
    ASSERT_NEAR(4 + 4, boxes[0]->distance(boxes[2]), 0.001);
    ASSERT_NEAR(2 + 2, boxes[1]->distance(boxes[4]), 0.001);
}