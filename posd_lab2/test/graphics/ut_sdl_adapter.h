#include "../../src/shape.h"
#include "../../src/rectangle.h"
#include "../../src/circle.h"
#include "../../src/triangle.h"
#include "../../src/compound_shape.h"
#include "../../src/graphics/sdl_adapter.h"
#include "mock_sdl_renderer.h"

class SDLAdapterTest : public ::testing::Test
{
protected:
    MockSDLRenderer *mockSDLRenderer;

    void SetUp() override
    {
        mockSDLRenderer = new MockSDLRenderer();
    }

    void TearDown() override
    {
        delete mockSDLRenderer;
    }
};

TEST_F(SDLAdapterTest, initShouldBeCalledWhenAdapterIsInitialized)
{
    Canvas *canvas = new SDLAdapter(1024, 768, mockSDLRenderer);
    ASSERT_TRUE(mockSDLRenderer->isInitCalled());
    delete canvas;
}

TEST_F(SDLAdapterTest, initCalledArgsShouldBeCorrect)
{
    Canvas *canvas = new SDLAdapter(1024, 768, mockSDLRenderer);
    ASSERT_EQ(1024, mockSDLRenderer->initWidth());
    ASSERT_EQ(768, mockSDLRenderer->initHeight());
    delete canvas;
}

TEST_F(SDLAdapterTest, widthAndHeightShouldBeGreaterThanZero)
{

    ASSERT_ANY_THROW(SDLAdapter(0, 0, mockSDLRenderer));
    ASSERT_ANY_THROW(SDLAdapter(-1, 768, mockSDLRenderer));
    ASSERT_ANY_THROW(SDLAdapter(1024, 0, mockSDLRenderer));
    ASSERT_ANY_THROW(SDLAdapter(-1, -1, mockSDLRenderer));
}

TEST_F(SDLAdapterTest, renderDrawCircleCalledArgsShouldBeCorrect)
{
    Point Q(-3, -3), R(-2, -5);
    TwoDimensionalVector v(Q, R);
    Circle cir(v);
    Canvas *canvas = new SDLAdapter(1024, 768, mockSDLRenderer);
    canvas->drawCircle(&cir);
    const double *calledArgs = mockSDLRenderer->renderDrawCircleCalledArgs();
    ASSERT_NEAR(-3, calledArgs[0], 0.001);
    ASSERT_NEAR(-3, calledArgs[1], 0.001);
    ASSERT_NEAR(2.236, calledArgs[2], 0.001);
    delete canvas;
}

TEST_F(SDLAdapterTest, renderDrawLinesCalledArgsShouldBeCorrectForNonRotatedRect)
{

    Point M(2, -5), N(2, -7), O(4, -7), P(4, -5);
    TwoDimensionalVector a(M, P), b(P, O);
    Rectangle rect(a, b);
    Canvas *canvas = new SDLAdapter(600, 600, mockSDLRenderer);
    canvas->drawRectangle(&rect);
    double calledSize = mockSDLRenderer->renderDrawLinesCalledSize();
    ASSERT_EQ(8, calledSize);
    const double *calledPoints = mockSDLRenderer->renderDrawLinesCalledPoints();
    ASSERT_NEAR(2, calledPoints[0], 0.001);
    ASSERT_NEAR(-7, calledPoints[1], 0.001);
    ASSERT_NEAR(2, calledPoints[2], 0.001);
    ASSERT_NEAR(-5, calledPoints[3], 0.001);
    ASSERT_NEAR(4, calledPoints[4], 0.001);
    ASSERT_NEAR(-5, calledPoints[5], 0.001);
    ASSERT_NEAR(4, calledPoints[6], 0.001);
    ASSERT_NEAR(-7, calledPoints[7], 0.001);
    delete[] calledPoints;
    delete canvas;
}

TEST_F(SDLAdapterTest, renderDrawLinesCalledArgsShouldBeCorrectForRotatedRect1)
{
    Point G(-2, -11), H(-1, -13), F(0, -10), I(1, -12);
    TwoDimensionalVector m(F, G), n(H, G);
    Rectangle rect(m, n);
    Canvas *canvas = new SDLAdapter(600, 600, mockSDLRenderer);
    canvas->drawRectangle(&rect);
    double calledSize = mockSDLRenderer->renderDrawLinesCalledSize();
    ASSERT_EQ(8, calledSize);
    const double *calledPoints = mockSDLRenderer->renderDrawLinesCalledPoints();
    ASSERT_NEAR(-2, calledPoints[0], 0.001);
    ASSERT_NEAR(-11, calledPoints[1], 0.001);
    ASSERT_NEAR(-1, calledPoints[2], 0.001);
    ASSERT_NEAR(-13, calledPoints[3], 0.001);
    ASSERT_NEAR(1, calledPoints[4], 0.001);
    ASSERT_NEAR(-12, calledPoints[5], 0.001);
    ASSERT_NEAR(0, calledPoints[6], 0.001);
    ASSERT_NEAR(-10, calledPoints[7], 0.001);
    delete[] calledPoints;
    delete canvas;
}

TEST_F(SDLAdapterTest, renderDrawLinesCalledArgsShouldBeCorrectForRotatedRect2)
{
    Point Z(-2, 4), A(-3, 2), B(-1, 1), C(0, 3);
    TwoDimensionalVector m(A, Z), n(Z, C);
    Rectangle rect(m, n);
    Canvas *canvas = new SDLAdapter(1, 1, mockSDLRenderer);
    canvas->drawRectangle(&rect);
    double calledSize = mockSDLRenderer->renderDrawLinesCalledSize();
    ASSERT_EQ(8, calledSize);
    const double *calledPoints = mockSDLRenderer->renderDrawLinesCalledPoints();
    ASSERT_NEAR(-3, calledPoints[0], 0.001);
    ASSERT_NEAR(2, calledPoints[1], 0.001);
    ASSERT_NEAR(-2, calledPoints[2], 0.001);
    ASSERT_NEAR(4, calledPoints[3], 0.001);
    ASSERT_NEAR(0, calledPoints[4], 0.001);
    ASSERT_NEAR(3, calledPoints[5], 0.001);
    ASSERT_NEAR(-1, calledPoints[6], 0.001);
    ASSERT_NEAR(1, calledPoints[7], 0.001);
    delete[] calledPoints;
    delete canvas;
}

TEST_F(SDLAdapterTest, renderDrawLinesCalledArgsShouldBeCorrectForRotatedRect3)
{
    Point D(8, 2), E(7, 1), F(8, 0), G(9, 1);
    TwoDimensionalVector m(D, E), n(D, G);
    Rectangle rect(m, n);
    Canvas *canvas = new SDLAdapter(123, 654, mockSDLRenderer);
    canvas->drawRectangle(&rect);
    double calledSize = mockSDLRenderer->renderDrawLinesCalledSize();
    ASSERT_EQ(8, calledSize);
    const double *calledPoints = mockSDLRenderer->renderDrawLinesCalledPoints();
    ASSERT_NEAR(7, calledPoints[0], 0.001);
    ASSERT_NEAR(1, calledPoints[1], 0.001);
    ASSERT_NEAR(8, calledPoints[2], 0.001);
    ASSERT_NEAR(0, calledPoints[3], 0.001);
    ASSERT_NEAR(9, calledPoints[4], 0.001);
    ASSERT_NEAR(1, calledPoints[5], 0.001);
    ASSERT_NEAR(8, calledPoints[6], 0.001);
    ASSERT_NEAR(2, calledPoints[7], 0.001);
    delete[] calledPoints;
    delete canvas;
}

TEST_F(SDLAdapterTest, renderDrawLinesCalledArgsShouldBeCorrectForTriangle1)
{
    Point J(-6, -7), K(-7, -9), L(-4, -9);
    TwoDimensionalVector m(J, K), n(K, L);
    Triangle tri(m, n);
    Canvas *canvas = new SDLAdapter(1024, 768, mockSDLRenderer);
    canvas->drawTriangle(&tri);
    double calledSize = mockSDLRenderer->renderDrawLinesCalledSize();
    ASSERT_EQ(6, calledSize);
    const double *calledPoints = mockSDLRenderer->renderDrawLinesCalledPoints();
    ASSERT_NEAR(-7, calledPoints[0], 0.001);
    ASSERT_NEAR(-9, calledPoints[1], 0.001);
    ASSERT_NEAR(-6, calledPoints[2], 0.001);
    ASSERT_NEAR(-7, calledPoints[3], 0.001);
    ASSERT_NEAR(-4, calledPoints[4], 0.001);
    ASSERT_NEAR(-9, calledPoints[5], 0.001);
    delete[] calledPoints;
    delete canvas;
}

TEST_F(SDLAdapterTest, renderDrawLinesCalledArgsShouldBeCorrectForTriangle2)
{
    Point A(4, -2), B(6, -4), C(6, -8);
    TwoDimensionalVector m(A, B), n(B, C);
    Triangle tri(m, n);
    Canvas *canvas = new SDLAdapter(1024, 768, mockSDLRenderer);
    canvas->drawTriangle(&tri);
    double calledSize = mockSDLRenderer->renderDrawLinesCalledSize();
    ASSERT_EQ(6, calledSize);
    const double *calledPoints = mockSDLRenderer->renderDrawLinesCalledPoints();
    ASSERT_NEAR(4, calledPoints[0], 0.001);
    ASSERT_NEAR(-2, calledPoints[1], 0.001);
    ASSERT_NEAR(6, calledPoints[2], 0.001);
    ASSERT_NEAR(-8, calledPoints[3], 0.001);
    ASSERT_NEAR(6, calledPoints[4], 0.001);
    ASSERT_NEAR(-4, calledPoints[5], 0.001);
    delete[] calledPoints;
    delete canvas;
}

TEST_F(SDLAdapterTest, renderPresentShouldBeCalledWhenAdapterIsDisplayed)
{
    Canvas *canvas = new SDLAdapter(1024, 768, mockSDLRenderer);
    canvas->display();
    ASSERT_TRUE(mockSDLRenderer->isRenderPresentCalled());
    delete canvas;
}

// TEST_F(SDLAdapterTest, destroyShouldBeCalledWhenAdapterIsDeleted)
// {
//     Canvas *canvas = new SDLAdapter(1024, 768, mockSDLRenderer);
//     delete canvas;
//     ASSERT_TRUE(mockSDLRenderer->isDestroyCalled());
// }