#include "../../src/shape.h"
#include "../../src/iterator/factory/illegal_node_iterator_factory.h"
#include "../../src/builder/aabb_tree_builder.h"

class IllegalNodeIteratorTest : public ::testing::Test
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

TEST_F(IllegalNodeIteratorTest, NullptrShouldBeReturnedWhenRootIsALeaf)
{
    AABBTreeBuilder *builder = new AABBTreeBuilder();
    builder->insertTriangle(A, B, C);
    Shape *root = builder->getTree();
    Iterator *it = root->createIterator(new IllegalNodeIteratorFactory(root));
    ASSERT_TRUE(it->isDone());
    ASSERT_ANY_THROW(it->currentItem());
    ASSERT_ANY_THROW(it->next());
}

TEST_F(IllegalNodeIteratorTest, NullptrShouldBeReturnedWhenOneLevelAABBTreeHasNoIllegalNodes)
{
    AABBTreeBuilder *builder = new AABBTreeBuilder();
    builder->insertTriangle(A, B, C);
    builder->insertCircle(D, E);
    Shape *root = builder->getTree();
    Iterator *it = root->createIterator(new IllegalNodeIteratorFactory(root));
    ASSERT_TRUE(it->isDone());
    ASSERT_ANY_THROW(it->currentItem());
    ASSERT_ANY_THROW(it->next());
}

TEST_F(IllegalNodeIteratorTest, ACompoundShapeShouldBeReturnedWhenAABBTreeIsASingleCompoundShape)
{
    Shape *ss[] = {};
    Shape *root = new CompoundShape(ss, 0);
    Iterator *it = root->createIterator(new IllegalNodeIteratorFactory(root));
    ASSERT_FALSE(it->isDone());
    ASSERT_TRUE(dynamic_cast<CompoundShape *>(it->currentItem()) != nullptr);
    ASSERT_NO_THROW(it->next());
    ASSERT_TRUE(it->isDone());
    ASSERT_ANY_THROW(it->currentItem());
    ASSERT_ANY_THROW(it->next());
}

TEST_F(IllegalNodeIteratorTest, NullptrShouldBeReturnedWhenTheCompoundShapeHasALeafShapeAsItsChild)
{
    AABBTreeBuilder *builder = new AABBTreeBuilder();
    builder->insertTriangle(A, B, C);
    builder->insertCircle(D, E);
    Shape *root = builder->getTree();
    Shape *tri = root->createIterator(new ListIteratorFactory())->currentItem();
    root->deleteShape(tri);

    Iterator *it = root->createIterator(new IllegalNodeIteratorFactory(root));
    ASSERT_TRUE(it->isDone());
    ASSERT_ANY_THROW(it->currentItem());
    ASSERT_ANY_THROW(it->next());
}

TEST_F(IllegalNodeIteratorTest, ACompoundShapeShouldBeReturnedWhenItHasOnlyOneChildThatIsAlsoACompoundShape)
{
    AABBTreeBuilder *builder = new AABBTreeBuilder();
    builder->insertTriangle(J, K, L);  // tri2
    builder->insertRectangle(G, F, H); // rect2
    builder->insertCircle(D, E);       // cir1
    Shape *root = builder->getTree();
    Shape *tri2 = root->createIterator(new ListIteratorFactory())->currentItem();
    root->deleteShape(tri2);

    Iterator *it = root->createIterator(new IllegalNodeIteratorFactory(root));
    ASSERT_FALSE(it->isDone());
    ASSERT_TRUE(dynamic_cast<CompoundShape *>(it->currentItem()) != nullptr);
    ASSERT_NO_THROW(it->next());
    ASSERT_TRUE(it->isDone());
    ASSERT_ANY_THROW(it->currentItem());
    ASSERT_ANY_THROW(it->next());
}

TEST_F(IllegalNodeIteratorTest, AllCompoundShapesShouldBeReturnedWhenAllLeafShapesAreRemoved)
{
    AABBTreeBuilder *builder = new AABBTreeBuilder();
    builder->insertTriangle(J, K, L);  // tri2
    builder->insertRectangle(G, F, H); // rect2
    builder->insertCircle(D, E);       // cir1
    Shape *root = builder->getTree();
    std::list<Shape *> leave;
    Iterator *rootIt = root->createIterator(new ListIteratorFactory());
    Shape *tri2 = rootIt->currentItem();
    leave.push_back(tri2);
    rootIt->next();
    for (Iterator *csChildIt = rootIt->currentItem()->createIterator(new ListIteratorFactory()); !csChildIt->isDone(); csChildIt->next())
    {
        leave.push_back(csChildIt->currentItem());
    }
    for (std::list<Shape *>::const_iterator it = leave.begin(); it != leave.end(); it++)
    {
        root->deleteShape(*it);
    }

    Iterator *it = root->createIterator(new IllegalNodeIteratorFactory(root));
    ASSERT_FALSE(it->isDone());
    ASSERT_TRUE(dynamic_cast<CompoundShape *>(it->currentItem()) != nullptr);
    ASSERT_NO_THROW(it->next());
    ASSERT_TRUE(dynamic_cast<CompoundShape *>(it->currentItem()) != nullptr);
    ASSERT_NO_THROW(it->next());
    ASSERT_TRUE(it->isDone());
    ASSERT_ANY_THROW(it->currentItem());
    ASSERT_ANY_THROW(it->next());
}