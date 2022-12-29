#pragma once

#include "./canvas.h"
#include "./sdl/sdl.h"
#include "../circle.h"
#include "../triangle.h"
#include "../rectangle.h"
#include <set>

class SDLAdapter : public Canvas
{
private:
    SDL *_sdl;

public:
    SDLAdapter(int width, int height, SDL *sdl) : _sdl(sdl)
    {
        if (width <= 0 || height <= 0)
        {
            throw "The width and height should be greater than 0.";
        }
        _sdl->init(width, height);
    };

    void drawCircle(Circle *cir) override
    {
        std::set<Point> points = cir->getPoints();
        const Point &p1 = *std::next(points.begin(), 0);
        const Point &p2 = *std::next(points.begin(), 1);
        double x = (p1.x() + p2.x()) / 2;
        double y = (p1.y() + p2.y()) / 2;
        double radius = cir->radius();
        _sdl->renderDrawCircle(x, y, radius);
    };

    void drawTriangle(Triangle *tri) override
    {
        std::set<Point> points = tri->getPoints();
        double *pValues = new double[6];
        int i = 0;
        for (std::set<Point>::iterator it = points.begin(); it != points.end(); it++)
        {
            pValues[i] = (*it).x();
            pValues[i + 1] = (*it).y();
            i += 2;
        }
        _sdl->renderDrawLines(pValues, 6);
    };

    void drawRectangle(Rectangle *rect) override
    {
        std::set<Point> points = rect->getPoints();
        double *pValues = new double[8];
        pValues[0] = (*std::next(points.begin(), 0)).x();
        pValues[1] = (*std::next(points.begin(), 0)).y();

        pValues[2] = (*std::next(points.begin(), 1)).x();
        pValues[3] = (*std::next(points.begin(), 1)).y();

        pValues[4] = (*std::next(points.begin(), 3)).x();
        pValues[5] = (*std::next(points.begin(), 3)).y();

        pValues[6] = (*std::next(points.begin(), 2)).x();
        pValues[7] = (*std::next(points.begin(), 2)).y();
        _sdl->renderDrawLines(pValues, 8);
    };

    void display() override
    {
        _sdl->renderPresent();
    }
};
