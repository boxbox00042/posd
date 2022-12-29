#pragma once

#include "shape_visitor.h"
#include "../graphics/canvas.h"

class ShapePrinter : public ShapeVisitor
{
private:
    Canvas *_canvas;

public:
    ShapePrinter(Canvas *canvas) : _canvas(canvas){};

    void visitCircle(Circle *circle) override
    {
        _canvas->drawCircle(circle);
    };

    void visitTriangle(Triangle *triangle) override
    {
        _canvas->drawTriangle(triangle);
    };

    void visitRectangle(Rectangle *rectangle) override
    {
        _canvas->drawRectangle(rectangle);
    };

    void visitCompoundShape(CompoundShape *compoundShape) override{

    };
};
