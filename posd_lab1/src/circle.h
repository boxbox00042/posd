#pragma once

#include <string>
#include <cmath>
#include <set>
#include "two_dimensional_vector.h"
#include "shape.h"
#include "./iterator/factory/iterator_factory.h"
#include "./visitor/shape_visitor.h"

class Circle : public Shape
{
private:
    TwoDimensionalVector *_radiusVec;

public:
    Circle(TwoDimensionalVector *radiusVec) : _radiusVec(radiusVec) {}
    ~Circle() {}

    double radius() const
    {
        return _radiusVec->length();
    }

    double area() const override
    {
        return pow(radius(), 2) * M_PI;
    }

    double perimeter() const override
    {
        return 2 * M_PI * radius();
    }

    std::string info() const override
    {
        return "Circle (" + _radiusVec->info() + ")";
    }

    Iterator *createIterator(IteratorFactory *factory) override
    {
        return factory->createIterator();
    }

    std::set<const Point *> getPoints() override
    {
        std::set<const Point *> points = {
            new Point(
                _radiusVec->a()->x() + radius(),
                _radiusVec->a()->y() + radius()),
            new Point(
                _radiusVec->a()->x() - radius(),
                _radiusVec->a()->y() - radius())};
        return points;
    }

    void accept(ShapeVisitor *visitor) override
    {
        visitor->visitCircle(this);
    }
};