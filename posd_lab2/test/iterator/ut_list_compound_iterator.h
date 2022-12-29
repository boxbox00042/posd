#include "../../src/shape.h"
#include "../../src/circle.h"
#include "../../src/rectangle.h"
#include "../../src/compound_shape.h"
#include "../../src/iterator/list_compound_iterator.h"
#include "../../src/iterator/factory/list_iterator_factory.h"

class ListCompoundIteratorTest : public ::testing::Test
{
protected:
    Point *p1, *p2, *p3, *p4;
    TwoDimensionalVector *vec1, *vec2, *vec3;
    Shape *cir1, *cir2, *rect;
    CompoundShape *cs1, *cs2;
    Iterator *it;

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

        Shape *shapes1[] = {cir1, rect};
        cs1 = new CompoundShape(shapes1, 2);

        Shape *shapes2[] = {cir2, cs1};
        cs2 = new CompoundShape(shapes2, 2);

        it = cs1->createIterator(IteratorFactory::getInstance("List"));
    }

    void TearDown() override
    {
        delete it;
        delete cs2;
        delete p1;
        delete p2;
        delete p3;
        delete p4;
        delete vec1;
        delete vec2;
        delete vec3;
    }
};

TEST_F(ListCompoundIteratorTest, CurrentItemShouldBeCorrect)
{
    ASSERT_EQ(cir1, it->currentItem());
    ASSERT_EQ(cir1, it->currentItem());
}

TEST_F(ListCompoundIteratorTest, NextShouldBeCorrect)
{
    ASSERT_EQ(cir1, it->currentItem());
    ASSERT_NO_THROW(it->next());
    ASSERT_EQ(rect, it->currentItem());
}

TEST_F(ListCompoundIteratorTest, IsDoneShouldBeCorrect)
{
    ASSERT_FALSE(it->isDone());
    ASSERT_NO_THROW(it->next());
    ASSERT_FALSE(it->isDone());
    ASSERT_NO_THROW(it->next());
    ASSERT_ANY_THROW(it->currentItem());
    ASSERT_ANY_THROW(it->next());
    ASSERT_TRUE(it->isDone());
}

TEST_F(ListCompoundIteratorTest, DeeperShapesShouldNotBeReturned)
{
    Iterator *lit = cs2->createIterator(IteratorFactory::getInstance("List"));
    ASSERT_EQ(cir2, lit->currentItem());
    ASSERT_NO_THROW(lit->next());
    ASSERT_EQ(cs1, lit->currentItem());
    ASSERT_NO_THROW(lit->next());
    ASSERT_TRUE(lit->isDone());
    ASSERT_ANY_THROW(lit->next());
    ASSERT_ANY_THROW(lit->currentItem());

    delete lit;
}