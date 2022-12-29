#pragma once

#include "./iterator_factory.h"

class BFSStepIteratorFactory : public IteratorFactory
{
public:
    Iterator *createIterator() override;
    Iterator *createIterator(std::list<Shape *>::const_iterator begin, std::list<Shape *>::const_iterator end) override;
};