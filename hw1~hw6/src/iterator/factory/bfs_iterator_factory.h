#pragma once

#include "./iterator_factory.h"

class BFSIteratorFactory : public IteratorFactory
{
private:
    static BFSIteratorFactory instance;
    BFSIteratorFactory();
public:
    Iterator *createIterator() override;
    Iterator *createIterator(std::list<Shape *>::const_iterator begin, std::list<Shape *>::const_iterator end) override;
};