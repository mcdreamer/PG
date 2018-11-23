#include "PG/ui/UI.h"
#include "PG/ui/UIMessageQueuePoster.h"
#include "PG/graphics/Scene.h"

#include <algorithm>

namespace PG {

//--------------------------------------------------------
void UI::pushElement(UIElement* element)
{
    m_UIStack.emplace_back(element);
    m_UIStack.back()->show(m_Scene.getUIRoot(), m_StyleSheet);
}

//--------------------------------------------------------
bool UI::handleClick(const Point& screenPt)
{
    if (!m_UIStack.empty())
    {
		auto msgPoster = getMessagePoster();

        for (auto elementIt = m_UIStack.rbegin(); elementIt != m_UIStack.rend(); ++elementIt)
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
void UI::update()
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
                    uiElement->close();
                    removeElement(uiElement, m_UIStack);
                }
                break;

            case UIMessage::kSendTag:
                if (msg.target)
                {
                    UIMessageQueuePoster msgPoster(m_MessageQueue);
                    msg.target->receiveTag(msg.tag);
                }
                break;

            case UIMessage::kPushElement:
                if (msg.target)
                {
					auto* uiElement = dynamic_cast<UIElement*>(msg.target);
                    pushElement(uiElement);
                }
                break;
        }

        m_MessageQueue.pop();
    }
}

//--------------------------------------------------------
void UI::setStyleSheet(const StyleSheet& styleSheet)
{
	m_StyleSheet = styleSheet;
}

//--------------------------------------------------------
const StyleSheet& UI::getStyleSheet() const
{
	return m_StyleSheet;
}

//--------------------------------------------------------
UIMessageQueuePoster UI::getMessagePoster()
{
	return UIMessageQueuePoster(m_MessageQueue);
}

}
