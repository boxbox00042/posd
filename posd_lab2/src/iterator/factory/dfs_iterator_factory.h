#pragma once

#include "./iterator_factory.h"

class DFSIteratorFactory : public IteratorFactory
{
private:
    static DFSIteratorFactory instance;
    DFSIteratorFactory();
public:
    Iterator *createIterator() override;
    Iterator *createIterator(std::list<Shape *>::const_iterator begin, std::list<Shape *>::const_iterator end) override;
};