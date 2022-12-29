#include "../mock_drag_and_drop.h"
#include "../../../../src/graphics/drag_and_drop/command/move_command.h"
#include "../../../../src/graphics/drag_and_drop/command/command_history.h"

TEST(MoveCommandTest, executeShouldCallMoveMethodWithCorrectMousePosition)
{
    MockDragAndDrop mockDragAndDrop;
    CommandHistory history;
    MousePosition::getInstance()->setPos(3.14, -6.28);
    MoveCommand moveCommand(&mockDragAndDrop, &history);
    moveCommand.execute();
    ASSERT_NEAR(3.14, mockDragAndDrop.getMoveX(), 0.001);
    ASSERT_NEAR(-6.28, mockDragAndDrop.getMoveY(), 0.001);
}

// TEST(MoveCommandTest, executeShouldCopyItselfInHistory)
// {
//     MockDragAndDrop mockDragAndDrop;
//     CommandHistory history;
//     MousePosition::getInstance()->setPos(0, 0);
//     MoveCommand moveCommand(&mockDragAndDrop, &history);
//     moveCommand.execute();
//     ASSERT_NEAR(0, mockDragAndDrop.getMoveX(), 0.001);
//     ASSERT_NEAR(0, mockDragAndDrop.getMoveY(), 0.001);
//     ASSERT_TRUE(dynamic_cast<MoveCommand *>(history.getHistory().top()) != nullptr);
// }

// TEST(MoveCommandTest, theCopiedCommandShouldHaveTheOriginalXY)
// {
//     MockDragAndDrop mockDragAndDrop;
//     CommandHistory history;
//     MousePosition::getInstance()->setPos(-984.23, -541.41);
//     MoveCommand moveCommand(&mockDragAndDrop, &history);
//     moveCommand.execute();
//     MousePosition::getInstance()->setPos(-851.369, -532.2);
//     MoveCommand *copied = (MoveCommand *)history.getHistory().top();
//     ASSERT_NEAR(-984.23, copied->getX(), 0.001);
//     ASSERT_NEAR(-541.41, copied->getY(), 0.001);
// }

TEST(MoveCommandTest, undoShouldCallMoveWithTheOriginalXY)
{
    MockDragAndDrop mockDragAndDrop;
    CommandHistory history;
    MousePosition::getInstance()->setPos(99, -99);
    MoveCommand moveCommand(&mockDragAndDrop, &history);
    moveCommand.execute();
    MousePosition::getInstance()->setPos(1024, -768);
    moveCommand.undo();
    ASSERT_NEAR(99, mockDragAndDrop.getMoveX(), 0.001);
    ASSERT_NEAR(-99, mockDragAndDrop.getMoveY(), 0.001);
}

TEST(MoveCommandTest, addCommandShouldThrowException)
{
    MockDragAndDrop mockDragAndDrop;
    CommandHistory history;
    MousePosition::getInstance()->setPos(0, 0);
    MoveCommand moveCommand(&mockDragAndDrop, &history);
    MockCommand mockCommand;
    ASSERT_ANY_THROW(moveCommand.addCommand(&mockCommand));
}

TEST(MoveCommandTest, getCommandsShouldThrowException)
{
    MockDragAndDrop mockDragAndDrop;
    CommandHistory history;
    MousePosition::getInstance()->setPos(0, 0);
    MoveCommand moveCommand(&mockDragAndDrop, &history);
    ASSERT_ANY_THROW(moveCommand.getCommands());
}