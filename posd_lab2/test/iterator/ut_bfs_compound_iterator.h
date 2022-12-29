#include "../../src/shape.h"
#include "../../src/rectangle.h"
#include "../../src/compound_shape.h"
#include "../../src/iterator/iterator.h"
#include "../../src/iterator/factory/bfs_iterator_factory.h"

class BFSCompoundIteratorTest : public ::testing::Test
{
protected:
    Point *p1, *p2, *p3, *p4;
    TwoDimensionalVector *vec1, *vec2, *vec3;
    Shape *cir1, *cir2, *rect;
    CompoundShape *cs1, *cs2, *cs3;
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

        Shape *sp1[] = {cir1, rect};
        cs1 = new CompoundShape(sp1, 2);

        Shape *sp2[] = {cir2, cs1};
        cs2 = new CompoundShape(sp2, 2);

        it = cs2->createIterator(IteratorFactory::getInstance("BFS"));
    }

    void TearDown() override
    {
        delete cs2;
        delete p1;
        delete p2;
        delete p3;
        delete p4;
        delete vec1;
        delete vec2;
        delete vec3;
        delete it;
    }
};

TEST_F(BFSCompoundIteratorTest, CurrentItemShouldBeCorrect)
{
    ASSERT_NEAR(3 * 3 * M_PI, it->currentItem()->area(), 0.001);
}

TEST_F(BFSCompoundIteratorTest, NextShouldBeCorrect)
{
    it->next();
    ASSERT_NEAR(5 * 5 * M_PI + 25, it->currentItem()->area(), 0.001);
}

TEST_F(BFSCompoundIteratorTest, IsDoneShouldBeCorrect)
{
    it->next();
    it->next();
    it->next();
    it->next();

    ASSERT_TRUE(it->isDone());
}

TEST_F(BFSCompoundIteratorTest, CurrentItemShouldThrowExceptionWhenIsDone)
{
    it->next();
    it->next();
    it->next();
    it->next();

    ASSERT_ANY_THROW(it->next());
}

TEST_F(BFSCompoundIteratorTest, NextShouldThrowExceptionWhenIsDone)
{
    it->next();
    it->next();
    it->next();
    it->next();

    ASSERT_ANY_THROW(it->currentItem());
}

TEST_F(BFSCompoundIteratorTest, BFSOrderShouldBeCorrectIfNoChildrenInCompound)
{
    Shape *sps[] = {};
    Shape *cs = new CompoundShape(sps, 0);
    Iterator *it = cs->createIterator(IteratorFactory::getInstance("BFS"));
    ASSERT_TRUE(it->isDone());
    ASSERT_ANY_THROW(it->currentItem());
    ASSERT_ANY_THROW(it->next());
    delete it;
    delete cs;
}

TEST_F(BFSCompoundIteratorTest, BFSOrderShouldBeCorrectIfACircleInCompound)
{
    Shape *cir = new Circle(*vec1);
    Shape *sps[] = {cir};
    Shape *cs = new CompoundShape(sps, 1);
    Iterator *it = cs->createIterator(IteratorFactory::getInstance("BFS"));
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ(it->currentItem(), cir);
    ASSERT_NO_THROW(it->next());
    ASSERT_TRUE(it->isDone());
    ASSERT_ANY_THROW(it->currentItem());
    delete it;
    delete cs;
}

TEST_F(BFSCompoundIteratorTest, BFSOrderShouldBeCorrectWithMultipleCompoundShapes)
{
    Shape *sps1[] = {};
    Shape *sps2[] = {};
    Shape *cs1 = new CompoundShape(sps1, 0);
    Shape *cs2 = new CompoundShape(sps2, 0);
    Shape *sps3[] = {cs1, cs2};
    Shape *cs3 = new CompoundShape(sps3, 2);
    Shape *sps4[] = {cs3};
    Shape *cs4 = new CompoundShape(sps4, 1);
    Iterator *it = cs4->createIterator(IteratorFactory::getInstance("BFS"));
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ(it->currentItem(), cs3);
    ASSERT_EQ(it->currentItem(), cs3);
    ASSERT_NO_THROW(it->next());

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ(it->currentItem(), cs1);
    ASSERT_EQ(it->currentItem(), cs1);
    ASSERT_NO_THROW(it->next());

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ(it->currentItem(), cs2);
    ASSERT_EQ(it->currentItem(), cs2);
    ASSERT_NO_THROW(it->next());

    ASSERT_TRUE(it->isDone());
    ASSERT_ANY_THROW(it->next());
    ASSERT_ANY_THROW(it->currentItem());

    delete it;
    delete cs4;
}

TEST_F(BFSCompoundIteratorTest, BFSOrderShouldBeCorrectWithComplicatedTreeStructure)
{
    Shape *cir1 = new Circle(*vec1);
    Shape *cir2 = new Circle(*vec2);
    Shape *cir3 = new Circle(*vec3);
    TwoDimensionalVector vec4(*p2, *p3);
    Shape *cir4 = new Circle(vec4);
    Shape *sps1[] = {cir1};
    Shape *cs1 = new CompoundShape(sps1, 1);
    Shape *sps2[] = {cs1, cir2};
    Shape *cs2 = new CompoundShape(sps2, 2);
    Shape *sps3[] = {cir3, cs2};
    Shape *cs3 = new CompoundShape(sps3, 2);
    Shape *sps4[] = {cs3, cir4};
    Shape *cs4 = new CompoundShape(sps4, 2);
    Iterator *it = cs4->createIterator(IteratorFactory::getInstance("BFS"));
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ(it->currentItem(), cs3);
    ASSERT_EQ(it->currentItem(), cs3);
    ASSERT_NO_THROW(it->next());
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ(it->currentItem(), cir4);
    ASSERT_EQ(it->currentItem(), cir4);
    ASSERT_NO_THROW(it->next());

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ(it->currentItem(), cir3);
    ASSERT_EQ(it->currentItem(), cir3);
    ASSERT_NO_THROW(it->next());
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ(it->currentItem(), cs2);
    ASSERT_EQ(it->currentItem(), cs2);
    ASSERT_NO_THROW(it->next());

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ(it->currentItem(), cs1);
    ASSERT_EQ(it->currentItem(), cs1);
    ASSERT_NO_THROW(it->next());

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ(it->currentItem(), cir2);
    ASSERT_EQ(it->currentItem(), cir2);
    ASSERT_NO_THROW(it->next());

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ(it->currentItem(), cir1);
    ASSERT_EQ(it->currentItem(), cir1);
    ASSERT_NO_THROW(it->next());

    ASSERT_TRUE(it->isDone());
    ASSERT_ANY_THROW(it->next());
    ASSERT_ANY_THROW(it->currentItem());

    delete it;
    delete cs4;
}