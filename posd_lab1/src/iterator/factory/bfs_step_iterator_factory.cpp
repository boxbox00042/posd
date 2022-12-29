#include "./bfs_step_iterator_factory.h"
#include "../null_iterator.h"
#include "../bfs_step_compound_iterator.h"

Iterator *BFSStepIteratorFactory::createIterator()
{
    return new NullIterator();
}

Iterator *BFSStepIteratorFactory::createIterator(std::list<Shape *>::const_iterator begin, std::list<Shape *>::const_iterator end)
{
    return new BFSStepCompoundIterator<std::list<Shape *>::const_iterator>(begin, end);
}