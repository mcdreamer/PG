#include "PG/internal/ui/Console.h"
#include "PG/ui/UIUtils.h"
#include "PG/ui/UIPositionCalculator.h"
#include "PG/graphics/NodeCreator.h"
#include "PG/app/StyleSheet.h"
#include "PG/app/GameConstants.h"
#include "PG/core/BindableValue.h"

#include "PG/console/ConsoleCommandRegistry.h"
#include "PG/console/ConsoleCommandArgument.h"
#include "PG/console/CommandSetHandle.h"
#include "PG/console/ConsoleController.h"

#include <list>

namespace PG {
namespace Internal {

//--------------------------------------------------------
struct ConsoleScene::State
{
	NodeHandle								consoleBackground;
	NodeHandle								consoleInput;
	std::vector<NodeHandle>					consoleOutput;
	std::list<BindableValue<std::string>>	consoleOutputLines;
};

//--------------------------------------------------------
ConsoleScene::ConsoleScene()
: m_State(new State)
{}

//--------------------------------------------------------
ConsoleScene::~ConsoleScene()
{
}

//--------------------------------------------------------
void ConsoleScene::initScene(SceneHandle scene)
{
	m_Scene = scene;
	
	auto& consoleController = m_Scene.scene->getConsoleController();
	
	m_Scene.scene->setBackgroundColour(Colour(20, 20, 20));
	
	UIUtils::createTextNodeForValue(Point(20, 220), Colour(255, 255, 200), 20,
									Alignment::kLeft, m_State->consoleInput, m_Scene,
									consoleController.getConsoleInput());
	
	for (int line = 0; line < 10; ++line)
	{
		m_State->consoleOutput.emplace_back();
		m_State->consoleOutputLines.emplace_back("");
	}
	
	auto lineIt = m_State->consoleOutputLines.begin();
	for (size_t line = 0; line < 10; ++line, ++lineIt)
	{
		UIUtils::createTextNodeForValue(Point(20, (line + 1) * 20), Colour(128, 255, 255), 20,
										Alignment::kLeft, m_State->consoleOutput[line], m_Scene,
										*lineIt);
	}
	
	consoleController.getConsoleOutputSize().setBinding([&, this](const int& size) {
		
		auto lineIt = m_State->consoleOutputLines.rbegin();
		auto outputIt = consoleController.getConsoleOutput().rbegin();
		for (; lineIt != m_State->consoleOutputLines.rend(); ++lineIt)
		{
			if (outputIt != consoleController.getConsoleOutput().rend())
			{
				*lineIt = *outputIt;
				++outputIt;
			}
			else
			{
				*lineIt = "";
			}
		}
	});
}

//--------------------------------------------------------
void ConsoleScene::update(double dt)
{
}

//--------------------------------------------------------
void ConsoleScene::keyDown(KeyCode code, KeyModifier mods)
{
	m_Scene.scene->getConsoleController().keyPressed(code);
}

}
}
