#include "PG/internal/ui/Console.h"
#include "PG/ui/UIUtils.h"
#include "PG/ui/UIPositionCalculator.h"
#include "PG/graphics/NodeCreator.h"
#include "PG/app/StyleSheet.h"
#include "PG/app/GameConstants.h"
#include "PG/app/AppHostServices.h"
#include "PG/core/BindableValue.h"

#include "PG/console/ConsoleCommandRegistry.h"
#include "PG/console/ConsoleCommandArgument.h"
#include "PG/console/CommandSetHandle.h"
#include "PG/console/ConsoleController.h"

#include <list>

namespace PG {
namespace Internal {

const int kSizePerLine = 20;
const int kLeftPadding = 20;
const Colour kBackgroundColour(20, 20, 20);
const Colour kInputLineColour(255, 255, 200);
const Colour kOutputLineColour(128, 255, 255);

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
: m_AppHostServices(nullptr),
m_State(new State)
{}

//--------------------------------------------------------
ConsoleScene::~ConsoleScene()
{
}

//--------------------------------------------------------
void ConsoleScene::initScene(AppHostServices& appHostServices, SceneHandle scene)
{
	m_Scene = scene;
	m_AppHostServices = &appHostServices;
	
	auto& consoleController = m_AppHostServices->getConsoleController();
	const auto& styleSheet = m_AppHostServices->getStyleSheet();
	
	m_Scene.scene->setBackgroundColour(kBackgroundColour);
	
	const int numOutputLines = (int)(m_Scene.scene->getSceneSize().height / (double)kSizePerLine) - 2;
	if (numOutputLines < 1)
	{
		return;
	}
	
	UIPositionCalculator posCalc(m_Scene.scene->getSceneSize());
	const auto linePositions = posCalc.multipleTopToBottom(Point(kLeftPadding, kSizePerLine),
														   numOutputLines + 1,
														   kSizePerLine);
	
	UIUtils::createTextNodeForValue(linePositions.back(), kInputLineColour, kSizePerLine,
									Alignment::kLeft, styleSheet, m_State->consoleInput, m_Scene,
									consoleController.getConsoleInput());
	
	createConsoleOutlineLinesNodes(linePositions, numOutputLines, kSizePerLine);
	
	consoleController.getConsoleOutputSize().setBinding([this](const int& size) { updateOutput(); });
}

//--------------------------------------------------------
void ConsoleScene::keyDown(KeyCode code, KeyModifier mods)
{
	m_AppHostServices->getConsoleController().keyPressed(code);
}

//--------------------------------------------------------
void ConsoleScene::createConsoleOutlineLinesNodes(const std::vector<Point>& linePositions,
												  const int numOutputLines,
												  const int sizePerLine)
{
	auto& styleSheet = m_AppHostServices->getStyleSheet();

	for (int line = 0; line < numOutputLines; ++line)
	{
		m_State->consoleOutput.emplace_back();
		m_State->consoleOutputLines.emplace_back("");
	}
	
	auto lineIt = m_State->consoleOutputLines.begin();
	for (size_t line = 0; line < (size_t)numOutputLines; ++line, ++lineIt)
	{
		UIUtils::createTextNodeForValue(linePositions[line], kOutputLineColour, sizePerLine,
										Alignment::kLeft, styleSheet, m_State->consoleOutput[line], m_Scene,
										*lineIt);
	}
}

//--------------------------------------------------------
void ConsoleScene::updateOutput()
{
	auto& consoleController = m_AppHostServices->getConsoleController();
	
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
}

}
}
