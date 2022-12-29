#pragma once

#include "../../src/graphics/sdl/sdl.h"

class MockSDLRenderer : public SDL
{
private:
    bool _isInitCalled = false;
    int _width, _height;
    bool _isRenderPresentCalled = false;
    double *_drawCircleCalledArgs;
    double *_drawLinesCalledPoints;
    double _drawLinesCalledSize;

public:
    MockSDLRenderer()
    {
        _drawCircleCalledArgs = new double[3];
    }

    ~MockSDLRenderer()
    {
        delete[] _drawCircleCalledArgs;
    }

    void init(int width, int height) override
    {
        _isInitCalled = true;
        _width = width;
        _height = height;
    };

    void renderDrawLines(double *points, int size) override
    {
        _drawLinesCalledPoints = points;
        _drawLinesCalledSize = size;
    };

    void renderDrawCircle(double centreX, double centreY, double radius) override
    {
        _drawCircleCalledArgs[0] = centreX;
        _drawCircleCalledArgs[1] = centreY;
        _drawCircleCalledArgs[2] = radius;
    };

    void renderPresent() override
    {
        _isRenderPresentCalled = true;
    };

    void destroy() override{};

    bool isInitCalled()
    {
        return _isInitCalled;
    }

    int initWidth()
    {
        return _width;
    }

    int initHeight()
    {
        return _height;
    }

    bool isRenderPresentCalled()
    {
        return _isRenderPresentCalled;
    }

    const double *renderDrawCircleCalledArgs()
    {
        return _drawCircleCalledArgs;
    }

    const double *renderDrawLinesCalledPoints()
    {
        return _drawLinesCalledPoints;
    }

    double renderDrawLinesCalledSize()
    {
        return _drawLinesCalledSize;
    }
};
