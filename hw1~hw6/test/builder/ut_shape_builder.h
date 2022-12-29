#include "../../src/shape.h"
#include "../../src/builder/shape_builder.h"
#include "../../src/iterator/factory/bfs_iterator_factory.h"
#include <vector>

class ShapeBuilderTest : public ::testing::Test
{
protected:
    Point *A, *B, *C, *D, *E;

    ShapeBuilder *builder;

    void SetUp() override
    {
        A = new Point(0, 0);
        B = new Point(3, 0);
        C = new Point(0, 4);
        D = new Point(5, 0);
        E = new Point(0, 2);

        builder = new ShapeBuilder();
    }

    void TearDown() override
    {
        delete A;
        delete B;
        delete C;
        delete D;
        delete E;
        delete builder;
    }
};

TEST_F(ShapeBuilderTest, BuildCircleShouldBeCorrect)
{
    builder->buildCircle(*A, *B);
    std::vector<Shape*> result = builder->getResult();

    ASSERT_NEAR(9*M_PI, result.at(0)->area() , 0.001);
    delete *(result.begin());
}

TEST_F(ShapeBuilderTest, BuildTriangleShouldBeCorrect)
{
    builder->buildTriangle(*A, *B, *C);
    std::vector<Shape*> result = builder->getResult();

    ASSERT_NEAR(6, result.at(0)->area() , 0.001);
    delete *(result.begin());
}

TEST_F(ShapeBuilderTest, BuildRectangleShouldBeCorrect)
{
    builder->buildRectangle(*A, *D, *E);
    std::vector<Shape*> result = builder->getResult();

    ASSERT_NEAR(10, result.at(0)->area() , 0.001);
    delete *(result.begin());
}

TEST_F(ShapeBuilderTest, BuildSimpleCompoundShouldBeCorrect)
{
    builder->buildCompoundShape();
    builder->buildCircle(*A, *B);
    builder->buildRectangle(*A, *D, *E);
    builder->buildCompoundEnd();
    std::vector<Shape*> result = builder->getResult();

    ASSERT_NEAR(9*M_PI + 10, result.at(0)->area() , 0.001);
    delete *(result.begin());
}

TEST_F(ShapeBuilderTest, BuildComplexCompoundShouldBeCorrect)
{
    builder->buildCompoundShape();
    builder->buildCircle(*A, *B);
    builder->buildCompoundShape();
    builder->buildTriangle(*A, *B, *C);
    builder->buildRectangle(*A, *D, *E);
    builder->buildCompoundEnd();
    builder->buildCompoundEnd();
    std::vector<Shape*> result = builder->getResult();

    ASSERT_NEAR(9*M_PI + 6 + 10, result.at(0)->area() , 0.001);

    Iterator *it = result.at(0)->createIterator(IteratorFactory::getInstance("BFS"));
    ASSERT_FALSE(it->isDone());
    ASSERT_NEAR(9*M_PI, it->currentItem()->area() , 0.001);
    ASSERT_NO_THROW(it->next());
    ASSERT_NEAR(10 + 6, it->currentItem()->area() , 0.001);
    ASSERT_NO_THROW(it->next());
    ASSERT_NEAR(6, it->currentItem()->area() , 0.001);
    ASSERT_NO_THROW(it->next());
    ASSERT_NEAR(10, it->currentItem()->area() , 0.001);

    delete it;
    delete *(result.begin());
}

TEST_F(ShapeBuilderTest, BuildMultipleShapeShouldBeCorrect)
{
    builder->buildCircle(*A, *B);
    builder->buildTriangle(*A, *B, *C);
    std::vector<Shape*> result = builder->getResult();

    ASSERT_NEAR(9*M_PI, result.at(0)->area() , 0.001);
    ASSERT_NEAR(6, result.at(1)->area() , 0.001);
    delete *(result.begin());
    delete *(result.begin()+1);
}