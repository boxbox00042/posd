#pragma once

#include "./iterator.h"
#include <queue>


template <class ForwardIterator>
class ListCompoundIterator : public Iterator
{
private:
    std::queue<Shape *> _shapes;

public:
    ListCompoundIterator(ForwardIterator begin, ForwardIterator end)
    {
        for (ForwardIterator it = begin; it != end; it++)
        {
            _shapes.push(*it);
        }
    }
    void first() override {}

    Shape *currentItem() const override
    {
        if (isDone())
        {
            throw "no current item";
        }
        return _shapes.front();
    }

    void next() override
    {
        if (isDone())
        {
            throw "no current item";
        }
        _shapes.pop();
    }

    bool isDone() const override
    {
        return _shapes.size() == 0;
    }
};
