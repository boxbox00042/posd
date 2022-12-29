#pragma once
#include "../circle.h"
#include "../triangle.h"
#include "../rectangle.h"
#include "../compound_shape.h"
#include <vector>
#include <stack>

class ShapeBuilder{
private:
    std::vector<Shape*> _result;
    std::stack<CompoundShape*> _compoundShapes;
public:

    void buildCircle(Point center, Point to_radius)
    {
        TwoDimensionalVector v(center, to_radius);
        Shape *cir = new Circle(v);
        if(!_compoundShapes.empty())
        {
            _compoundShapes.top()->addShape(cir);
        }
        else
        {
            _result.push_back(cir);
        }
    }

    void buildTriangle(Point common_point, Point v1_point, Point v2_point)
    {
        TwoDimensionalVector n(common_point, v1_point), m(common_point, v2_point);
        Shape *tri = new Triangle(n, m);
        if(!_compoundShapes.empty())
        {
            _compoundShapes.top()->addShape(tri);
        }
        else
        {
            _result.push_back(tri);
        }
    }

    void buildRectangle(Point common_point, Point v1_point, Point v2_point)
    {
        TwoDimensionalVector n(common_point, v1_point), m(common_point, v2_point);
        Shape *rect = new Rectangle(n, m);
        if(!_compoundShapes.empty())
        {
            _compoundShapes.top()->addShape(rect);
        }
        else
        {
            _result.push_back(rect);
        }
    }

    void buildCompoundShape()
    {
        CompoundShape *cs = new CompoundShape();
        _compoundShapes.push(cs);
    }

    void buildCompoundEnd()
    {
        CompoundShape *topCS = _compoundShapes.top();
        _compoundShapes.pop();
        if(_compoundShapes.empty())
        {
            _result.push_back(topCS);
        }
        else
        {
            _compoundShapes.top()->addShape(topCS);
        }
    }

    std::vector<Shape*> getResult()
    {
        return _result;
    }
};