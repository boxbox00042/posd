#include "mock_command.h"
#include "../../../../src/graphics/drag_and_drop/command/command.h"
#include "../../../../src/graphics/drag_and_drop/command/macro_command.h"

#include <vector>

TEST(MacroCommandTest, addCommandShouldBeCorrect)
{
    MacroCommand macroCommand;
    MockCommand * mockCommand = new MockCommand();
    macroCommand.addCommand(mockCommand);
    std::vector<Command *> comds = macroCommand.getCommands();
    ASSERT_EQ(1, comds.size());
    ASSERT_EQ(mockCommand, comds[0]);
}

TEST(MacroCommandTest, executeShouldExecuteAllCommands)
{
    MacroCommand macroCommand;
    MockCommand * mockCommand1 = new MockCommand();
    MockCommand * mockCommand2 = new MockCommand();
    macroCommand.addCommand(mockCommand1);
    macroCommand.addCommand(mockCommand2);
    macroCommand.execute();
    ASSERT_TRUE(mockCommand1->isExecuteCalled());
    ASSERT_TRUE(mockCommand2->isExecuteCalled());
}

TEST(MacroCommandTest, undoShouldUndoAllCommands)
{
    MacroCommand macroCommand;
    MockCommand * mockCommand1 = new MockCommand();
    MockCommand * mockCommand2 = new MockCommand();
    macroCommand.addCommand(mockCommand1);
    macroCommand.addCommand(mockCommand2);
    macroCommand.undo();
    ASSERT_TRUE(mockCommand1->isUndoCalled());
    ASSERT_TRUE(mockCommand2->isUndoCalled());
}