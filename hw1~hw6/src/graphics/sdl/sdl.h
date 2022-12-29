#pragma once

class SDL
{
public:
    virtual ~SDL() {};
    virtual void init(int width, int height) = 0;
    virtual void renderDrawLines(double *points, int size) = 0;
    virtual void renderDrawCircle(double centreX, double centreY, double radius) = 0;
    virtual void renderPresent() = 0;
    virtual void destroy() = 0;
};