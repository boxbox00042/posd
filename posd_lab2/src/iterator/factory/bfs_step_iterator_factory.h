#pragma once

#include "./iterator_factory.h"

class BFSStepIteratorFactory : public IteratorFactory
{
private:
    BFSStepIteratorFactory(){}
    static BFSStepIteratorFactory *instance;
public:
    static BFSStepIteratorFactory *getInstance();
    Iterator *createIterator() override;
    Iterator *createIterator(std::list<Shape *>::const_iterator begin, std::list<Shape *>::const_iterator end) override;
};