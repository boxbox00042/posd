#include <cmath>
#include "../src/two_dimensional_vector.h"
#include "../src/shape.h"
#include "../src/triangle.h"
#include "../src/rectangle.h"
#include "../src/circle.h"

class ShapeTest : public ::testing::Test
{
protected:
    Point *A, *B, *C, *I, *J, *G, *H, *K, *L;
    TwoDimensionalVector *u, *v, *k, *l, *r;
    void SetUp() override
    {

        A = new Point(5, 8);
        B = new Point(10, 8);
        C = new Point(8, 11);
        I = new Point(20, 13);
        J = new Point(16, 14);
        G = new Point(15, 10);
        K = new Point(14, 2);
        L = new Point(18, -4);
        u = new TwoDimensionalVector(*A, *B);
        v = new TwoDimensionalVector(*A, *C);
        k = new TwoDimensionalVector(*I, *J);
        l = new TwoDimensionalVector(*J, *G);
        r = new TwoDimensionalVector(*K, *L);
    }

    void TearDown() override
    {
        delete A; delete B; delete C;
        delete I; delete J; delete G;
        delete K; delete L;
        delete u; delete v; delete k;
        delete l; delete r;
    }
};

TEST_F(ShapeTest, AreaWithPolymorphismShouldBeCorrect)
{
    Shape *s1 = new Triangle(*v, *u);
    Shape *s2 = new Rectangle(*k, *l);
    Shape *s3 = new Circle(*r);
    ASSERT_NEAR(7.5, s1->area(), 0.001);
    ASSERT_NEAR(17, s2->area(), 0.001);
    ASSERT_NEAR(pow(7.2111, 2) * M_PI, s3->area(), 0.001);
    delete s1;
    delete s2;
    delete s3;
}

TEST_F(ShapeTest, PerimeterWithPolymorphismShouldBeCorrect)
{
    Shape *s1 = new Triangle(*v, *u);
    Shape *s2 = new Rectangle(*k, *l);
    Shape *s3 = new Circle(*r);
    ASSERT_NEAR(12.8481, s1->perimeter(), 0.001);
    ASSERT_NEAR(16.4924, s2->perimeter(), 0.001);
    ASSERT_NEAR(2 * M_PI * 7.2111, s3->perimeter(), 0.001);
    delete s1;
    delete s2;
    delete s3;
}

TEST_F(ShapeTest, InfoWithPolymorphismShouldBeCorrect)
{
    Shape *s1 = new Triangle(*v, *u);
    Shape *s2 = new Rectangle(*k, *l);
    Shape *s3 = new Circle(*r);
    ASSERT_EQ("Triangle (Vector ((5.00, 8.00), (8.00, 11.00)), Vector ((5.00, 8.00), (10.00, 8.00)))", s1->info());
    ASSERT_EQ("Rectangle (Vector ((20.00, 13.00), (16.00, 14.00)), Vector ((16.00, 14.00), (15.00, 10.00)))", s2->info());
    ASSERT_EQ("Circle (Vector ((14.00, 2.00), (18.00, -4.00)))", s3->info());
    delete s1;
    delete s2;
    delete s3;
}