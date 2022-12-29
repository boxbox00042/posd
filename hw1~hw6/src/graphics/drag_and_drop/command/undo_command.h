#pragma once

#include "command.h"
#include "command_history.h"
#include "../drag_and_drop.h"

class UndoCommand : public Command
{

private:
    DragAndDrop *_dragAndDrop;
    CommandHistory *_commandHistory;

public:
    UndoCommand(DragAndDrop *dragAndDrop, CommandHistory *commandHistory) : _dragAndDrop(dragAndDrop), _commandHistory(commandHistory) {}

    void execute() override
    {
        _commandHistory->undo();
    }

    void undo() override
    {
    }
};
