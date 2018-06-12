#include "stdafx.h"
#include "../TextEditorLib/History.h"
#include "../TextEditorLib/ICommand.h"

using namespace std;

namespace
{

struct MockCommand : ICommand
{
	struct State
	{
		bool executed = false;
		bool destroyed = false;
	};

	shared_ptr<State> state = make_shared<State>();

	~MockCommand()
	{
		state->destroyed = true;
	}

	void Execute() override
	{
		state->executed = true;
	}

	void Unexecute() override
	{
		state->executed = false;
	}
};

struct MockCommandAndState
{
	unique_ptr<MockCommand> cmd = make_unique<MockCommand>();
	shared_ptr<MockCommand::State> state = cmd->state;
};

} // namespace

TEST_SUITE("History tests")
{
	SCENARIO("A History has limited size")
	{
		GIVEN("a history filled with commands")
		{
			History history(2);

			MockCommandAndState cmd1;
			MockCommandAndState cmd2;
			history.AddAndExecuteCommand(move(cmd1.cmd));
			history.AddAndExecuteCommand(move(cmd2.cmd));

			REQUIRE(cmd1.state->executed);
			REQUIRE(!cmd1.state->destroyed);
			REQUIRE(cmd2.state->executed);
			REQUIRE(!cmd2.state->destroyed);

			MockCommandAndState newCmd;

			WHEN("a new command is added")
			{
				history.AddAndExecuteCommand(move(newCmd.cmd));

				THEN("the first command is removed")
				{
					CHECK(cmd1.state->executed);
					CHECK(cmd1.state->destroyed);
				}

				THEN("the new command is added")
				{
					CHECK(cmd2.state->executed);
					CHECK(!cmd2.state->destroyed);
					CHECK(newCmd.state->executed);
					CHECK(!newCmd.state->destroyed);
				}
			}

			WHEN("the last command is undone")
			{
				history.Undo();
				REQUIRE(!cmd2.state->executed);
				REQUIRE(!cmd2.state->destroyed);

				AND_WHEN("a new command is added")
				{
					history.AddAndExecuteCommand(move(newCmd.cmd));

					THEN("the undone command is removed")
					{
						CHECK(!cmd2.state->executed);
						CHECK(!cmd2.state->destroyed);
					}

					THEN("the new command is added")
					{
						CHECK(cmd1.state->executed);
						CHECK(!cmd1.state->destroyed);
						CHECK(newCmd.state->executed);
						CHECK(!newCmd.state->destroyed);
					}
				}
			}
		}
	}
}
