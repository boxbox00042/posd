#include "../../src/shape.h"
#include "../../src/iterator/factory/list_iterator_factory.h"
#include "../../src/iterator/factory/bfs_iterator_factory.h"
#include "../../src/builder/aabb_tree_builder.h"

class AABBTreeBuilderTest : public ::testing::Test
{
protected:
    Point *A, *B, *C, *D,
        *E, *F, *G, *H,
        *J, *K, *L, *M,
        *N, *O;

    void SetUp()
    {
        A = new Point(4, -2);
        B = new Point(6, -4);
        C = new Point(6, -8);
        D = new Point(-1.5, -8);
        E = new Point(0, -8);
        F = new Point(0, -10);
        G = new Point(-2, -11);
        H = new Point(-1, -13);
        J = new Point(-6, -7);
        K = new Point(-7, -9);
        L = new Point(-4, -9);
        M = new Point(2, -5);
        N = new Point(2, -7);
        O = new Point(4, -7);
    }

    void TearDown()
    {
        delete A;
        delete B;
        delete C;
        delete D;
        delete E;
        delete F;
        delete G;
        delete H;
        delete J;
        delete K;
        delete L;
        delete M;
        delete O;
        delete N;
    }
};

TEST_F(AABBTreeBuilderTest, insertTriangleShouldBeCorrect)
{
    AABBTreeBuilder *builder = new AABBTreeBuilder();
    builder->insertTriangle(A, B, C);
    Shape *root = builder->getTree();
    ASSERT_NEAR(4, root->area(), 0.001);
}

TEST_F(AABBTreeBuilderTest, insertCircleOnTriangleShouldBeCorrect)
{
    AABBTreeBuilder *builder = new AABBTreeBuilder();
    builder->insertTriangle(A, B, C);
    builder->insertCircle(D, E);

    Shape *root = builder->getTree();
    Iterator *it = root->createIterator(new ListIteratorFactory());
    ASSERT_FALSE(it->isDone());
    ASSERT_NEAR(4, it->currentItem()->area(), 0.001);
    ASSERT_NO_THROW(it->next());
    ASSERT_NEAR(-1.5 * -1.5 * M_PI, it->currentItem()->area(), 0.001);
    ASSERT_NO_THROW(it->next());
    ASSERT_TRUE(it->isDone());
}

TEST_F(AABBTreeBuilderTest, insertTriangleOnCircleShouldBeCorrect)
{
    AABBTreeBuilder *builder = new AABBTreeBuilder();
    builder->insertCircle(D, E);
    builder->insertTriangle(A, B, C);

    Shape *root = builder->getTree();
    Iterator *it = root->createIterator(new ListIteratorFactory());
    ASSERT_FALSE(it->isDone());
    ASSERT_NEAR(-1.5 * -1.5 * M_PI, it->currentItem()->area(), 0.001);
    ASSERT_NO_THROW(it->next());
    ASSERT_NEAR(4, it->currentItem()->area(), 0.001);
    ASSERT_NO_THROW(it->next());
    ASSERT_TRUE(it->isDone());
}

TEST_F(AABBTreeBuilderTest, insertRectangleOnTriangleShouldBeCorrect)
{
    AABBTreeBuilder *builder = new AABBTreeBuilder();
    builder->insertTriangle(A, B, C);
    builder->insertRectangle(G, F, H);

    Shape *root = builder->getTree();
    Iterator *it = root->createIterator(new ListIteratorFactory());
    ASSERT_FALSE(it->isDone());
    ASSERT_NEAR(4, it->currentItem()->area(), 0.001);
    ASSERT_NO_THROW(it->next());
    ASSERT_NEAR(5, it->currentItem()->area(), 0.001);
    ASSERT_NO_THROW(it->next());
    ASSERT_TRUE(it->isDone());
}

TEST_F(AABBTreeBuilderTest, insertingShapesToConstructTwoLevelTreeShouldBeCorrect)
{
    AABBTreeBuilder *builder = new AABBTreeBuilder();
    builder->insertTriangle(A, B, C);  // tri1
    builder->insertRectangle(G, F, H); // rect2
    builder->insertRectangle(N, M, O); // rect1
    builder->insertCircle(D, E);       // cir1

    Shape *root = builder->getTree();
    ASSERT_TRUE(dynamic_cast<CompoundShape *>(root) != nullptr);
    Iterator *it = root->createIterator(new BFSIteratorFactory());
    ASSERT_FALSE(it->isDone());
    ASSERT_TRUE(dynamic_cast<CompoundShape *>(it->currentItem()) != nullptr);
    ASSERT_NO_THROW(it->next());
    ASSERT_TRUE(dynamic_cast<CompoundShape *>(it->currentItem()) != nullptr);
    ASSERT_NO_THROW(it->next());
    ASSERT_NEAR(4, it->currentItem()->area(), 0.001);
    ASSERT_TRUE(dynamic_cast<Triangle *>(it->currentItem()) != nullptr);
    ASSERT_NO_THROW(it->next());
    ASSERT_NEAR(4, it->currentItem()->area(), 0.001);
    ASSERT_TRUE(dynamic_cast<Rectangle *>(it->currentItem()) != nullptr);
    ASSERT_NO_THROW(it->next());
    ASSERT_NEAR(5, it->currentItem()->area(), 0.001);
    ASSERT_NO_THROW(it->next());
    ASSERT_NEAR(-1.5 * -1.5 * M_PI, it->currentItem()->area(), 0.001);
    ASSERT_FALSE(it->isDone());
    ASSERT_NO_THROW(it->next());
    ASSERT_TRUE(it->isDone());
    ASSERT_ANY_THROW(it->currentItem());
}

TEST_F(AABBTreeBuilderTest, insertingShapesToConstructThreeLevelTreeShouldBeCorrect)
{
    AABBTreeBuilder *builder = new AABBTreeBuilder();
    builder->insertTriangle(J, K, L);  // tri2
    builder->insertCircle(D, E);       // cir1
    builder->insertRectangle(G, F, H); // rect2
    builder->insertRectangle(N, M, O); // rect1

    Shape *root = builder->getTree();
    ASSERT_TRUE(dynamic_cast<CompoundShape *>(root) != nullptr);

    Iterator *it = root->createIterator(new BFSIteratorFactory());
    ASSERT_FALSE(it->isDone());

    ASSERT_NEAR(3, it->currentItem()->area(), 0.001);
    ASSERT_NO_THROW(it->next());
    ASSERT_TRUE(dynamic_cast<CompoundShape *>(it->currentItem()) != nullptr);
    ASSERT_NO_THROW(it->next());

    ASSERT_TRUE(dynamic_cast<CompoundShape *>(it->currentItem()) != nullptr);
    ASSERT_NO_THROW(it->next());
    ASSERT_NEAR(5, it->currentItem()->area(), 0.001);
    ASSERT_NO_THROW(it->next());

    ASSERT_NEAR(-1.5 * -1.5 * M_PI, it->currentItem()->area(), 0.001);
    ASSERT_NO_THROW(it->next());
    ASSERT_NEAR(4, it->currentItem()->area(), 0.001);
    ASSERT_TRUE(dynamic_cast<Rectangle *>(it->currentItem()) != nullptr);

    ASSERT_FALSE(it->isDone());
    ASSERT_NO_THROW(it->next());
    ASSERT_TRUE(it->isDone());
    ASSERT_ANY_THROW(it->currentItem());
}