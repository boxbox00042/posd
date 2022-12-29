#pragma once

#include "./iterator_factory.h"

class DFSStepIteratorFactory : public IteratorFactory
{
private:
    DFSStepIteratorFactory(){}
    static DFSStepIteratorFactory *instance;
public:
    static DFSStepIteratorFactory *getInstance();
    Iterator *createIterator() override;
    Iterator *createIterator(std::list<Shape *>::const_iterator begin, std::list<Shape *>::const_iterator end) override;
};