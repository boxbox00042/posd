#pragma once

#include "iterator.h"
#include "../shape.h"
#include "./factory/dfs_iterator_factory.h"
#include <queue>


template<class ForwardIterator>
class DFSCompoundIterator : public Iterator
{
private:
    std::queue<Shape*> _shapes;
public:
    DFSCompoundIterator(ForwardIterator begin, ForwardIterator end)
    {
        for(ForwardIterator it=begin; it!=end; it++)
        {
            Iterator *itt = (*it)->createIterator(new DFSIteratorFactory());
            if(!itt->isDone())
            {
                _shapes.push(*it);
                for(itt;!itt->isDone();itt->next())
                {
                    _shapes.push(itt->currentItem());
                }
            }
            else
            {
                _shapes.push(*it);
            }
        }
    }

    void first() override {}

    Shape* currentItem() const override
    {
        if(isDone())
        {
            throw "no current item";
        }
        return _shapes.front();
    }

    void next() override
    {
        if(isDone())
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