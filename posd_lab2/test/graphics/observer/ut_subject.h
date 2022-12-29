#include "../../../src/graphics/observer/subject.h"

#include "../../../src/two_dimensional_vector.h"
#include "../../../src/shape.h"
#include "../../../src/triangle.h"
#include "../../../src/rectangle.h"
#include "../../../src/circle.h"

class SubjectTest : public ::testing::Test
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

TEST_F(SubjectTest, attachShouldBeCorrect)
{
    Shape *s1 = new Triangle(*v, *u);
    Shape *s2 = new Rectangle(*k, *l);
    Shape *s3 = new Circle(*r);

   // Drawing *p = new Drawing(shapes);
   // std::vector<Shapes *> p1 =  p->shapes();
    //ASSERT_NEAR(7.5, s1->area(), 0.001);
    //ASSERT_NEAR(17, s2->area(), 0.001);
  //  ASSERT_NEAR(pow(7.2111, 2) * M_PI, s3->area(), 0.001);
    delete s1;
    delete s2;
    delete s3;
}
TEST_F(SubjectTest, attachShouldBeCorrectForMutipleObservers)
{
    Shape *s1 = new Triangle(*v, *u);
    Shape *s2 = new Rectangle(*k, *l);
    Shape *s3 = new Circle(*r);

   // Drawing *p = new Drawing(shapes);
   // std::vector<Shapes *> p1 =  p->shapes();
    //ASSERT_NEAR(7.5, s1->area(), 0.001);
    //ASSERT_NEAR(17, s2->area(), 0.001);
  //  ASSERT_NEAR(pow(7.2111, 2) * M_PI, s3->area(), 0.001);
    delete s1;
    delete s2;
    delete s3;
}
TEST_F(SubjectTest, notifyShouldBeCorrect)
{
    Shape *s1 = new Triangle(*v, *u);
    Shape *s2 = new Rectangle(*k, *l);
    Shape *s3 = new Circle(*r);

   // Drawing *p = new Drawing(shapes);
   // std::vector<Shapes *> p1 =  p->shapes();
    //ASSERT_NEAR(7.5, s1->area(), 0.001);
    //ASSERT_NEAR(17, s2->area(), 0.001);
  //  ASSERT_NEAR(pow(7.2111, 2) * M_PI, s3->area(), 0.001);
    delete s1;
    delete s2;
    delete s3;
}
TEST_F(SubjectTest, notifyShouldBeCorrectForMutipleObservers)
{
    Shape *s1 = new Triangle(*v, *u);
    Shape *s2 = new Rectangle(*k, *l);
    Shape *s3 = new Circle(*r);

   // Drawing *p = new Drawing(shapes);
   // std::vector<Shapes *> p1 =  p->shapes();
    //ASSERT_NEAR(7.5, s1->area(), 0.001);
    //ASSERT_NEAR(17, s2->area(), 0.001);
  //  ASSERT_NEAR(pow(7.2111, 2) * M_PI, s3->area(), 0.001);
    delete s1;
    delete s2;
    delete s3;
}
TEST_F(SubjectTest, detachShouldBeCorrectForMutipleObserver)
{
    Shape *s1 = new Triangle(*v, *u);
    Shape *s2 = new Rectangle(*k, *l);
    Shape *s3 = new Circle(*r);

   // Drawing *p = new Drawing(shapes);
   // std::vector<Shapes *> p1 =  p->shapes();
    //ASSERT_NEAR(7.5, s1->area(), 0.001);
    //ASSERT_NEAR(17, s2->area(), 0.001);
  //  ASSERT_NEAR(pow(7.2111, 2) * M_PI, s3->area(), 0.001);
    delete s1;
    delete s2;
    delete s3;
}
TEST_F(SubjectTest, AnExceptionShouldBeThrewWhenDetachingNonExistentObserver )
{
    Shape *s1 = new Triangle(*v, *u);
    Shape *s2 = new Rectangle(*k, *l);
    Shape *s3 = new Circle(*r);

   // Drawing *p = new Drawing(shapes);
   // std::vector<Shapes *> p1 =  p->shapes();
    //ASSERT_NEAR(7.5, s1->area(), 0.001);
    //ASSERT_NEAR(17, s2->area(), 0.001);
  //  ASSERT_NEAR(pow(7.2111, 2) * M_PI, s3->area(), 0.001);
    delete s1;
    delete s2;
    delete s3;
}
TEST_F(SubjectTest, detachShouldBeCorrect)
{
    Shape *s1 = new Triangle(*v, *u);
    Shape *s2 = new Rectangle(*k, *l);
    Shape *s3 = new Circle(*r);

   // Drawing *p = new Drawing(shapes);
   // std::vector<Shapes *> p1 =  p->shapes();
    //ASSERT_NEAR(7.5, s1->area(), 0.001);
    //ASSERT_NEAR(17, s2->area(), 0.001);
  //  ASSERT_NEAR(pow(7.2111, 2) * M_PI, s3->area(), 0.001);
    delete s1;
    delete s2;
    delete s3;
}