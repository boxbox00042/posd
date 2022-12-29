#pragma once

#include "iterator.h"
#include "../shape.h"
#include "./factory/dfs_step_iterator_factory.h"
#include <queue>


template<class ForwardIterator>
class DFSStepCompoundIterator : public Iterator
{
private:
    ForwardIterator _begin;
    ForwardIterator _current;
    ForwardIterator _end;
    Iterator *_currentIt;
    bool _currentReturned, _currentItFirstCalled;

public:
    DFSStepCompoundIterator(ForwardIterator begin, ForwardIterator end): _begin(begin), _end(end)
    {
        this->first();
    }

    void first() override {
        _current = _begin;
        if (_current != _end)
            _currentIt = (*_current)->createIterator(
                DFSStepIteratorFactory::getInstance()
            );
        _currentReturned = false;
        _currentItFirstCalled = false;
    }

    Shape* currentItem() const override
    {
        if (isDone())
        {
            throw "no current item";
        }
        if (!_currentReturned)
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
            throw "no current item";
        }
        _currentReturned = true;
        if (_currentIt->isDone())
        {
            _current++;
            if (_current != _end)
            {
                _currentIt = (*_current)->createIterator(
                    DFSStepIteratorFactory::getInstance()
                );
                _currentReturned = false;
                _currentItFirstCalled = false;
            }
        }
        else
        {
            if (!_currentItFirstCalled)
            {
                _currentItFirstCalled = true;
            }
            else
            {
                _currentIt->next();
                if (_currentIt->isDone())
                {
                    _current++;
                    if (_current != _end)
                        _currentIt = (*_current)->createIterator(
                            DFSStepIteratorFactory::getInstance()
                        );
                    _currentReturned = false;
                    _currentItFirstCalled = false;
                }
            }
        }
    }

    bool isDone() const override
    {
        return _current == _end;
    }
};