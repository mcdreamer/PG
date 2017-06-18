#include "PG/ui/PGUI.h"
#include "PG/ui/PGUIMessageQueuePoster.h"
#include "PG/graphics/Scene.h"

#include <algorithm>

namespace PG {

//--------------------------------------------------------
void PGUI::pushElement(PGUIElement* element)
{
    m_UIStack.emplace_back(element);
    m_UIStack.back()->show(m_Scene, m_StyleSheet);
}

//--------------------------------------------------------
bool PGUI::handleClick(const PGPoint& screenPt)
{
    if (!m_UIStack.empty())
    {
        PGUIMessageQueuePoster msgPoster(m_MessageQueue);

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
    void removeElement(const PGUIElement* toRemove, PGUIElementArray& uiStack)
    {
        uiStack.erase(std::remove_if(uiStack.begin(), uiStack.end(), [&](const auto& e) { return e.get() == toRemove; }), uiStack.end());
    }
}

//--------------------------------------------------------
void PGUI::update()
{
    while (!m_MessageQueue.empty())
    {
        auto msg = m_MessageQueue.front();

        switch (msg.type)
        {
            case PGUIMessage::kClose:
                if (msg.target)
                {
					auto* uiElement = dynamic_cast<PGUIElement*>(msg.target);
                    uiElement->close();
                    removeElement(uiElement, m_UIStack);
                }
                break;

            case PGUIMessage::kSendTag:
                if (msg.target)
                {
                    PGUIMessageQueuePoster msgPoster(m_MessageQueue);
                    msg.target->receiveTag(msg.tag, msgPoster);
                }
                break;

            case PGUIMessage::kPushElement:
                if (msg.target)
                {
					auto* uiElement = dynamic_cast<PGUIElement*>(msg.target);
                    pushElement(uiElement);
                }
                break;
        }

        m_MessageQueue.pop();
    }
}

//--------------------------------------------------------
void PGUI::setStyleSheet(const StyleSheet& styleSheet)
{
	m_StyleSheet = styleSheet;
}

//--------------------------------------------------------
const StyleSheet& PGUI::getStyleSheet() const
{
	return m_StyleSheet;
}

}
