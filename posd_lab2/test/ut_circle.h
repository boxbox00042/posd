#include <cmath>
#include "../src/circle.h"
#include "../src/iterator/iterator.h"
#include "../src/iterator/factory/dfs_iterator_factory.h"
#include "../src/iterator/factory/bfs_iterator_factory.h"

class CircleTest : public ::testing::Test
{
protected:
    Point *K, *L;
    TwoDimensionalVector *r;

    void SetUp() override
    {
        K = new Point(14, 2);
        L = new Point(18, -4);
        r = new TwoDimensionalVector(*K, *L);
    }

    void TearDown() override
    {
        delete K;
        delete L;
        delete r;
    }
};

TEST_F(CircleTest, LegalCircle)
{
    ASSERT_NO_THROW(Circle cir(*r));
}

TEST_F(CircleTest, RadiusShouldBeCorrect)
{
    ASSERT_NEAR(7.2111, Circle(*r).radius(), 0.001);
}

TEST_F(CircleTest, AreaShouldBeCorrect)
{
    ASSERT_NEAR(pow(7.2111, 2) * M_PI, Circle(*r).area(), 0.001);
}

TEST_F(CircleTest, PerimeterShouldBeCorrect)
{
    ASSERT_NEAR(2 * M_PI * 7.2111, Circle(*r).perimeter(), 0.001);
}

TEST_F(CircleTest, InfoShouldBeCorrect)
{
    Circle cir(*r);
    ASSERT_EQ("Circle (Vector ((14.00, 2.00), (18.00, -4.00)))", cir.info());
}

// hw 2
TEST_F(CircleTest, AddShapeShouldThrowException)
{
    Circle cir(*r);
    Shape *s = new Circle(*r);

    ASSERT_ANY_THROW(cir.addShape(s));

    delete s;
}

TEST_F(CircleTest, DeleteShapeShouldThrowException)
{
    Circle cir(*r);
    Shape *s = new Circle(*r);

    ASSERT_ANY_THROW(cir.deleteShape(s));

    delete s;
}

TEST_F(CircleTest, CurrentItemOfDFSIteratorShouldThrowException)
{
    Circle cir(*r);
    Iterator *it = cir.createIterator(IteratorFactory::getInstance("DFS"));
    ASSERT_ANY_THROW(it->currentItem());

    delete it;
}

TEST_F(CircleTest, IsDoneOfDFSIteratorShouldReturnTrue)
{
    Circle cir(*r);
    Iterator *it = cir.createIterator(IteratorFactory::getInstance("DFS"));
    ASSERT_TRUE(it->isDone());

    delete it;
}

TEST_F(CircleTest, CurrentItemOfBFSIteratorShouldThrowException)
{
    Circle cir(*r);
    Iterator *it = cir.createIterator(IteratorFactory::getInstance("BFS"));
    ASSERT_ANY_THROW(it->currentItem());

    delete it;
}

TEST_F(CircleTest, IsDoneOfBFSIteratorShouldReturnTrue)
{
    Circle cir(*r);
    Iterator *it = cir.createIterator(IteratorFactory::getInstance("BFS"));
    ASSERT_TRUE(it->isDone());

    delete it;
}

// hw 3
TEST_F(CircleTest, getPointsShouldBeCorrect)
{
    double radius = r->length();
    Circle cir(*r);
    std::set<Point> points = cir.getPoints();
    ASSERT_TRUE(points.size() == 2);
    Point pMax(K->x() + radius, K->y() + radius);
    Point pMin(K->x() - radius, K->y() - radius);
    ASSERT_TRUE(points.find(pMax) != points.end());
    ASSERT_TRUE(points.find(pMin) != points.end());
    Point lowerright(K->x() + radius, K->y() - radius);
    Point upperleft(K->x() - radius, K->y() + radius);
    ASSERT_TRUE(points.find(lowerright) == points.end());
    ASSERT_TRUE(points.find(upperleft) == points.end());
}

// hw6
TEST_F(CircleTest, MoveShouldBeCorrect)
{
    Circle cir(*r);
    cir.move(10, 10);
    ASSERT_NEAR(pow(7.2111, 2) * M_PI, Circle(*r).area(), 0.001);
    ASSERT_EQ("Circle (Vector ((24.00, 12.00), (28.00, 6.00)))", cir.info());
}