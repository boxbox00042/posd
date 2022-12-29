#pragma once

#include "../shape.h"
#include "../compound_shape.h"
#include "./shape_visitor.h"
#include "../bounding_box.h"
#include "../iterator/factory/list_iterator_factory.h"
#include <stack>

class ClosestShapeFinder : public ShapeVisitor
{
private:
    CompoundShape *_parent = nullptr;
    std::stack<CompoundShape *> _candidateParent;
    Shape *_closestShape = nullptr;
    BoundingBox *_targetBoundingBox;
    double _minimumDistance = DBL_MAX;

public:
    ClosestShapeFinder(Shape *shape)
    {
        _targetBoundingBox = new BoundingBox(shape->getPoints());
    }

    void visitCircle(Circle *circle) override
    {
        BoundingBox *box = new BoundingBox(circle->getPoints());
        double dist = box->distance(_targetBoundingBox);
        if (dist < _minimumDistance)
        {
            _closestShape = circle;
            _minimumDistance = dist;
            if (_candidateParent.size())
                _parent = _candidateParent.top();
        }
        delete box;
    }

    void visitTriangle(Triangle *triangle) override
    {
        BoundingBox *box = new BoundingBox(triangle->getPoints());
        double dist = box->distance(_targetBoundingBox);
        if (dist < _minimumDistance)
        {
            _closestShape = triangle;
            _minimumDistance = dist;
            if (_candidateParent.size())
                _parent = _candidateParent.top();
        }
        delete box;
    }

    void visitRectangle(Rectangle *rectangle) override
    {
        BoundingBox *box = new BoundingBox(rectangle->getPoints());
        double dist = box->distance(_targetBoundingBox);
        if (dist < _minimumDistance)
        {
            _closestShape = rectangle;
            _minimumDistance = dist;
            if (_candidateParent.size())
                _parent = _candidateParent.top();
        }
        delete box;
    }

    void visitCompoundShape(CompoundShape *compoundShape) override
    {
        _candidateParent.push(compoundShape);
        Iterator *it = compoundShape->createIterator(new ListIteratorFactory());
        for (; !it->isDone(); it->next())
        {
            it->currentItem()->accept(this);
        }
        _candidateParent.pop();
    }

    Shape *getClosestShape() const
    {
        return _closestShape;
    }

    CompoundShape *getParent() const
    {
        return _parent;
    }
};