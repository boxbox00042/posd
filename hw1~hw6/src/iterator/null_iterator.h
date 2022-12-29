#pragma once

#include "iterator.h"

class NullIterator : public Iterator
{
public:
    void first() override
    {
        throw "don't have the first item";
    }

    Shape* currentItem() const override
    {
        throw "point to nothing";
    }

    void next() override
    {
        throw "can't move to next item";
    }

    bool isDone() const override
    {
        return true;
    }
};