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
    TwoDimensionalVector _v1;
    TwoDimensionalVector _v2;

public:
    Triangle(TwoDimensionalVector v1, TwoDimensionalVector v2) : _v1(v1), _v2(v2)
    {
        if (v1.a() == v2.a() ||
            v1.b() == v2.b() ||
            v1.b() == v2.a() ||
            v1.a() == v2.b())
        {
            if (v1.cross(v2) == 0)
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
        return abs(_v1.cross(_v2)) / 2;
    }

    double perimeter() const override
    {
        double thirdLength = 0;
        if (_v1.a() == _v2.a())
        {
            thirdLength = TwoDimensionalVector(_v1.b(), _v2.b()).length();
        }
        else if (_v1.b() == _v2.b())
        {
            thirdLength = TwoDimensionalVector(_v1.a(), _v2.a()).length();
        }
        else if (_v1.b() == _v2.a())
        {
            thirdLength = TwoDimensionalVector(_v1.a(), _v2.b()).length();
        }
        else if (_v1.a() == _v2.b())
        {
            thirdLength = TwoDimensionalVector(_v1.b(), _v2.a()).length();
        }
        return _v1.length() + _v2.length() + thirdLength;
    }

    std::string info() const override
    {
        return "Triangle (" + _v1.info() + ", " + _v2.info() + ")";
    }

    Iterator *createIterator(IteratorFactory *factory) override
    {
        return factory->createIterator();
    }

    std::set<Point> getPoints() override
    {
        std::set<Point> points = {
            _v1.a(), _v1.b(),
            _v2.a(), _v2.b()};
        return points;
    }

    void accept(ShapeVisitor *visitor) override
    {
        visitor->visitTriangle(this);
    }

    void move(double deltaX, double deltaY) override
    {
        _v1.move(deltaX, deltaY);
        _v2.move(deltaX, deltaY);
    }
};