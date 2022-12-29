#include "../mock_drag_and_drop.h"
#include "../../../../src/graphics/drag_and_drop/command/grab_command.h"
#include "../../../../src/graphics/drag_and_drop/command/command_history.h"

TEST(GrabCommandTest, executeShouldCallDragMethodWithCorrectMousePosition)
{
    MockDragAndDrop mockDragAndDrop;
    CommandHistory history;
    MousePosition::getInstance()->setPos(-9.8, 11.23);
    GrabCommand grabCommand(&mockDragAndDrop, &history);
    grabCommand.execute();
    ASSERT_NEAR(-9.8, mockDragAndDrop.getGrabX(), 0.001);
    ASSERT_NEAR(11.23, mockDragAndDrop.getGrabY(), 0.001);
}

TEST(GrabCommandTest, executeShouldCopyItselfInMacroCommandInHistory)
{
    MockDragAndDrop mockDragAndDrop;
    CommandHistory history;
    MousePosition::getInstance()->setPos(0, 0);
    GrabCommand grabCommand(&mockDragAndDrop, &history);
    grabCommand.execute();
    ASSERT_NEAR(0, mockDragAndDrop.getGrabX(), 0.001);
    ASSERT_NEAR(0, mockDragAndDrop.getGrabY(), 0.001);
    ASSERT_TRUE(dynamic_cast<GrabCommand *>(history.getHistory().top()->getCommands()[0]) != nullptr);
}

TEST(GrabCommandTest, theCopiedCommandShouldHaveTheOriginalXY)
{
    MockDragAndDrop mockDragAndDrop;
    CommandHistory history;
    MousePosition::getInstance()->setPos(-7.6, 3.27);
    GrabCommand grabCommand(&mockDragAndDrop, &history);
    grabCommand.execute();
    MousePosition::getInstance()->setPos(95.66, 77.54);
    GrabCommand *copied = (GrabCommand *)history.getHistory().top()->getCommands()[0];
    ASSERT_NEAR(-7.6, copied->getX(), 0.001);
    ASSERT_NEAR(3.27, copied->getY(), 0.001);
}

TEST(GrabCommandTest, undoShouldCallMoveAndDropWithTheOriginalXY)
{
    MockDragAndDrop mockDragAndDrop;
    CommandHistory history;
    MousePosition::getInstance()->setPos(99, -99);
    GrabCommand grabCommand(&mockDragAndDrop, &history);
    grabCommand.execute();
    MousePosition::getInstance()->setPos(1024, -768);
    GrabCommand *copied = (GrabCommand *)history.getHistory().top()->getCommands()[0];
    copied->undo();
    ASSERT_NEAR(99, mockDragAndDrop.getMoveX(), 0.001);
    ASSERT_NEAR(-99, mockDragAndDrop.getMoveY(), 0.001);
    ASSERT_NEAR(99, mockDragAndDrop.getDropX(), 0.001);
    ASSERT_NEAR(-99, mockDragAndDrop.getDropY(), 0.001);
}

TEST(GrabCommandTest, addCommandShouldThrowException)
{
    MockDragAndDrop mockDragAndDrop;
    CommandHistory history;
    MousePosition::getInstance()->setPos(0, 0);
    GrabCommand grabCommand(&mockDragAndDrop, &history);
    MockCommand mockCommand;
    ASSERT_ANY_THROW(grabCommand.addCommand(&mockCommand));
}

TEST(GrabCommandTest, getCommandsShouldThrowException)
{
    MockDragAndDrop mockDragAndDrop;
    CommandHistory history;
    MousePosition::getInstance()->setPos(0, 0);
    GrabCommand grabCommand(&mockDragAndDrop, &history);
    ASSERT_ANY_THROW(grabCommand.getCommands());
}