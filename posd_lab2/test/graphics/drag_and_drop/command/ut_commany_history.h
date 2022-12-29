#include "mock_command.h"
#include "../../../../src/graphics/drag_and_drop/command/command.h"
#include "../../../../src/graphics/drag_and_drop/command/command_history.h"

#include <stack>

TEST(CommandHistoryTest, addCommandShouldBeCorrect)
{
    CommandHistory history;
    MockCommand *mockCommand = new MockCommand();
    history.addCommand(mockCommand);
    std::stack<Command *> _hist = history.getHistory();
    ASSERT_EQ(1, _hist.size());
    ASSERT_EQ(mockCommand, _hist.top());
}

TEST(CommandHistoryTest, beginMacroCommandShouldAddAMacroCommand)
{
    CommandHistory history;
    history.beginMacroCommand();
    std::stack<Command *> _hist = history.getHistory();
    ASSERT_EQ(1, _hist.size());
    ASSERT_TRUE(dynamic_cast<MacroCommand *>(_hist.top()) != nullptr);
}

TEST(CommandHistoryTest, commandShouldBeAddedInTheMacroCommandAfterBeginningMacro)
{
    CommandHistory history;
    MockCommand *mockCommand = new MockCommand();
    history.beginMacroCommand();
    history.addCommand(mockCommand);
    std::stack<Command *> _hist = history.getHistory();
    ASSERT_EQ(1, _hist.size());
    ASSERT_TRUE(dynamic_cast<MacroCommand *>(_hist.top()) != nullptr);
    MacroCommand *macro = (MacroCommand *)_hist.top();
    ASSERT_EQ(1, macro->getCommands().size());
    ASSERT_EQ(mockCommand, macro->getCommands()[0]);
}

TEST(CommandHistoryTest, commandShouldNotBeAddedInTheMacroCommandAfterEndingMacro)
{
    CommandHistory history;
    MockCommand *mockCommand = new MockCommand();
    history.beginMacroCommand();
    history.endMacroCommand();
    history.addCommand(mockCommand);
    std::stack<Command *> _hist = history.getHistory();
    ASSERT_EQ(2, _hist.size());
    ASSERT_EQ(mockCommand, _hist.top());
    _hist.pop();
    ASSERT_TRUE(dynamic_cast<MacroCommand *>(_hist.top()) != nullptr);
    MacroCommand *macro = (MacroCommand *)_hist.top();
    ASSERT_EQ(0, macro->getCommands().size());
}

TEST(CommandHistoryTest, UndoShouldCallTheUndoOfTheLatestCommandAndPopItOut)
{
    CommandHistory history;
    MockCommand *mockCommand = new MockCommand();
    history.addCommand(mockCommand);
    history.undo();
    ASSERT_TRUE(mockCommand->isUndoCalled());
}