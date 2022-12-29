#pragma once

#include "iterator.h"
#include "../shape.h"
#include "./factory/bfs_step_iterator_factory.h"
#include <queue>

template<class ForwardIterator>
class BFSStepCompoundIterator : public Iterator
{
private:
    ForwardIterator _begin;
    ForwardIterator _current;
    ForwardIterator _end;
    std::queue<Iterator *> _its;
    Iterator *_currentIt;

    void next_iterator() {
        while (_its.size() != 0)
        {
            _currentIt = _its.front();
            _its.pop();
            if (!_currentIt->isDone())
                break;
        }
    }

public:
    BFSStepCompoundIterator(ForwardIterator begin, ForwardIterator end): _begin(begin), _end(end)
    {
        this->first();
    }

    void first() override {
        _current = _begin;
        if (_current != _end)
            _its.push((*_current)->createIterator(
                new BFSStepIteratorFactory()
            ));
    }

    Shape* currentItem() const override
    {
        if (isDone())
        {
            throw std::string("no current item");
        }
        if (_current != _end)
        {
            return *_current;
        }
        else
        {
            return _currentIt->currentItem();
        }
    }

    void next() override
    {
        if (isDone())
        {
            throw "no more items";
        }
        if (_current != _end)
        {
            _current++;
            if (_current == _end)
            {
                next_iterator();
            }
            else
            {
                _its.push((*_current)->createIterator(
                    new BFSStepIteratorFactory()
                ));
            }
        }
        else
        {
            _currentIt->next();
            if (_currentIt->isDone())
            {
                next_iterator();
            }
        }
    }

    bool isDone() const override
    {
        if (_begin == _end) {
            return true;
        } else {
            return _current == _end && _its.size() == 0 && _currentIt->isDone();
        }
    }
};