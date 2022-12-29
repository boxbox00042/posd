#pragma once

#include <cmath>
#include "point.h"

class TwoDimensionalVector
{
private:
    const Point *_a;
    const Point *_b;

public:
    TwoDimensionalVector(const Point *a, const Point *b) : _a(a), _b(b) {}
    ~TwoDimensionalVector() {}

    const Point *a() const
    {
        return _a;
    }

    const Point *b() const
    {
        return _b;
    }

    double length() const
    {
        return sqrt(
            pow(_b->x() - _a->x(), 2) +
            pow(_b->y() - _a->y(), 2)
        );
    }

    double dot(const TwoDimensionalVector *vec) const
    {
        return (_b->x() - _a->x()) * (vec->b()->x() - vec->a()->x()) +
               (_b->y() - _a->y()) * (vec->b()->y() - vec->a()->y());
    }

    double cross(const TwoDimensionalVector *vec) const
    {
        return (_b->x() - _a->x()) * (vec->b()->y() - vec->a()->y()) -
               (_b->y() - _a->y()) * (vec->b()->x() - vec->a()->x());
    }

    std::string info() const
    {
        return "Vector (" + _a->info() + ", " + _b->info() + ")";
    }
};