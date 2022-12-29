#include "../mock_drag_and_drop.h"
#include "../../../../src/graphics/drag_and_drop/command/drop_command.h"
#include "../../../../src/graphics/drag_and_drop/command/grab_command.h"
#include "../../../../src/graphics/drag_and_drop/command/command_history.h"

TEST(DropCommandTest, executeShouldCallDropMethodWithCorrectMousePosition)
{
    MockDragAndDrop mockDragAndDrop;
    CommandHistory history;
    MousePosition::getInstance()->setPos(85.23, 232.7);
    DropCommand dropCommand(&mockDragAndDrop, &history);
    dropCommand.execute();
    ASSERT_NEAR(85.23, mockDragAndDrop.getDropX(), 0.001);
    ASSERT_NEAR(232.7, mockDragAndDrop.getDropY(), 0.001);
}

TEST(DropCommandTest, executeShouldCopyItselfInMacroCommandInHistory)
{
    MockDragAndDrop mockDragAndDrop;
    CommandHistory history;
    MousePosition::getInstance()->setPos(0, 0);
    GrabCommand grabCommand(&mockDragAndDrop, &history);
    grabCommand.execute();
    MousePosition::getInstance()->setPos(23.45, 89.01);
    DropCommand dropCommand(&mockDragAndDrop, &history);
    dropCommand.execute();
    ASSERT_NEAR(23.45, mockDragAndDrop.getDropX(), 0.001);
    ASSERT_NEAR(89.01, mockDragAndDrop.getDropY(), 0.001);
    ASSERT_TRUE(dynamic_cast<DropCommand *>(history.getHistory().top()->getCommands()[1]) != nullptr);
}

TEST(DropCommandTest, theCopiedCommandShouldHaveTheOriginalXY)
{
    MockDragAndDrop mockDragAndDrop;
    CommandHistory history;
    MousePosition::getInstance()->setPos(-7.6, 3.27);
    GrabCommand grabCommand(&mockDragAndDrop, &history);
    grabCommand.execute();
    MousePosition::getInstance()->setPos(95.66, 77.54);
    DropCommand dropCommand(&mockDragAndDrop, &history);
    dropCommand.execute();
    DropCommand *copied = (DropCommand *)history.getHistory().top()->getCommands()[1];
    ASSERT_NEAR(95.66, copied->getX(), 0.001);
    ASSERT_NEAR(77.54, copied->getY(), 0.001);
}

TEST(DropCommandTest, undoShouldCallDragWithTheOriginalXY)
{
    MockDragAndDrop mockDragAndDrop;
    CommandHistory history;
    MousePosition::getInstance()->setPos(99, -99);
    GrabCommand grabCommand(&mockDragAndDrop, &history);
    grabCommand.execute();
    MousePosition::getInstance()->setPos(1024, -768);
    DropCommand dropCommand(&mockDragAndDrop, &history);
    dropCommand.execute();
    Command *macro = history.getHistory().top();
    macro->undo();
    ASSERT_NEAR(1024, mockDragAndDrop.getGrabX(), 0.001);
    ASSERT_NEAR(-768, mockDragAndDrop.getGrabY(), 0.001);
    ASSERT_NEAR(99, mockDragAndDrop.getDropX(), 0.001);
    ASSERT_NEAR(-99, mockDragAndDrop.getDropY(), 0.001);
}

TEST(DropCommandTest, addCommandShouldThrowException)
{
    MockDragAndDrop mockDragAndDrop;
    CommandHistory history;
    MousePosition::getInstance()->setPos(0, 0);
    DropCommand dropCommand(&mockDragAndDrop, &history);
    MockCommand mockCommand;
    ASSERT_ANY_THROW(dropCommand.addCommand(&mockCommand));
}

TEST(DropCommandTest, getCommandsShouldThrowException)
{
    MockDragAndDrop mockDragAndDrop;
    CommandHistory history;
    MousePosition::getInstance()->setPos(0, 0);
    DropCommand dropCommand(&mockDragAndDrop, &history);
    ASSERT_ANY_THROW(dropCommand.getCommands());
}