#pragma once

#include <string>
#include <set>
#include "shape.h"
#include "two_dimensional_vector.h"
#include "./iterator/factory/iterator_factory.h"
#include "./visitor/shape_visitor.h"

class Triangle : public Shape
{
private:
    TwoDimensionalVector *_v1;
    TwoDimensionalVector *_v2;

public:
    Triangle(TwoDimensionalVector *v1, TwoDimensionalVector *v2) : _v1(v1), _v2(v2)
    {
        if (v1->a() == v2->a() || v1->b() == v2->b() || v1->b() == v2->a() || v1->a() == v2->b())
        {
            if (v1->cross(v2) == 0)
            {
                throw std::string("Two vectors should not be parallel.");
            }
        }
        else
        {
            throw std::string("Two vectors should be connected.");
        }
    }
    ~Triangle() {}

    double area() const override
    {
        return abs(_v1->cross(_v2)) / 2;
    }

    double perimeter() const override
    {
        const Point *p1, *p2;
        if (_v1->a() == _v2->a())
        {
            p1 = _v1->b();
            p2 = _v2->b();
        }
        else if (_v1->b() == _v2->b())
        {
            p1 = _v1->a();
            p2 = _v2->a();
        }
        else if (_v1->b() == _v2->a())
        {
            p1 = _v1->a();
            p2 = _v2->b();
        }
        else if (_v1->a() == _v2->b())
        {
            p1 = _v2->a();
            p2 = _v1->b();
        }
        TwoDimensionalVector *v3 = new TwoDimensionalVector(p1, p2);
        return _v1->length() + _v2->length() + v3->length();
    }

    std::string info() const override
    {
        return "Triangle (" + _v1->info() + ", " + _v2->info() + ")";
    }

    Iterator *createIterator(IteratorFactory *factory) override
    {
        return factory->createIterator();
    }

    std::set<const Point *> getPoints() override
    {
        std::set<const Point *> points = {
            _v1->a(),
            _v1->b(),
            _v2->a(),
            _v2->b()
        };
        return points;
    }

    void accept(ShapeVisitor *visitor) override
    {
        visitor->visitTriangle(this);
    }
};