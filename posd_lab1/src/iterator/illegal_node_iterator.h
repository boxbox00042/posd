#include "./iterator.h"
#include "./factory/dfs_iterator_factory.h"
#include "../visitor/illegal_node_checker.h"
#include <queue>

class IllegalNodeIterator : public Iterator
{
private:
    Shape *_root;
    std::queue<Shape *> _illegalNodes;
    IllegalNodeChecker *_checker;

    void _check(Shape *shape)
    {
        shape->accept(_checker);
        if (_checker->isIllegal())
            _illegalNodes.push(shape);
    }

public:
    IllegalNodeIterator(Shape *root) : _root(root)
    {
        _checker = new IllegalNodeChecker();
        _check(_root);
        for (Iterator *it = _root->createIterator(new DFSIteratorFactory()); !it->isDone(); it->next())
            _check(it->currentItem());
    }

    void first() override {}

    Shape *currentItem() const override
    {
        if (isDone())
        {
            throw "no current item";
        }
        return _illegalNodes.front();
    }

    void next() override
    {
        if (isDone())
        {
            throw "no current item";
        }
        _illegalNodes.pop();
    }

    bool isDone() const override
    {
        return _illegalNodes.size() == 0;
    }
};