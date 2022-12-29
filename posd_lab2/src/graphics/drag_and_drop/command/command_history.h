#pragma once

#include <stack>
#include "command.h"
#include "macro_command.h"

class CommandHistory
{
private:
    bool inMacro = false;
    std::stack<Command *> _history;
    std::stack<Command *> _undoCommands;

public:
    CommandHistory(){};
    ~CommandHistory()
    {
        while (!_history.empty())
        {
            Command *c = _history.top();
            delete c;
            _history.pop();
        }
        while (!_undoCommands.empty())
        {
            Command *c = _undoCommands.top();
            delete c;
            _undoCommands.pop();
        }
    };

    void beginMacroCommand()
    {
        Command *macro = new MacroCommand();
        _history.push(macro);
        inMacro = true;
    }

    void addCommand(Command *command)
    {
        if (inMacro)
            _history.top()->addCommand(command);
        else
            _history.push(command);
    }

    void endMacroCommand()
    {
        inMacro = false;
    }

    void undo()
    {
        if (_history.size() != 0)
        {
            Command *command = _history.top();
            command->undo();
            _history.pop();
            _undoCommands.push(command);
        }
        else
        {
            std::cout << "No more commands to undo." << std::endl;
        }
    }

    std::stack<Command *> getHistory()
    {
        return _history;
    }
};