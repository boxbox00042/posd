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
        u = new TwoDimensionalVector(A, B);
        v = new TwoDimensionalVector(A, C);
        w = new TwoDimensionalVector(C, B);
        e = new TwoDimensionalVector(A, D);
        f = new TwoDimensionalVector(E, F);
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
    ASSERT_NO_THROW(Triangle(v, u));
    ASSERT_NO_THROW(Triangle(v, e));
    ASSERT_NO_THROW(Triangle(v, w));
    ASSERT_NO_THROW(Triangle(w, u));
}

TEST_F(TriangleTest, IllegalTriangle)
{
    // two vectors do not connect to each other
    ASSERT_ANY_THROW(Triangle(v, f));
    ASSERT_ANY_THROW(Triangle(f, v));
    ASSERT_ANY_THROW(Triangle(w, e));
    ASSERT_ANY_THROW(Triangle(f, w));
    // parallel vectors
    ASSERT_ANY_THROW(Triangle(e, u));
}

TEST_F(TriangleTest, AreaShouldBeCorrect)
{
    ASSERT_NEAR(7.5, Triangle(v, u).area(), 0.001);
    ASSERT_NEAR(7.5, Triangle(u, v).area(), 0.001);
    ASSERT_NEAR(7.5, Triangle(w, u).area(), 0.001);
    ASSERT_NEAR(7.5, Triangle(v, w).area(), 0.001);
}

TEST_F(TriangleTest, PerimeterShouldBeCorrect)
{
    ASSERT_NEAR(12.8481, Triangle(v, u).perimeter(), 0.001);
    ASSERT_NEAR(12.8481, Triangle(u, v).perimeter(), 0.001);
    ASSERT_NEAR(12.8481, Triangle(w, u).perimeter(), 0.001);
    ASSERT_NEAR(12.8481, Triangle(v, w).perimeter(), 0.001);
}

TEST_F(TriangleTest, InfoShouldBeCorrect)
{
    Triangle tri(v, u);
    ASSERT_EQ("Triangle (Vector ((5.00, 8.00), (8.00, 11.00)), Vector ((5.00, 8.00), (10.00, 8.00)))", tri.info());
}

// hw 2
TEST_F(TriangleTest, AddShapeShouldThrowException)
{
    Triangle tri(v, u);
    Shape *s = new Triangle(v, u);

    ASSERT_ANY_THROW(tri.addShape(s));

    delete s;
}

TEST_F(TriangleTest, DeleteShapeShouldThrowException)
{
    Triangle tri(v, u);
    Shape *s = new Triangle(v, u);

    ASSERT_ANY_THROW(tri.deleteShape(s));

    delete s;
}

TEST_F(TriangleTest, CurrentItemOfDFSIteratorShouldThrowException)
{
    Triangle tri(v, u);
    Iterator *it = tri.createIterator(new DFSIteratorFactory());
    ASSERT_ANY_THROW(it->currentItem());

    delete it;
}

TEST_F(TriangleTest, IsDoneOfDFSIteratorShouldReturnTrue)
{
    Triangle tri(v, u);
    Iterator *it = tri.createIterator(new DFSIteratorFactory());
    ASSERT_TRUE(it->isDone());

    delete it;
}

TEST_F(TriangleTest, CurrentItemOfBFSIteratorShouldThrowException)
{
    Triangle tri(v, u);
    Iterator *it = tri.createIterator(new BFSIteratorFactory());
    ASSERT_ANY_THROW(it->currentItem());

    delete it;
}

TEST_F(TriangleTest, IsDoneOfBFSIteratorShouldReturnTrue)
{
    Triangle tri(v, u);
    Iterator *it = tri.createIterator(new BFSIteratorFactory());
    ASSERT_TRUE(it->isDone());

    delete it;
}

// hw 3
TEST_F(TriangleTest, GetPointsShouldBeCorrect)
{
    Triangle tri(v, u);
    std::set<const Point *> points = tri.getPoints();
    std::set<const Point *, bool (*)(const Point *, const Point *)> actualPoints(
        points.begin(), points.end(),
        [](const Point *p1, const Point *p2) -> bool
        {
            return p1->x() < p2->x() || (p1->x() == p2->x() && p1->y() < p2->y());
        }
    );
    ASSERT_TRUE(actualPoints.size() == 3);
    ASSERT_TRUE(actualPoints.find(A) != actualPoints.end());
    ASSERT_TRUE(actualPoints.find(B) != actualPoints.end());
    ASSERT_TRUE(actualPoints.find(C) != actualPoints.end());
}
