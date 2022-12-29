#pragma once

#include <string>
#include <set>
#include "shape.h"
#include "two_dimensional_vector.h"
#include "./iterator/factory/iterator_factory.h"
#include "./visitor/shape_visitor.h"

class Rectangle : public Shape
{
private:
    TwoDimensionalVector _lengthVec;
    TwoDimensionalVector _widthVec;

public:
    Rectangle(TwoDimensionalVector lengthVec, TwoDimensionalVector widthVec) : _lengthVec(lengthVec), _widthVec(widthVec)
    {
        if (_lengthVec.a() == _widthVec.a() ||
            _lengthVec.b() == _widthVec.b() ||
            _lengthVec.b() == _widthVec.a() ||
            _lengthVec.a() == _widthVec.b())
        {
            if (lengthVec.dot(widthVec) != 0)
            {
                throw std::string("Two vectors should be orthogonal.");
            }
        }
        else
        {
            throw std::string("Two vectors should be connected.");
        }
    }
    ~Rectangle() {}

    double length() const
    {
        return _lengthVec.length();
    }

    double width() const
    {
        return _lengthVec.length();
    }

    double area() const override
    {
        return _lengthVec.length() * _widthVec.length();
    }

    double perimeter() const override
    {
        return (_lengthVec.length() + _widthVec.length()) * 2;
    }

    std::string info() const override
    {
        return "Rectangle (" + _lengthVec.info() + ", " + _widthVec.info() + ")";
    }

    Iterator *createIterator(IteratorFactory *factory) override
    {
        return factory->createIterator();
    }

    Point findFourthVertex(TwoDimensionalVector vec1, TwoDimensionalVector vec2)
    {
        if (vec1.a() == vec2.a())
        {
            Point A = vec1.b();
            Point B = vec2.b();
            Point C = vec1.a();
            return Point(
                A.x() + B.x() - C.x(),
                A.y() + B.y() - C.y());
        }
        else if (vec1.b() == vec2.b())
        {
            Point A = vec1.a();
            Point B = vec2.a();
            Point C = vec1.b();
            return Point(
                A.x() + B.x() - C.x(),
                A.y() + B.y() - C.y());
        }
        else if (vec1.b() == vec2.a())
        {
            Point A = vec1.a();
            Point B = vec2.b();
            Point C = vec1.b();
            return Point(
                A.x() + B.x() - C.x(),
                A.y() + B.y() - C.y());
        }
        else // if (vec1.a() == vec2.b())
        {
            Point A = vec1.b();
            Point B = vec2.a();
            Point C = vec1.a();
            return Point(
                A.x() + B.x() - C.x(),
                A.y() + B.y() - C.y());
        }
    }

    std::set<Point> getPoints() override
    {
        std::set<Point> points = {
            _lengthVec.a(), _lengthVec.b(),
            _widthVec.a(), _widthVec.b(),
            this->findFourthVertex(_lengthVec, _widthVec)};
        return points;
    }

    void accept(ShapeVisitor *visitor) override
    {
        visitor->visitRectangle(this);
    }

    void move(double deltaX, double deltaY) override
    {
        _lengthVec.move(deltaX, deltaY);
        _widthVec.move(deltaX, deltaY);
    }
};