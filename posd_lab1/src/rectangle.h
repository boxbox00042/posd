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
    TwoDimensionalVector *_lengthVec;
    TwoDimensionalVector *_widthVec;

public:
    Rectangle(TwoDimensionalVector *lengthVec, TwoDimensionalVector *widthVec) : _lengthVec(lengthVec), _widthVec(widthVec)
    {
        if (lengthVec->a() == widthVec->a() ||
            lengthVec->b() == widthVec->b() ||
            lengthVec->b() == widthVec->a() ||
            lengthVec->a() == widthVec->b())
        {
            if (lengthVec->dot(widthVec) != 0)
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
        return _lengthVec->length();
    }

    double width() const
    {
        return _lengthVec->length();
    }

    double area() const override
    {
        return _lengthVec->length() * _widthVec->length();
    }

    double perimeter() const override
    {
        return (_lengthVec->length() + _widthVec->length()) * 2;
    }

    std::string info() const override
    {
        return "Rectangle (" + _lengthVec->info() + ", " + _widthVec->info() + ")";
    }

    Iterator *createIterator(IteratorFactory *factory) override
    {
        return factory->createIterator();
    }

    Point *findFourthVertex(TwoDimensionalVector *vec1, TwoDimensionalVector *vec2)
    {
        const Point *A, *B, *C;
        if (vec1->a() == vec2->a())
        {
            A = vec1->b();
            B = vec2->b();
            C = vec1->a();
        }
        else if (vec1->b() == vec2->b())
        {
            A = vec1->a();
            B = vec2->a();
            C = vec1->b();
        }
        else if (vec1->b() == vec2->a())
        {
            A = vec1->a();
            B = vec2->b();
            C = vec1->b();
        }
        else if (vec1->a() == vec2->b())
        {
            A = vec1->b();
            B = vec2->a();
            C = vec1->a();
        }
        return new Point(
            A->x() + B->x() - C->x(),
            A->y() + B->y() - C->y());
    }

    std::set<const Point *> getPoints() override
    {
        std::set<const Point *> points = {
            _lengthVec->a(),
            _lengthVec->b(),
            _widthVec->a(),
            _widthVec->b(),
            this->findFourthVertex(_lengthVec, _widthVec)
        };
        return points;
    }

    void accept(ShapeVisitor *visitor) override
    {
        visitor->visitRectangle(this);
    }
};