#pragma once

#include "PG/menu/MenuNode.h"
#include "PG/core/Point.h"

#include <stack>
#include <boost/optional.hpp>

namespace PG {

class IScene;
class INode;

//--------------------------------------------------------
class IMenuManagerCallback
{
public:
    virtual ~IMenuManagerCallback() {}

    virtual void itemWithTagActioned(int tag)=0;
};

//--------------------------------------------------------
class MenuManager
{
public:
    //--------------------------------------------------------
    struct MenuCursor
    {
        MenuCursor()
        : currItem(nullptr)
        {}
        
        std::stack<const MenuNode*> navigationStack;
        const MenuNode*             currItem;
    };

    //--------------------------------------------------------
    MenuManager(IMenuManagerCallback& callback, const IScene& scene, const MenuNode& topLevelNode)
    : m_Callback(callback), m_Scene(scene), m_TopLevelNode(topLevelNode),
    m_Layer(nullptr)
    {}
    
    MenuManager(const MenuManager& other)=delete;

    void initAndDisplayMenu(INode& layer);
    
    void moveSelectionUp();
    void moveSelectionDown();
    void actionSelection();
    void navigateBack();
    void actionMenuNodeAtPoint(const PGPoint& pt);

private:
    IMenuManagerCallback&   m_Callback;
    const IScene&           m_Scene;
    const MenuNode          m_TopLevelNode;
    MenuCursor              m_Cursor;
    INode*                  m_Layer;
    
    void enterMenu(const MenuNode& node);
    void presentOnScene(const MenuNode& parentNode);
    void highlightItem(const MenuNode& node);
};

}
