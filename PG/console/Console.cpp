#include "PG/console/Console.h"
#include "PG/console/InputParser.h"
#include "PG/console/CommandSetHandle.h"
#include "PG/core/KeyCode.h"
#include "PG/app/KeyCodeUtils.h"

namespace PG {

//--------------------------------------------------------
Console::Console()
: m_NextSetID(0), m_NotFoundString("Command not found"), m_ConsoleInput("|")
{}

//--------------------------------------------------------
void Console::setCommandNotFoundString(const std::string& notFoundString)
{
	m_NotFoundString = notFoundString;
}

//--------------------------------------------------------
CommandSetHandle Console::addCommandSet(const PG::ConsoleCommandRegistry& registry)
{
	CommandSetHandle setHandle(m_NextSetID++);
	
	m_CommandSets.emplace_back(setHandle, registry);
	
	return setHandle;
}

//--------------------------------------------------------
void Console::removeCommandSet(const CommandSetHandle& setHandle)
{
	auto setIt = std::find_if(m_CommandSets.begin(),
							  m_CommandSets.end(),
							  [&](const auto& set) { return set.first == setHandle; });
	
	if (setIt != m_CommandSets.end())
	{
		m_CommandSets.erase(setIt);
	}
}

namespace
{
	//--------------------------------------------------------
	void handleBackspace(const KeyCode& code, std::string& str)
	{
		if (code == KeyCode::kBackspace && !str.empty())
		{
			str.pop_back();
		}
	}
	
	//--------------------------------------------------------
	void handleEscape(const KeyCode& code, std::string& str)
	{
		if (code == KeyCode::kEscape && !str.empty())
		{
			str.clear();
		}
	}
}

//--------------------------------------------------------
void Console::keyPressed(const KeyCode& code)
{
	if (code == PG::KeyCode::kEnter)
	{
		auto input = m_ConsoleInput.get();
		if (!input.empty())
		{
			input.pop_back();
		}

		auto output = handleInputAndGetOutput(input);
		
		m_ConsoleOutput.push_back(output);
		m_ConsoleOutputSize = (int)m_ConsoleOutput.size();
		
		m_ConsoleInput.set("");
	}
	
	auto existingValue = m_ConsoleInput.get();
	
	if (!existingValue.empty())
	{
		existingValue.pop_back();
	}
	
	KeyCodeUtils::addCharacterForKeyCode(code, existingValue);
	handleBackspace(code, existingValue);
	handleEscape(code, existingValue);
	
	existingValue += "|";
	
	m_ConsoleInput.set(existingValue);
}

//--------------------------------------------------------
std::string Console::handleInputAndGetOutput(const std::string& input)
{
	InputParser parser;
	const auto cmd = parser.parseInput(input);
	if (cmd.is_initialized())
	{
		for (auto& commandSet : m_CommandSets)
		{
			auto output = commandSet.second.handleCommand(cmd.get());
			if (output.is_initialized())
			{
				return output.get();
			}
		}
	}
	
	return m_NotFoundString;
}

}
