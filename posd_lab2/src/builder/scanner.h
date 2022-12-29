#pragma once

#include <string>
#include <vector>

class Scanner 
{
private:
    std::string _inputText;
    std::string::size_type pos = 0;
    std::vector<std::string> tokenList = {"Circle", "Rectangle", "Triangle", "CompoundShape", "Vector", "(", ")", ","};

    void skipWhiteSpace()
    {
        while(_inputText[pos] == ' ')
        {
            pos++;
        }
    }

public:
    Scanner(std::string input = ""): _inputText(input) {}

    std::string next()
    {
        std::string result = "";
        if(isDone())
        {
            throw std::string("No more token to return");
        }
        while(!isDone() && result == "")
        {
            for(auto token : tokenList)
            {
                if(_inputText.compare(pos,token.length(),token) == 0)
                {
                    pos += token.length();
                    result = token;
                    break;
                }
            }
            if(result == "")
                pos++;
        }
        return result;
    }

    double nextDouble()
    {
        double isNegative = 1;
        std::string result = "";
        if(isDone())
        {
            throw std::string("No more double to return");
        }
        if(_inputText[pos] == '-' || _inputText[pos] == '-')
        {
            isNegative = -1;
        }
        while(!isDone() && result == "")
        {
            while (true)
            {
                if((_inputText[pos] <= '9' && _inputText[pos] >= '0') || _inputText[pos] == '.')
                {
                    result = result + _inputText[pos];
                    pos++;
                }
                else
                {
                    break;
                }
            }
            if(result == "")
                pos++;
        }
        return isNegative * std::stod(result);
    }

    bool isDone()
    {
        skipWhiteSpace();
        return pos == _inputText.length();
    }
};