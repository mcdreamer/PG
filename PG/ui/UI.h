#pragma once

#include "PG/ui/UIMessage.h"
#include "PG/ui/UIElement.h"
#include "PG/app/StyleSheet.h"

namespace PG {

class IScene;
struct StyleSheet;
class UIMessageQueuePoster;

//--------------------------------------------------------
class UI
{
public:
    UI(IScene& scene)
    : m_Scene(scene)
    {}
    
	void					setStyleSheet(const StyleSheet& styleSheet);
	const StyleSheet&		getStyleSheet() const;
	UIMessageQueuePoster	getMessagePoster();
	
	void					pushElement(UIElement* element);
    bool					handleClick(const Point& screenPt);
    void					update();
	
private:
    PGUIMessageQueue    	m_MessageQueue;
    UIElementArray			m_UIStack;
    IScene&             	m_Scene;
	StyleSheet				m_StyleSheet;
};

}
