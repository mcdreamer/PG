#include "ConsoleTests.h"
#include "gtest/gtest.h"

#include "PG/console/InputParser.h"
#include "PG/console/ConsoleCommand.h"

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
