#pragma once

class Command
{
public:
    virtual ~Command(){};
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual void addCommand(Command *command)
    {
        throw "cannot add command.";
    }
    virtual std::vector<Command *> getCommands()
    {
        throw "cannot get commands.";
    }
};
