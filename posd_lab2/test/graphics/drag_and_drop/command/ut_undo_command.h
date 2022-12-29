#include "mock_command.h"
#include "../mock_drag_and_drop.h"
#include "../../../../src/graphics/drag_and_drop/command/undo_command.h"
#include "../../../../src/graphics/drag_and_drop/command/command_history.h"

TEST(UndoCommandTest, executeShouldCallCommandHistoryToUndo)
{
    MockDragAndDrop mockDragAndDrop;
    CommandHistory history;
    MockCommand *mockCommand = new MockCommand();
    history.addCommand(mockCommand);
    UndoCommand undoCommand(&mockDragAndDrop, &history);
    undoCommand.execute();
    ASSERT_TRUE(mockCommand->isUndoCalled());
}
