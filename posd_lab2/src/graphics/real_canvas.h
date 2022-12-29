#pragma once
#include "canvas.h"
#include "drawing.h"
#include "../graphics/observer/observer.h"
#include "../visitor/shape_printer.h"
#include "../../src/shape.h"
#include "../../src/iterator/iterator.h"
#include "../../src/iterator/factory/iterator_factory.h"
class RealCanvas  : public Observer{
private:
     std::vector<Shape *> _shapes;
    ShapePrinter *_printer;
public:
    RealCanvas(Canvas *_canvas,Drawing *p){
        for(int i =0;i< p->shapes().size();i++){
            _shapes.push_back(p->shapes().at(i));
        }
         _printer = new ShapePrinter(_canvas);
}

    ~RealCanvas()
    {
        delete _printer;
    }
 void update() override{
    for (std::vector<Shape *>::iterator it = _shapes.begin(); it != _shapes.end(); it++)
        {
            Iterator *sit = (*it)->createIterator(IteratorFactory::getInstance("DFS"));
            (*it)->accept(_printer);
            for (; !sit->isDone(); sit->next())
                sit->currentItem()->accept(_printer);
        }
    }
};
