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
void UI::update(UILayer& activeLayer)
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
			{
				bool handled = false;
				
				if (msg.target)
				{
					handled = msg.target->receiveTag(msg.tag);
				}
				
				if (!handled && !m_ReceiverStack.empty() && m_ReceiverStack.top())
				{
					handled = m_ReceiverStack.top()->receiveTag(msg.tag);
				}
				
				if (!handled && m_UIParent)
				{
					handled = m_UIParent->receiveTag(msg.tag);
				}
				break;
			}
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
	
//-----------------------------------------------------------------
void UI::pushReceiver(TagReceiver* receiver, const bool replace)
{
	if (replace)
	{
		m_ReceiverStack = std::stack<TagReceiver*>();
	}
	
	m_ReceiverStack.push(receiver);
}
	
//-----------------------------------------------------------------
void UI::popReceiver()
{
	if (!m_ReceiverStack.empty())
	{
		m_ReceiverStack.pop();
	}
}
	
}
