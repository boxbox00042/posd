#pragma once

#include "./iterator_factory.h"

class ListIteratorFactory : public IteratorFactory
{
private:
    static ListIteratorFactory instance;
    ListIteratorFactory();
public:
    Iterator *createIterator() override;
    Iterator *createIterator(std::list<Shape *>::const_iterator begin, std::list<Shape *>::const_iterator end) override;
};