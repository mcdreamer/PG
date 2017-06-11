#pragma once

#include "PG/ui/PGUIMessage.h"
#include "PG/ui/PGUIElement.h"
#include "PG/app/StyleSheet.h"

namespace PG {

class IScene;
struct StyleSheet;

//--------------------------------------------------------
class PGUI
{
public:
    PGUI(IScene& scene)
    : m_Scene(scene)
    {}
    
	void				setStyleSheet(const StyleSheet& styleSheet);
	const StyleSheet&	getStyleSheet() const;
	
	void				pushElement(PGUIElement* element);
    bool				handleClick(const PGPoint& screenPt);
    void				update();
	
private:
    PGUIMessageQueue    m_MessageQueue;
    PGUIElementArray    m_UIStack;
    IScene&             m_Scene;
	StyleSheet			m_StyleSheet;
};

}
