#include "./list_iterator_factory.h"
#include "../list_compound_iterator.h"
#include "../null_iterator.h"

#include <string>

ListIteratorFactory ListIteratorFactory::instance;

ListIteratorFactory::ListIteratorFactory() {
    IteratorFactory::_register("List", this);
}

Iterator *ListIteratorFactory::createIterator()
{
    return new NullIterator();
}

Iterator *ListIteratorFactory::createIterator(std::list<Shape *>::const_iterator begin, std::list<Shape *>::const_iterator end)
{
    return new ListCompoundIterator<std::list<Shape *>::const_iterator>(begin, end);
}