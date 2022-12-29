#include "./bfs_iterator_factory.h"
#include "../null_iterator.h"
#include "../bfs_compound_iterator.h"

BFSIteratorFactory BFSIteratorFactory::instance;

BFSIteratorFactory::BFSIteratorFactory() {
    IteratorFactory::_register("BFS", this);
}

Iterator *BFSIteratorFactory::createIterator()
{
    return new NullIterator();
}

Iterator *BFSIteratorFactory::createIterator(std::list<Shape *>::const_iterator begin, std::list<Shape *>::const_iterator end)
{
    return new BFSCompoundIterator<std::list<Shape *>::const_iterator>(begin, end);
}
