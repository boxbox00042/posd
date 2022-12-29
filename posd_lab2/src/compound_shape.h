#pragma once

#include "shape.h"
#include "./iterator/factory/iterator_factory.h"
#include "./iterator/factory/dfs_iterator_factory.h"
#include "./visitor/shape_visitor.h"

#include <list>
#include <set>

class CompoundShape : public Shape
{
private:
    std::list<Shape *> _shapes;

public:
    CompoundShape(){}
    CompoundShape(Shape **shapes, int size) : _shapes(shapes, shapes + size) {}

    ~CompoundShape()
    {
        for (std::list<Shape *>::iterator it = _shapes.begin(); it != _shapes.end(); ++it)
        {
            delete *it;
        }
        _shapes.clear();
    }

    double area() const override
    {
        double result = 0;
        for (std::list<Shape *>::const_iterator it = _shapes.begin(); it != _shapes.end(); ++it)
        {
            result += (*it)->area();
        }
        return result;
    }

    double perimeter() const override
    {
        double result = 0;
        for (std::list<Shape *>::const_iterator it = _shapes.begin(); it != _shapes.end(); ++it)
        {
            result += (*it)->perimeter();
        }
        return result;
    }

    std::string info() const override
    {
        std::string result = "CompoundShape (";
        for (std::list<Shape *>::const_iterator it = _shapes.begin(); it != _shapes.end(); ++it)
        {
            result += (*it)->info();
            if (std::next(it) != _shapes.end())
            {
                result += ", ";
            }
        }
        result += ")";
        return result;
    }

    Iterator *createIterator(IteratorFactory *factory) override
    {
        return factory->createIterator(_shapes.begin(), _shapes.end());
    }

    void addShape(Shape *shape) override
    {
        _shapes.push_back(shape);
    }

    void deleteShape(Shape *shape) override
    {
        for (std::list<Shape *>::const_iterator it = _shapes.begin(); it != _shapes.end(); ++it)
        {
            if (*it == shape)
            {
                delete *it;
                _shapes.erase(it);
                break;
            }
            else
            {
                Iterator *shapeIt = (*it)->createIterator(
                    IteratorFactory::getInstance("DFS"));
                if (!shapeIt->isDone())
                    (*it)->deleteShape(shape);
                delete shapeIt;
            }
        }
    }

    std::set<Point> getPoints() override
    {
        std::set<Point> points;
        for (std::list<Shape *>::const_iterator it = _shapes.begin(); it != _shapes.end(); ++it)
        {
            std::set<Point> s_points = (*it)->getPoints();
            points.insert(s_points.begin(), s_points.end());
        }
        return points;
    }

    void accept(ShapeVisitor *visitor) override
    {
        visitor->visitCompoundShape(this);
    }

    void move(double deltaX, double deltaY) override
    {
        for (std::list<Shape *>::const_iterator it = _shapes.begin(); it != _shapes.end(); ++it)
            (*it)->move(deltaX, deltaY);
    }
};