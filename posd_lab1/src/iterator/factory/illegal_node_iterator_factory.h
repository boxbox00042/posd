#pragma once
#include "./iterator_factory.h"
#include "../null_iterator.h"
#include "../illegal_node_iterator.h"

class IllegalNodeIteratorFactory : public IteratorFactory
{
private:
    Shape *_root;

public:
    IllegalNodeIteratorFactory(Shape *root) : _root(root) {}

    Iterator *createIterator() override
    {
        return new NullIterator();
    }

    Iterator *createIterator(std::list<Shape *>::const_iterator begin, std::list<Shape *>::const_iterator end) override
    {
        return new IllegalNodeIterator(_root);
    }
};