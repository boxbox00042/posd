#include "./dfs_step_iterator_factory.h"
#include "../null_iterator.h"
#include "../dfs_step_compound_iterator.h"

Iterator *DFSStepIteratorFactory::createIterator()
{
    return new NullIterator();
}

Iterator *DFSStepIteratorFactory::createIterator(std::list<Shape *>::const_iterator begin, std::list<Shape *>::const_iterator end)
{
    return new DFSStepCompoundIterator<std::list<Shape *>::const_iterator>(begin, end);
}