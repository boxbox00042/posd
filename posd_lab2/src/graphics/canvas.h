#pragma once

class Circle;
class Triangle;
class Rectangle;

class Canvas
{
public:
    virtual ~Canvas() {};
    virtual void drawCircle(Circle *cir) = 0;
    virtual void drawTriangle(Triangle *tri) = 0;
    virtual void drawRectangle(Rectangle *rect) = 0;
    virtual void display() = 0;
};