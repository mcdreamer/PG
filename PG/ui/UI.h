#pragma once

#include "PG/ui/UIMessage.h"
#include "PG/ui/UIElement.h"
#include "PG/app/StyleSheet.h"
#include "PG/graphics/Node.h"

#include <stack>

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
	
	NodeHandle             	m_UIRoot;
    UIElementArray			m_UIStack;
	StyleSheet				m_StyleSheet;
};

	

//--------------------------------------------------------
class UI
{
public:
	UI(TagReceiver* uiParent)
	: m_UIParent(uiParent)
	{}
	
	UIMessageQueuePoster		getMessagePoster();
	
	bool						handleClick(UILayer& activeLayer, const Point& screenPt);
	void						update(UILayer& activeLayer);
	
	void 						pushReceiver(TagReceiver* receiver, const bool replace);
	void 						popReceiver();
	
private:
	PGUIMessageQueue    		m_MessageQueue;
	TagReceiver* 				m_UIParent;
	std::stack<TagReceiver*>	m_ReceiverStack;
};
	
}
