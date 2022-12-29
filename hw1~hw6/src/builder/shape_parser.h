#pragma once
#include "./scanner.h"
#include "./shape_builder.h"
#include "../two_dimensional_vector.h"
#include <string>
#include <vector>

class ShapeParser
{
private:
    Scanner *_scanner;
    ShapeBuilder *_builder;

    void parseCircle(std::string token)
    {
        if(token == "Circle")
        {
            parseLeftParentheses();
            TwoDimensionalVector vec = parseVector();
            parseRightParentheses();

            _builder->buildCircle(vec.a(), vec.b());
        }
    }

    void parseTriangle(std::string token)
    {
        if(token == "Triangle")
        {
            parseLeftParentheses();
            TwoDimensionalVector vec1 = parseVector();
            parseComma();
            TwoDimensionalVector vec2 = parseVector();
            parseRightParentheses();

            if(vec1.a() == vec2.a()){
                _builder->buildTriangle(vec1.a(), vec1.b(), vec2.b());
            }
            else if(vec1.a() == vec2.b()){
                _builder->buildTriangle(vec1.a(), vec1.b(), vec2.a());
            }
            else if(vec1.b() == vec2.a()){
                _builder->buildTriangle(vec1.b(), vec1.a(), vec2.b());
            }
            else if(vec1.b() == vec2.b()){
                _builder->buildTriangle(vec1.b(), vec1.a(), vec2.a());
            }
        }
    }

    void parseRectangle(std::string token)
    {
        if(token == "Rectangle")
        {
            parseLeftParentheses();
            TwoDimensionalVector vec1 = parseVector();
            parseComma();
            TwoDimensionalVector vec2 = parseVector();
            parseRightParentheses();

            if(vec1.a() == vec2.a()){
                _builder->buildRectangle(vec1.a(), vec1.b(), vec2.b());
            }
            else if(vec1.a() == vec2.b()){
                _builder->buildRectangle(vec1.a(), vec1.b(), vec2.a());
            }
            else if(vec1.b() == vec2.a()){
                _builder->buildRectangle(vec1.b(), vec1.a(), vec2.b());
            }
            else if(vec1.b() == vec2.b()){
                _builder->buildRectangle(vec1.b(), vec1.a(), vec2.a());
            }
        }
    }

    void parseCompoundShape(std::string token)
    {
        if(token == "CompoundShape")
        {
            parseLeftParentheses();
            _builder->buildCompoundShape();
            parseShape(_scanner->next());
            while(true)
            {
                token = _scanner->next();
                if(token != ",")
                    break;
                parseShape(_scanner->next());
            }
            if(token != ")")
                throw std::string("Valid format, missing right parentheses");
            _builder->buildCompoundEnd();
        }
    }

    TwoDimensionalVector parseVector()
    {
        if(_scanner->next() != "Vector")
            throw std::string("Invalid format. The next token should be a vector.");
        else
        {
            parseLeftParentheses();
            Point p1 = parsePoint();
            parseComma();
            Point p2 = parsePoint();
            parseRightParentheses();
            TwoDimensionalVector v(p1, p2);
            return v;
        }
    }

    Point parsePoint()
    {
        parseLeftParentheses();
        double x = _scanner->nextDouble();
        parseComma();
        double y = _scanner->nextDouble();
        parseRightParentheses();
        return Point(x, y);
    }

    void parseRightParentheses()
    {
        if(_scanner->next() != ")")
            throw std::string("Invalid format. The next token should be a right parentheses.");
    }

    void parseLeftParentheses()
    {
        if(_scanner->next() != "(")
            throw std::string("Invalid format. The next token should be a left parentheses.");
    }

    void parseComma()
    {
        if(_scanner->next() != ",")
            throw std::string("Invalid format. The next token should be a comma.");
    }

    void parseShape(std::string token)
    {
        parseCircle(token);
        parseTriangle(token);
        parseRectangle(token);
        parseCompoundShape(token);
    }

public:
    ShapeParser(std::string input)
    {
        _scanner = new Scanner(input);
        _builder = new ShapeBuilder();
    }

    ~ShapeParser()
    {
        delete _scanner;
        delete _builder;
    }

    void parse()
    {
        while(!_scanner->isDone())
        {
            std::string token = _scanner->next();
            parseShape(token);
        }
    }

    std::vector<Shape*> getResult()
    {
        return _builder->getResult();
    }
};