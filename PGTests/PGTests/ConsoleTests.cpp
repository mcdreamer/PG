#include "ConsoleTests.h"
#include "gtest/gtest.h"

#include "PG/console/InputParser.h"
#include "PG/console/RawConsoleCommand.h"
#include "PG/console/ConsoleCommandArgument.h"
#include "PG/console/ConsoleCommandArgumentType.h"
#include "PG/console/ConsoleCommandRegistry.h"

#include <string>

using namespace PG;

//--------------------------------------------------------
TEST(ConsoleTests,testInputParser)
{
	InputParser parser;
	
	auto cmd = parser.parseInput("");
	EXPECT_FALSE(cmd.is_initialized());
	
	cmd = parser.parseInput("showFPS");
	ASSERT_TRUE(cmd.is_initialized());
	EXPECT_EQ(std::string("showFPS"), cmd->getCommandName());
	EXPECT_TRUE(cmd->getArguments().empty());
	
	cmd = parser.parseInput("   showFPS");
	ASSERT_TRUE(cmd.is_initialized());
	EXPECT_EQ(std::string("showFPS"), cmd->getCommandName());
	EXPECT_TRUE(cmd->getArguments().empty());
	
	cmd = parser.parseInput("   showFPS    ");
	ASSERT_TRUE(cmd.is_initialized());
	EXPECT_EQ(std::string("showFPS"), cmd->getCommandName());
	EXPECT_TRUE(cmd->getArguments().empty());
	
	cmd = parser.parseInput("showFPS true");
	ASSERT_TRUE(cmd.is_initialized());
	EXPECT_EQ(std::string("showFPS"), cmd->getCommandName());
	ASSERT_EQ((size_t)1, cmd->getArguments().size());
	EXPECT_EQ(std::string("true"), cmd->getArguments()[0]);
	
	cmd = parser.parseInput("showFPS      true");
	ASSERT_TRUE(cmd.is_initialized());
	EXPECT_EQ(std::string("showFPS"), cmd->getCommandName());
	ASSERT_EQ((size_t)1, cmd->getArguments().size());
	EXPECT_EQ(std::string("true"), cmd->getArguments()[0]);
	
	cmd = parser.parseInput("showFPS true 200");
	ASSERT_TRUE(cmd.is_initialized());
	EXPECT_EQ(std::string("showFPS"), cmd->getCommandName());
	ASSERT_EQ((size_t)2, cmd->getArguments().size());
	EXPECT_EQ(std::string("true"), cmd->getArguments()[0]);
	EXPECT_EQ(std::string("200"), cmd->getArguments()[1]);
}

//--------------------------------------------------------
TEST(ConsoleTests,testConsoleCommandRegistry)
{
	const std::string notFoundString("no command");
	const std::string argsString("arg count required =");
	const std::string errorString("error");

	ConsoleCommandRegistry registry;
	registry.setNArgumentsString(argsString);
	registry.setErrorString(errorString);
	
	RawConsoleCommand cmd("test", {});
	auto response = registry.handleCommand(cmd);
	EXPECT_FALSE(response.is_initialized());
	
	registry.addHandler("test", [](const std::vector<ConsoleCommandArgument>& args) { return "hi"; }, {});
	response = registry.handleCommand(cmd);
	ASSERT_TRUE(response.is_initialized());
	EXPECT_EQ(std::string("hi"), response);
	
	registry.addHandler("test", [](const std::vector<ConsoleCommandArgument>& args)
	{
		return std::to_string(args[0].getValueAsInt() + args[1].getValueAsInt());
	},
	{ ConsoleCommandArgumentType::kInt,
	ConsoleCommandArgumentType::kInt
	});
	
	cmd = RawConsoleCommand("test", { "1", "2" });
	response = registry.handleCommand(cmd);
	ASSERT_TRUE(response.is_initialized());
	EXPECT_EQ(std::string("3"), response);
	
	cmd = RawConsoleCommand("test", { "1", "2", "3" });
	response = registry.handleCommand(cmd);
	ASSERT_TRUE(response.is_initialized());
	EXPECT_EQ(argsString + " 2", response);
	
	cmd = RawConsoleCommand("test", { "1", "sdg" });
	response = registry.handleCommand(cmd);
	ASSERT_TRUE(response.is_initialized());
	EXPECT_EQ(errorString, response);
}
