#pragma once

#include "command.h"
#include "../../canvas.h"
#include "../../../shape.h"
#include "../../../visitor/shape_printer.h"
#include "../../../iterator/iterator.h"
#include "../../../iterator/factory/iterator_factory.h"
#include <vector>

class RefreshCommand : public Command
{
private:
    Canvas *_canvas;
    ShapePrinter *_printer;
    std::vector<Shape *> _shapes;

public:
    RefreshCommand(Canvas *canvas, std::vector<Shape *> shapes) : _canvas(canvas), _shapes(shapes)
    {
        _printer = new ShapePrinter(_canvas);
    }

    ~RefreshCommand()
    {
        delete _printer;
    }

    void execute() override
    {
        for (std::vector<Shape *>::iterator it = _shapes.begin(); it != _shapes.end(); it++)
        {
            Iterator *sit = (*it)->createIterator(IteratorFactory::getInstance("DFS"));
            (*it)->accept(_printer);
            for (; !sit->isDone(); sit->next())
                sit->currentItem()->accept(_printer);
        }
    }

    void undo() override
    {
    }
};
