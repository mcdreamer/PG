#include "PG/ui/UI.h"
#include "PG/ui/UIMessageQueuePoster.h"

#include <algorithm>

namespace PG {

//--------------------------------------------------------
void UILayer::pushElement(UIElement* element)
{
    m_UIStack.emplace_back(element);
    m_UIStack.back()->show(m_UIRoot, m_StyleSheet);
}

//--------------------------------------------------------
void UILayer::setStyleSheet(const StyleSheet& styleSheet)
{
	m_StyleSheet = styleSheet;
}

//--------------------------------------------------------
const StyleSheet& UILayer::getStyleSheet() const
{
	return m_StyleSheet;
}

//--------------------------------------------------------
UIMessageQueuePoster UI::getMessagePoster()
{
	return UIMessageQueuePoster(m_MessageQueue);
}

//--------------------------------------------------------
bool UI::handleClick(UILayer& activeLayer, const Point& screenPt)
{
	if (!activeLayer.m_UIStack.empty())
	{
		auto msgPoster = getMessagePoster();
		
		for (auto elementIt = activeLayer.m_UIStack.rbegin();
			 elementIt != activeLayer.m_UIStack.rend();
			 ++elementIt)
		{
			if ((*elementIt)->handleClick(screenPt, msgPoster))
			{
				return true;
			}
		}
	}
	
	return false;
}

namespace
{
	//--------------------------------------------------------
	void removeElement(const UIElement* toRemove, UIElementArray& uiStack)
	{
		uiStack.erase(std::remove_if(uiStack.begin(), uiStack.end(), [&](const auto& e) { return e.get() == toRemove; }), uiStack.end());
	}
}

//--------------------------------------------------------
void UI::update(UILayer& activeLayer,
				const std::vector<TagReceiver*>& parents)
{
	while (!m_MessageQueue.empty())
	{
		auto msg = m_MessageQueue.front();
		
		switch (msg.type)
		{
			case UIMessage::kClose:
				if (msg.target)
				{
					auto* uiElement = dynamic_cast<UIElement*>(msg.target);
					if (uiElement)
					{
						uiElement->close();
						removeElement(uiElement, activeLayer.m_UIStack);
					}
				}
				break;
				
			case UIMessage::kSendTag:
				if (!msg.target || !msg.target->receiveTag(msg.tag))
				{
					for (auto parentIt = parents.begin();
						 parentIt != parents.end();
						 ++parentIt)
					{
						if ((*parentIt)->receiveTag(msg.tag))
						{
							break;
						}
					}
				}
				break;
				
			case UIMessage::kPushElement:
				if (msg.target)
				{
					auto* uiElement = dynamic_cast<UIElement*>(msg.target);
					activeLayer.pushElement(uiElement);
				}
				break;
		}
		
		m_MessageQueue.pop();
	}
}
	
}
