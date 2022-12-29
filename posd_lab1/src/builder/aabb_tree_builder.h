#pragma once

#include "../shape.h"
#include "../triangle.h"
#include "../circle.h"
#include "../iterator/factory/list_iterator_factory.h"
#include "../visitor/closest_shape_finder.h"

class AABBTreeBuilder
{
private:
    Shape *_root = nullptr;
    void _insert(Shape *shape)
    {
        if (_root == nullptr)
        {
            _root = shape;
        }
        else
        {
            ClosestShapeFinder *finder = new ClosestShapeFinder(shape);
            _root->accept(finder);
            Shape *closest_shape = finder->getClosestShape();
            CompoundShape *parent = finder->getParent();
            if (parent == nullptr) // there is only one leaf shape in the tree
            {
                Shape *theOnlyShape = _root;
                Shape *ss[] = {theOnlyShape, shape};
                CompoundShape *cs = new CompoundShape(ss, 2);
                _root = cs;
            }
            else
            {
                int size = 0;
                for (Iterator *it = parent->createIterator(new ListIteratorFactory());
                     !it->isDone(); it->next())
                    size++;
                if (size < 2)
                {
                    parent->addShape(shape);
                }
                else
                {
                    Shape *ss[] = {closest_shape, shape};
                    parent->replace(
                        closest_shape,
                        new CompoundShape(ss, 2));
                }
            }

            delete finder;
        }
    }

public:
    void insertTriangle(const Point *common_point, const Point *v1_point, const Point *v2_point)
    {
        Shape *tri = new Triangle(
            new TwoDimensionalVector(common_point, v1_point),
            new TwoDimensionalVector(common_point, v2_point));
        _insert(tri);
    }

    void insertCircle(const Point *center, const Point *to_radius)
    {
        Shape *cir = new Circle(
            new TwoDimensionalVector(center, to_radius));
        _insert(cir);
    }

    void insertRectangle(const Point *common_point, const Point *v1_point, const Point *v2_point)
    {
        Shape *rect = new Rectangle(
            new TwoDimensionalVector(common_point, v1_point),
            new TwoDimensionalVector(common_point, v2_point));
        _insert(rect);
    }

    Shape *getTree() const
    {
        return _root;
    }
};