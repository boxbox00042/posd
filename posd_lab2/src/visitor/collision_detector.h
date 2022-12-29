#pragma once

#include "shape_visitor.h"
#include "../circle.h"
#include "../triangle.h"
#include "../rectangle.h"
#include "../compound_shape.h"
#include "../bounding_box.h"
#include "../iterator/factory/bfs_iterator_factory.h"
#include <vector>

class CollisionDetector : public ShapeVisitor
{
private:
    std::vector<Shape *> _collideResult;
    BoundingBox *_targetBoundingBox;

public:
    CollisionDetector(Shape *shape)
    {
        _targetBoundingBox = new BoundingBox(shape->getPoints());
    }

    ~CollisionDetector()
    {
        delete _targetBoundingBox;
    }

    void visitCircle(Circle *circle) override
    {
        BoundingBox *box = new BoundingBox(circle->getPoints());
        if (box->collide(_targetBoundingBox))
        {
            _collideResult.push_back(circle);
        }
        delete box;
    }

    void visitTriangle(Triangle *triangle) override
    {
        BoundingBox *box = new BoundingBox(triangle->getPoints());
        if (box->collide(_targetBoundingBox))
        {
            _collideResult.push_back(triangle);
        }
        delete box;
    }

    void visitRectangle(Rectangle *rectangle) override
    {
        BoundingBox *box = new BoundingBox(rectangle->getPoints());
        if (box->collide(_targetBoundingBox))
        {
            _collideResult.push_back(rectangle);
        }
        delete box;
    }

    void visitCompoundShape(CompoundShape *compoundShape) override
    {
        BoundingBox *box = new BoundingBox(compoundShape->getPoints());
        if (box->collide(_targetBoundingBox))
        {
            Iterator *it = compoundShape->createIterator(
                IteratorFactory::getInstance("List"));
            for (it->first(); !it->isDone(); it->next())
            {
                it->currentItem()->accept(this);
            }
            delete it;
        }
        delete box;
    }

    std::vector<Shape *> collidedShapes() const
    {
        return _collideResult;
    }
};