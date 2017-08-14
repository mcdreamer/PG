#include "PG/console/ConsoleController.h"
#include "PG/console/InputParser.h"
#include "PG/console/CommandSetHandle.h"
#include "PG/core/KeyCode.h"
#include "PG/app/KeyCodeUtils.h"

namespace PG {

//--------------------------------------------------------
ConsoleController::ConsoleController()
: m_NextSetID(0), m_NotFoundString("Command not found")
{
	addCaret();
}

//--------------------------------------------------------
void ConsoleController::setCommandNotFoundString(const std::string& notFoundString)
{
	m_NotFoundString = notFoundString;
}

//--------------------------------------------------------
CommandSetHandle ConsoleController::addCommandSet(const PG::ConsoleCommandRegistry& registry)
{
	CommandSetHandle setHandle(m_NextSetID++);
	
	m_CommandSets.emplace_back(setHandle, registry);
	
	return setHandle;
}

//--------------------------------------------------------
void ConsoleController::removeCommandSet(const CommandSetHandle& setHandle)
{
	auto setIt = std::find_if(m_CommandSets.begin(),
							  m_CommandSets.end(),
							  [&](const auto& set) { return set.first == setHandle; });
	
	if (setIt != m_CommandSets.end())
	{
		m_CommandSets.erase(setIt);
	}
}

//--------------------------------------------------------
void ConsoleController::keyPressed(const KeyCode& code)
{
	removeCaret();
	
	auto input = m_ConsoleInput.get();
	
	switch (code)
	{
		case PG::KeyCode::kEnter:
		{
			auto output = handleInputAndGetOutput(input);
			
			m_ConsoleOutput.push_back(output);
			m_ConsoleOutputSize = (int)m_ConsoleOutput.size();
			
			input = "";
			
			break;
		}
		
		case KeyCode::kBackspace:
			if (!input.empty())
			{
				input.pop_back();
			}
			break;
		
		case KeyCode::kEscape:
			input = "";
			break;
		
		default:
			KeyCodeUtils::addCharacterForKeyCode(code, input);
			break;
	}
	
	m_ConsoleInput = input;
	
	addCaret();
}

//--------------------------------------------------------
std::string ConsoleController::handleInputAndGetOutput(const std::string& input)
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

//--------------------------------------------------------
void ConsoleController::addCaret()
{
	m_ConsoleInput.set(m_ConsoleInput.get() + "|");
}

//--------------------------------------------------------
void ConsoleController::removeCaret()
{
	auto input = m_ConsoleInput.get();
	if (!input.empty())
	{
		input.pop_back();
		m_ConsoleInput.set(input);
	}
}

}
