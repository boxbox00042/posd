#pragma once

#include "../drawing.h"
#include "../../shape.h"
#include "../../two_dimensional_vector.h"
#include "../../circle.h"
#include "../../compound_shape.h"
#include "../../visitor/collision_detector.h"

#include <iostream>

class DragAndDrop
{
private:
    Drawing *_drawing;
    Shape *_target_shape = nullptr;
    double _previousX, _previousY;

public:
    DragAndDrop() {}
    DragAndDrop(Drawing *drawing) : _drawing(drawing)
    {
        _drawing->notify();
    }
    ~DragAndDrop() {}

    virtual void grab(double x, double y)
    {
        Point c1(x, y), c2(x, y);
        TwoDimensionalVector mr(c1, c2);
        Circle mousePoint(mr);
        CollisionDetector cd(&mousePoint);
        std::vector<Shape *> _shapes = _drawing->shapes();
        for (std::vector<Shape *>::iterator it = _shapes.begin(); it != _shapes.end(); it++)
            (*it)->accept(&cd);
        std::vector<Shape *> collidedShapes = cd.collidedShapes();
        if (collidedShapes.size() != 0)
            _target_shape = collidedShapes[0];
        _previousX = x;
        _previousY = y;
    }

    virtual void move(double x, double y)
    {
        if (_target_shape != nullptr)
        {
            double deltaX = x - _previousX, deltaY = y - _previousY;
            _target_shape->move(deltaX, deltaY);
            _previousX = x;
            _previousY = y;
            _drawing->notify();
        }
        else
        {
            throw "The target shape is not specified yet.";
        }
    }

    virtual void drop(double x, double y)
    {
        _target_shape = nullptr;
    }
};
