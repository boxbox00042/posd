#include "../src/triangle.h"
#include "../src/iterator/factory/dfs_iterator_factory.h"
#include "../src/iterator/factory/bfs_iterator_factory.h"

class TriangleTest : public ::testing::Test
{
protected:
    Point *A, *B, *C, *D, *E, *F;
    TwoDimensionalVector *u, *v, *w, *e, *f;
    void SetUp() override
    {

        A = new Point(5, 8);
        B = new Point(10, 8);
        C = new Point(8, 11);
        D = new Point(7, 8);
        E = new Point(5, 11);
        F = new Point(6, 12);
        u = new TwoDimensionalVector(*A, *B);
        v = new TwoDimensionalVector(*A, *C);
        w = new TwoDimensionalVector(*C, *B);
        e = new TwoDimensionalVector(*A, *D);
        f = new TwoDimensionalVector(*E, *F);
    }

    void TearDown() override
    {
        delete A;
        delete B;
        delete C;
        delete D;
        delete E;
        delete F;
        delete u;
        delete v;
        delete w;
        delete e;
        delete f;
    }
};

TEST_F(TriangleTest, LegalTriangle)
{
    ASSERT_NO_THROW(Triangle(*v, *u));
    ASSERT_NO_THROW(Triangle(*v, *e));
    ASSERT_NO_THROW(Triangle(*v, *w));
    ASSERT_NO_THROW(Triangle(*w, *u));
}

TEST_F(TriangleTest, IllegalTriangle)
{
    // two vectors do not connect to each other
    ASSERT_ANY_THROW(Triangle(*v, *f));
    ASSERT_ANY_THROW(Triangle(*f, *v));
    ASSERT_ANY_THROW(Triangle(*w, *e));
    ASSERT_ANY_THROW(Triangle(*f, *w));
    // parallel vectors
    ASSERT_ANY_THROW(Triangle(*e, *u));
}

TEST_F(TriangleTest, AreaShouldBeCorrect)
{
    ASSERT_NEAR(7.5, Triangle(*v, *u).area(), 0.001);
    ASSERT_NEAR(7.5, Triangle(*u, *v).area(), 0.001);
    ASSERT_NEAR(7.5, Triangle(*w, *u).area(), 0.001);
    ASSERT_NEAR(7.5, Triangle(*v, *w).area(), 0.001);
}

TEST_F(TriangleTest, PerimeterShouldBeCorrect)
{
    ASSERT_NEAR(12.8481, Triangle(*v, *u).perimeter(), 0.001);
    ASSERT_NEAR(12.8481, Triangle(*u, *v).perimeter(), 0.001);
    ASSERT_NEAR(12.8481, Triangle(*w, *u).perimeter(), 0.001);
    ASSERT_NEAR(12.8481, Triangle(*v, *w).perimeter(), 0.001);
}

TEST_F(TriangleTest, InfoShouldBeCorrect)
{
    Triangle tri(*v, *u);
    ASSERT_EQ("Triangle (Vector ((5.00, 8.00), (8.00, 11.00)), Vector ((5.00, 8.00), (10.00, 8.00)))", tri.info());
}

// hw 2
TEST_F(TriangleTest, AddShapeShouldThrowException)
{
    Triangle tri(*v, *u);
    Shape *s = new Triangle(*v, *u);

    ASSERT_ANY_THROW(tri.addShape(s));

    delete s;
}

TEST_F(TriangleTest, DeleteShapeShouldThrowException)
{
    Triangle tri(*v, *u);
    Shape *s = new Triangle(*v, *u);

    ASSERT_ANY_THROW(tri.deleteShape(s));

    delete s;
}

TEST_F(TriangleTest, CurrentItemOfDFSIteratorShouldThrowException)
{
    Triangle tri(*v, *u);
    Iterator *it = tri.createIterator(IteratorFactory::getInstance("DFS"));
    ASSERT_ANY_THROW(it->currentItem());

    delete it;
}

TEST_F(TriangleTest, IsDoneOfDFSIteratorShouldReturnTrue)
{
    Triangle tri(*v, *u);
    Iterator *it = tri.createIterator(IteratorFactory::getInstance("DFS"));
    ASSERT_TRUE(it->isDone());

    delete it;
}

TEST_F(TriangleTest, CurrentItemOfBFSIteratorShouldThrowException)
{
    Triangle tri(*v, *u);
    Iterator *it = tri.createIterator(IteratorFactory::getInstance("BFS"));
    ASSERT_ANY_THROW(it->currentItem());

    delete it;
}

TEST_F(TriangleTest, IsDoneOfBFSIteratorShouldReturnTrue)
{
    Triangle tri(*v, *u);
    Iterator *it = tri.createIterator(IteratorFactory::getInstance("BFS"));
    ASSERT_TRUE(it->isDone());

    delete it;
}

// hw 3
TEST_F(TriangleTest, GetPointsShouldBeCorrect)
{
    Triangle tri(*v, *u);
    std::set<Point> points = tri.getPoints();
    ASSERT_TRUE(points.size() == 3);
    ASSERT_TRUE(points.find(*A) != points.end());
    ASSERT_TRUE(points.find(*B) != points.end());
    ASSERT_TRUE(points.find(*C) != points.end());
}

// hw6
TEST_F(TriangleTest, MoveShouldBeCorrect)
{
    Triangle tri(*v, *u);
    tri.move(6.9, -8.1);
    ASSERT_NEAR(7.5, tri.area(), 0.001);
    ASSERT_EQ("Triangle (Vector ((11.90, -0.10), (14.90, 2.90)), Vector ((11.90, -0.10), (16.90, -0.10)))", tri.info());
}