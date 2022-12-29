#include "../src/circle.h"
#include "../src/rectangle.h"
#include "../src/compound_shape.h"
#include "../src/iterator/iterator.h"
#include "../src/iterator/factory/dfs_iterator_factory.h"
#include "../src/iterator/factory/bfs_iterator_factory.h"

class CompoundShapeTest : public ::testing::Test
{
protected:
    Point *p1, *p2, *p3, *p4;
    TwoDimensionalVector *vec1, *vec2, *vec3;
    Shape *cir1, *cir2, *rect;
    CompoundShape *cs1, *cs2, *cs3;

    void SetUp() override
    {
        p1 = new Point(0, 0);
        p2 = new Point(0, 5);
        p3 = new Point(5, 0);
        p4 = new Point(0, 3);

        vec1 = new TwoDimensionalVector(*p1, *p2);
        vec2 = new TwoDimensionalVector(*p1, *p3);
        vec3 = new TwoDimensionalVector(*p1, *p4);
        cir1 = new Circle(*vec1);
        cir2 = new Circle(*vec3);
        rect = new Rectangle(*vec1, *vec2);

        Shape *sp1[] = {cir1, rect};
        cs1 = new CompoundShape(sp1, 2);

        Shape *sp2[] = {cir2};
        cs2 = new CompoundShape(sp2, 1);

        Shape *sp3[] = {cs1, cs2};
        cs3 = new CompoundShape(sp3, 2);
    }

    void TearDown() override
    {
        delete cs3;
        delete p1;
        delete p2;
        delete p3;
        delete p4;
        delete vec1;
        delete vec2;
        delete vec3;
    }
};

TEST_F(CompoundShapeTest, ConstructorShouldBeCorrect)
{
    Shape *cir1 = new Circle(*vec1);
    Shape *cir2 = new Circle(*vec3);
    Shape *rect = new Rectangle(*vec1, *vec2);
    Shape *shapes[] = {cir1, rect, cir2};
    ASSERT_NO_THROW(CompoundShape cs(shapes, 3));
}

TEST_F(CompoundShapeTest, AreaShouldBeCalculatedCorrectly)
{
    ASSERT_NEAR(pow(5.0, 2) * M_PI + 25, cs1->area(), 0.001);
    ASSERT_NEAR(pow(3.0, 2) * M_PI + pow(5.0, 2) * M_PI + 25, cs3->area(), 0.001);
}

TEST_F(CompoundShapeTest, PerimeterShouldBeCalculatedCorrectly)
{
    ASSERT_NEAR(10 * M_PI + 20, cs1->perimeter(), 0.001);
    ASSERT_NEAR(10 * M_PI + 6 * M_PI + 20, cs3->perimeter(), 0.001);
}

TEST_F(CompoundShapeTest, InfoShouldBeCorrectly)
{
    std::string result = "CompoundShape (Circle (Vector ((0.00, 0.00), (0.00, 5.00))), Rectangle (Vector ((0.00, 0.00), (0.00, 5.00)), Vector ((0.00, 0.00), (5.00, 0.00))))";

    ASSERT_EQ(result, cs1->info());

    std::string result2 = "CompoundShape (CompoundShape (Circle (Vector ((0.00, 0.00), (0.00, 5.00))), Rectangle (Vector ((0.00, 0.00), (0.00, 5.00)), Vector ((0.00, 0.00), (5.00, 0.00)))), CompoundShape (Circle (Vector ((0.00, 0.00), (0.00, 3.00)))))";

    ASSERT_EQ(result2, cs3->info());
}

TEST_F(CompoundShapeTest, AddShapeCorrectly)
{
    Shape *shapes[] = {};
    CompoundShape *cs = new CompoundShape(shapes, 0);
    Circle *c1 = new Circle(*vec1);

    ASSERT_NO_THROW(cs->addShape(c1));

    Iterator *it = cs->createIterator(IteratorFactory::getInstance("DFS"));
    ASSERT_EQ(c1, it->currentItem());

    delete cs;
    delete it;
}

TEST_F(CompoundShapeTest, DeleteShapeCorrectly)
{
    Shape *shapes[] = {};
    CompoundShape *cs = new CompoundShape(shapes, 0);
    Circle *c1 = new Circle(*vec1);
    Circle *c2 = new Circle(*vec3);

    cs->addShape(c1);
    cs->addShape(c2);
    cs->deleteShape(c2);

    Iterator *it = cs->createIterator(IteratorFactory::getInstance("DFS"));
    ASSERT_EQ(c1, it->currentItem());

    delete cs;
    delete it;
}

TEST_F(CompoundShapeTest, DeleteInnerShapeCorrectly)
{
    Shape *shapes1[] = {};
    Shape *shapes2[] = {};
    CompoundShape *cShape = new CompoundShape(shapes1, 0);
    CompoundShape *cShape2 = new CompoundShape(shapes2, 0);
    Circle *c1 = new Circle(*vec1);
    Circle *c2 = new Circle(*vec3);
    Circle *c3 = new Circle(*vec3);

    cShape->addShape(c1);
    cShape->addShape(c2);
    cShape2->addShape(cShape);
    cShape2->addShape(c3);

    Iterator *it = cShape2->createIterator(IteratorFactory::getInstance("DFS"));

    ASSERT_NEAR(5 * 5 * M_PI + 3 * 3 * M_PI * 2, cShape2->area(), 0.001);
    cShape2->deleteShape(c2);
    ASSERT_NEAR(5 * 5 * M_PI + +3 * 3 * M_PI, cShape2->area(), 0.001);

    delete cShape2;
    delete it;
}

TEST_F(CompoundShapeTest, DFSIteratorShouldBeCorrect)
{
    Iterator *it;
    ASSERT_NO_THROW(it = cs3->createIterator(IteratorFactory::getInstance("DFS")));
    ASSERT_FALSE(it->isDone());

    ASSERT_NEAR(5 * 5 * M_PI + 25, it->currentItem()->area(), 0.001);
    ASSERT_NO_THROW(it->next());
    ASSERT_NEAR(5 * 5 * M_PI, it->currentItem()->area(), 0.001);
    ASSERT_NO_THROW(it->next());
    ASSERT_NEAR(25, it->currentItem()->area(), 0.001);
    ASSERT_NO_THROW(it->next());
    ASSERT_NEAR(3 * 3 * M_PI, it->currentItem()->area(), 0.001);
    ASSERT_NO_THROW(it->next());
    ASSERT_NEAR(3 * 3 * M_PI, it->currentItem()->area(), 0.001);

    ASSERT_NO_THROW(it->next());
    ASSERT_TRUE(it->isDone());

    delete it;
}

TEST_F(CompoundShapeTest, BFSIteratorShouldBeCorrect)
{
    Iterator *it;
    ASSERT_NO_THROW(it = cs3->createIterator(IteratorFactory::getInstance("BFS")));
    ASSERT_FALSE(it->isDone());

    ASSERT_NEAR(5 * 5 * M_PI + 25, it->currentItem()->area(), 0.001);
    ASSERT_NO_THROW(it->next());
    ASSERT_NEAR(3 * 3 * M_PI, it->currentItem()->area(), 0.001);
    ASSERT_NO_THROW(it->next());
    ASSERT_NEAR(5 * 5 * M_PI, it->currentItem()->area(), 0.001);
    ASSERT_NO_THROW(it->next());
    ASSERT_NEAR(25, it->currentItem()->area(), 0.001);
    ASSERT_NO_THROW(it->next());
    ASSERT_NEAR(3 * 3 * M_PI, it->currentItem()->area(), 0.001);

    ASSERT_NO_THROW(it->next());
    ASSERT_TRUE(it->isDone());

    delete it;
}

// hw 3
TEST_F(CompoundShapeTest, GetPointsShouldBeCorrect)
{
    std::set<Point> points = cs3->getPoints();
    std::set<Point, bool (*)(Point, Point)> actualPoints(
        points.begin(), points.end(),
        [](Point p1, Point p2) -> bool
        {
            return p1.x() < p2.x() || (p1.x() == p2.x() && p1.y() < p2.y());
        });
    Point pMax1(5, 5), pMin1(-5, -5), pMax2(3, 3), pMin2(-3, -3);
    ASSERT_TRUE(actualPoints.size() == 7);
    ASSERT_TRUE(actualPoints.find(*p1) != actualPoints.end());
    ASSERT_TRUE(actualPoints.find(*p2) != actualPoints.end());
    ASSERT_TRUE(actualPoints.find(*p3) != actualPoints.end());
    ASSERT_TRUE(actualPoints.find(pMax1) != actualPoints.end());
    ASSERT_TRUE(actualPoints.find(pMin1) != actualPoints.end());
    ASSERT_TRUE(actualPoints.find(pMax2) != actualPoints.end());
    ASSERT_TRUE(actualPoints.find(pMin2) != actualPoints.end());
}

// hw6
TEST_F(CompoundShapeTest, MoveShouldBeCorrect)
{
    cs1->move(-26.5, -17.8);
    ASSERT_EQ("CompoundShape (Circle (Vector ((-26.50, -17.80), (-26.50, -12.80))), Rectangle (Vector ((-26.50, -17.80), (-26.50, -12.80)), Vector ((-26.50, -17.80), (-21.50, -17.80))))", cs1->info());
}