#pragma once

#include "command.h"
#include <vector>

class MacroCommand : public Command
{
private:
    std::vector<Command *> _commands;

public:
    MacroCommand() {}
    ~MacroCommand()
    {
        for (std::vector<Command *>::iterator it = _commands.begin(); it != _commands.end(); it++)
            delete (*it);
    }

    void execute() override
    {
        for (std::vector<Command *>::iterator it = _commands.begin(); it != _commands.end(); it++)
            (*it)->execute();
    }

    void addCommand(Command *command) override
    {
        _commands.push_back(command);
    }

    void undo() override
    {
        for (std::vector<Command *>::reverse_iterator it = _commands.rbegin(); it != _commands.rend(); it++)
            (*it)->undo();
    }

    std::vector<Command *> getCommands() override
    {
        return _commands;
    }
};
