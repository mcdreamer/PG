#include "UITests.h"
#include "gtest/gtest.h"

#include "PG/core/PGRectUtils.h"
#include "PG/ui/PGUIUtils.h"
#include "PG/ui/PGUI.h"
#include "PG/ui/PGButton.h"
#include "PG/graphics/NodeCreator.h"
#include "PG/graphics/Scene.h"

using namespace PG;

//--------------------------------------------------------
TEST(UITests,nodeContains)
{
    auto node = NodeCreator::createColourNode(Colour(), PGSize(10, 10));
    NodeHandle root(node.get());
    root.node->setPosition(PGPoint(10, 10));
    
    EXPECT_FALSE(PGRectUtils::containsPoint(root.node->getRect(), PGPoint(0, 0)));
    EXPECT_TRUE(PGRectUtils::containsPoint(root.node->getRect(), PGPoint(5, 5)));
    EXPECT_TRUE(PGRectUtils::containsPoint(root.node->getRect(), PGPoint(6, 6)));
    EXPECT_TRUE(PGRectUtils::containsPoint(root.node->getRect(), PGPoint(10, 10)));
    EXPECT_TRUE(PGRectUtils::containsPoint(root.node->getRect(), PGPoint(14, 14)));
    EXPECT_TRUE(PGRectUtils::containsPoint(root.node->getRect(), PGPoint(15, 15)));
    EXPECT_FALSE(PGRectUtils::containsPoint(root.node->getRect(), PGPoint(16, 16)));
}

//--------------------------------------------------------
TEST(UITests,testPointMapping)
{
    auto rNode = NodeCreator::createNode();
    NodeHandle root(rNode.get());

    auto rootSize = root.node->getSize();
    EXPECT_EQ(PGSize(0, 0), rootSize);

    auto dNode = NodeCreator::createColourNode(Colour(), PGSize(15, 15));
    NodeHandle dialogRoot = root.node->addChild(dNode);
    dialogRoot.node->setPosition(PGPoint(10, 10));

    auto dlgSize = dialogRoot.node->getSize();
    EXPECT_EQ(PGSize(15, 15), dlgSize);

    rootSize = root.node->getSize();
    EXPECT_EQ(PGSize(0, 0), rootSize);

    auto c = NodeCreator::createColourNode(Colour(), PGSize(6, 6));
    auto child = dialogRoot.node->addChild(c);
    child.node->setPosition(PGPoint(5, 5));

    EXPECT_EQ(PGSize(0, 0), rootSize);
    EXPECT_EQ(PGPoint(0, 0), root.node->getPosition());

    auto mappedRootPt = PGUIUtils::calculateNodeRelativePoint(PGPoint(20, 21), root);
    EXPECT_EQ(PGPoint(20, 21), mappedRootPt);
    EXPECT_TRUE(PGRectUtils::isEmpty(root.node->getRect()));
    
    auto mappedDlgPt = PGUIUtils::calculateNodeRelativePoint(mappedRootPt, dialogRoot);

    EXPECT_EQ(PGPoint(10, 11), mappedDlgPt);
    EXPECT_TRUE(PGRectUtils::containsPoint(dialogRoot.node->getRect(), mappedDlgPt));
    
    auto mappedChildPt = PGUIUtils::calculateNodeRelativePoint(mappedDlgPt, child);
    
    EXPECT_EQ(PGPoint(5, 6), mappedChildPt);
    EXPECT_TRUE(PGRectUtils::containsPoint(child.node->getRect(), mappedChildPt));
}

namespace
{
    //--------------------------------------------------------
    class TestUIElement : public PGUIElement
    {
    public:
        TestUIElement()
        : m_LastReceivedTag(-1)
        {}
    
        virtual void init(const StyleSheet& styleSheet) override {}

        virtual void receiveTag(const int tag, PGUIMessageQueuePoster& msgPoster) override
        {
            m_LastReceivedTag = tag;
        }
        
        int m_LastReceivedTag;
    };
}

//--------------------------------------------------------
TEST(UITests,testClickHandling)
{
    auto scene = SceneCreator::createScene();
    PGUI ui(*scene);
	
	StyleSheet styleSheet;
	styleSheet.uiFontName = "OpenSans-Regular";
//	styleSheet. = PGSize(1000, 1000);
	
	ui.setStyleSheet(styleSheet);
	
    TestUIElement testElement;
    
    ui.pushElement(new PGButton(testElement, PGPoint(100, 100), "Test Button", 1234, PGSize(80, 20)));
    
    const bool clickHandled = ui.handleClick(PGPoint(100, 100));
    EXPECT_TRUE(clickHandled);
    
    ui.update();
    EXPECT_EQ(1234, testElement.m_LastReceivedTag);
}
