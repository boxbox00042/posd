#pragma once

#include "./shape_visitor.h"
#include "../iterator/factory/list_iterator_factory.h"

class IllegalNodeChecker : public ShapeVisitor
{
private:
    bool _isIllegal;

public:
    void visitCircle(Circle *circle) override
    {
    }

    void visitTriangle(Triangle *triangle) override
    {
    }

    void visitRectangle(Rectangle *rectangle) override
    {
    }

    void visitCompoundShape(CompoundShape *compoundShape) override
    {
        _isIllegal = false;
        int size = 0;
        Shape *firstChild = nullptr;
        for (Iterator *it = compoundShape->createIterator(new ListIteratorFactory());
             !it->isDone(); it->next())
        {
            if (firstChild == nullptr)
                firstChild = it->currentItem();
            size++;
        }
        switch (size)
        {
        case 0:
            _isIllegal = true;
            break;
        case 1:
            if (dynamic_cast<CompoundShape *>(firstChild) != nullptr)
            {
                _isIllegal = true;
            }
            break;
        default:
            _isIllegal = false;
            break;
        }
    }

    bool isIllegal() const
    {
        return _isIllegal;
    }
};