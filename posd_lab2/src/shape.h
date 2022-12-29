#pragma once

#include <string>
#include <set>

class Iterator;
class Point;
class ShapeVisitor;
class IteratorFactory;

class Shape
{
public:
    virtual ~Shape() {}
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual std::string info() const = 0;
    virtual Iterator* createIterator(IteratorFactory * factory) = 0;
    virtual std::set<Point> getPoints() = 0;
    virtual void accept(ShapeVisitor* visitor) = 0;
    virtual void move(double deltaX, double deltaY) = 0;

    virtual void addShape(Shape* shape)
    {
        throw "can't add shape";
    }

    virtual void deleteShape(Shape* shape)
    {
        throw "can't add shape";
    }
};
