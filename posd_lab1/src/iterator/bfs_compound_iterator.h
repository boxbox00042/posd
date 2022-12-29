#pragma once

#include "iterator.h"
#include "../shape.h"
#include "./factory/bfs_iterator_factory.h"
#include <queue>
#include <list>

template<class ForwardIterator>
class BFSCompoundIterator : public Iterator
{
private:
    std::queue<Shape*> _shapes;
public:
    BFSCompoundIterator(ForwardIterator begin, ForwardIterator end)
    {
        std::list<Iterator*> buffer;
        for(ForwardIterator it=begin; it!=end; it++)
        {
            _shapes.push(*it);
            buffer.push_back((*it)->createIterator(new BFSIteratorFactory()));
        }
        for(std::list<Iterator*>::const_iterator it = buffer.begin(); it!= buffer.end(); it++)
        {
            for(;!(*it)->isDone() ;(*it)->next())
            {
                _shapes.push((*it)->currentItem());
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