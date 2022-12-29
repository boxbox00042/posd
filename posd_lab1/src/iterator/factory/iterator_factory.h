#pragma once

#include "../iterator.h"
#include <list>

class IteratorFactory
{
public:
    virtual Iterator *createIterator() = 0;
    virtual Iterator *createIterator(std::list<Shape *>::const_iterator begin, std::list<Shape *>::const_iterator end) = 0;
};