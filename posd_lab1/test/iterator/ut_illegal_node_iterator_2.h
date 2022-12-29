#include "../../src/shape.h"
#include "../../src/iterator/factory/illegal_node_iterator_factory.h"

class IllegalNodeIteratorTest2 : public ::testing::Test
{
protected:
    Point *A, *B, *C, *D,
        *E, *F, *G, *H,
        *J, *K, *L, *M,
        *N, *O;

    TwoDimensionalVector *vec1, *vec2, *vec3, *vec4, *vec5, *vec6, *vec7;

    Shape *tri1, *tri2, *cir1, *rect1;

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

        vec1 = new TwoDimensionalVector(A, B);
        vec2 = new TwoDimensionalVector(A, C);
        vec3 = new TwoDimensionalVector(D, E);
        vec4 = new TwoDimensionalVector(J, K);
        vec5 = new TwoDimensionalVector(J, L);
        vec6 = new TwoDimensionalVector(G, F);
        vec7 = new TwoDimensionalVector(G, H);

        tri1 = new Triangle(vec1, vec2);
        tri2 = new Triangle(vec4, vec5);
        cir1 = new Circle(vec3);
        rect1 = new Rectangle(vec6, vec7);
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
        delete vec1;
        delete vec2;
        delete vec3;
        delete vec4;
        delete vec5;
        delete vec6;
        delete vec7;
    }
};

TEST_F(IllegalNodeIteratorTest2, NullptrShouldBeReturnedWhenRootIsALeaf)
{ 
    Shape *root = new Triangle(vec1, vec2);
    Iterator *it = root->createIterator(new IllegalNodeIteratorFactory(root));
    ASSERT_TRUE(it->isDone());
    ASSERT_ANY_THROW(it->currentItem());
    ASSERT_ANY_THROW(it->next());
}

TEST_F(IllegalNodeIteratorTest2, NullptrShouldBeReturnedWhenOneLevelAABBTreeHasNoIllegalNodes)
{
    Shape *shapes[] = {tri1, cir1};
    Shape *root = new CompoundShape(shapes, 2);
    Iterator *it = root->createIterator(new IllegalNodeIteratorFactory(root));
    ASSERT_TRUE(it->isDone());
    ASSERT_ANY_THROW(it->currentItem());
    ASSERT_ANY_THROW(it->next());
}

TEST_F(IllegalNodeIteratorTest2, ACompoundShapeShouldBeReturnedWhenAABBTreeIsASingleCompoundShape)
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

TEST_F(IllegalNodeIteratorTest2, NullptrShouldBeReturnedWhenTheCompoundShapeHasALeafShapeAsItsChild)
{
    Shape *shapes[] = {tri1, cir1};
    Shape *root = new CompoundShape(shapes, 2);
    Shape *tri = root->createIterator(new ListIteratorFactory())->currentItem();
    root->deleteShape(tri);

    Iterator *it = root->createIterator(new IllegalNodeIteratorFactory(root));
    ASSERT_TRUE(it->isDone());
    ASSERT_ANY_THROW(it->currentItem());
    ASSERT_ANY_THROW(it->next());
}

TEST_F(IllegalNodeIteratorTest2, ACompoundShapeShouldBeReturnedWhenItHasOnlyOneChildThatIsAlsoACompoundShape)
{
    Shape *shapes[] = {tri2, cir1};
    Shape *cs = new CompoundShape(shapes, 2);
    Shape *shapes2[] = {tri1, cs};
    Shape *root = new CompoundShape(shapes2, 2);
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

TEST_F(IllegalNodeIteratorTest2, AllCompoundShapesShouldBeReturnedWhenAllLeafShapesAreRemoved)
{
    Shape *shapes[] = {tri2, cir1};
    Shape *cs = new CompoundShape(shapes, 2);
    Shape *shapes2[] = {tri1, cs};
    Shape *root = new CompoundShape(shapes2, 2);
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