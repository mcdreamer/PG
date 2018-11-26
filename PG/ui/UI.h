#pragma once

#include "PG/ui/UIMessage.h"
#include "PG/ui/UIElement.h"
#include "PG/app/StyleSheet.h"
#include "PG/graphics/Node.h"

namespace PG {

struct StyleSheet;
class UIMessageQueuePoster;
struct NodeHandle;
	
//--------------------------------------------------------
class UILayer
{
public:
    UILayer(NodeHandle uiRoot)
    : m_UIRoot(uiRoot)
    {}
	
	NodeHandle             	getUIRoot() { return m_UIRoot; }
    
	void					setStyleSheet(const StyleSheet& styleSheet);
	const StyleSheet&		getStyleSheet() const;
	
	void					pushElement(UIElement* element);
	
private:
	friend class UI;
	
    UIElementArray			m_UIStack;
    NodeHandle             	m_UIRoot;
	StyleSheet				m_StyleSheet;
};

//--------------------------------------------------------
class UI
{
public:
	UIMessageQueuePoster	getMessagePoster();
	
	bool					handleClick(UILayer& activeLayer, const Point& screenPt);
	void					update(UILayer& activeLayer);
	
private:
	PGUIMessageQueue    	m_MessageQueue;
};
	
}
