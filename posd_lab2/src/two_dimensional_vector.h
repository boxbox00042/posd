#pragma once

#include <cmath>
#include "point.h"

class TwoDimensionalVector
{
private:
    Point _a;
    Point _b;

public:
    TwoDimensionalVector(Point a, Point b) : _a(a), _b(b) {}
    ~TwoDimensionalVector() {}

    Point a() const
    {
        return _a;
    }

    Point b() const
    {
        return _b;
    }

    double length() const
    {
        return sqrt(
            pow(_b.x() - _a.x(), 2) +
            pow(_b.y() - _a.y(), 2));
    }

    double dot(TwoDimensionalVector vec) const
    {
        return (_b.x() - _a.x()) * (vec.b().x() - vec.a().x()) +
               (_b.y() - _a.y()) * (vec.b().y() - vec.a().y());
    }

    double cross(TwoDimensionalVector vec) const
    {
        return (_b.x() - _a.x()) * (vec.b().y() - vec.a().y()) -
               (_b.y() - _a.y()) * (vec.b().x() - vec.a().x());
    }

    void move(double deltaX, double deltaY)
    {
        _a.move(deltaX, deltaY);
        _b.move(deltaX, deltaY);
    }

    std::string info() const
    {
        return "Vector (" + _a.info() + ", " + _b.info() + ")";
    }
};