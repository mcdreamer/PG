#include "UITests.h"
#include "TestResourceHandler.h"
#include "TestSoundController.h"
#include "TestPlatformServices.h"
#include "gtest/gtest.h"

#include "PG/core/RectUtils.h"
#include "PG/ui/UIUtils.h"
#include "PG/ui/UI.h"
#include "PG/ui/Button.h"
#include "PG/ui/UIPositionCalculator.h"
#include "PG/graphics/NodeCreator.h"
#include "PG/graphics/Scene.h"
#include "PG/console/ConsoleController.h"
#include "PG/app/AppHostServices.h"

using namespace PG;

//--------------------------------------------------------
TEST(UITests,nodeContains)
{
    auto node = NodeCreator::createColourNode(Colour(), Size(10, 10));
    NodeHandle root(node.get());
    root.node->setPosition(Point(10, 10));
    
    EXPECT_FALSE(RectUtils::containsPoint(root.node->getRect(), Point(0, 0)));
    EXPECT_TRUE(RectUtils::containsPoint(root.node->getRect(), Point(5, 5)));
    EXPECT_TRUE(RectUtils::containsPoint(root.node->getRect(), Point(6, 6)));
    EXPECT_TRUE(RectUtils::containsPoint(root.node->getRect(), Point(10, 10)));
    EXPECT_TRUE(RectUtils::containsPoint(root.node->getRect(), Point(14, 14)));
    EXPECT_TRUE(RectUtils::containsPoint(root.node->getRect(), Point(15, 15)));
    EXPECT_FALSE(RectUtils::containsPoint(root.node->getRect(), Point(16, 16)));
}

//--------------------------------------------------------
TEST(UITests,testPointMapping)
{
    auto rNode = NodeCreator::createNode();
    NodeHandle root(rNode.get());

    auto rootSize = root.node->getSize();
    EXPECT_EQ(Size(0, 0), rootSize);

    auto dNode = NodeCreator::createColourNode(Colour(), Size(15, 15));
    NodeHandle dialogRoot = root.node->addChild(dNode);
    dialogRoot.node->setPosition(Point(10, 10));

    auto dlgSize = dialogRoot.node->getSize();
    EXPECT_EQ(Size(15, 15), dlgSize);

    rootSize = root.node->getSize();
    EXPECT_EQ(Size(0, 0), rootSize);

    auto c = NodeCreator::createColourNode(Colour(), Size(6, 6));
    auto child = dialogRoot.node->addChild(c);
    child.node->setPosition(Point(5, 5));

    EXPECT_EQ(Size(0, 0), rootSize);
    EXPECT_EQ(Point(0, 0), root.node->getPosition());

    auto mappedRootPt = UIUtils::calculateNodeRelativePoint(Point(10, 11), root);
    EXPECT_EQ(Point(10, 11), mappedRootPt);
    EXPECT_TRUE(RectUtils::isEmpty(root.node->getRect()));
    
    auto mappedDlgPt = UIUtils::calculateNodeRelativePoint(mappedRootPt, dialogRoot);
    EXPECT_EQ(Point(7.5, 8.5), mappedDlgPt);
    EXPECT_TRUE(RectUtils::containsPoint(dialogRoot.node->getRect(), mappedDlgPt));
    
    auto mappedChildPt = UIUtils::calculateNodeRelativePoint(mappedDlgPt, child);
    EXPECT_EQ(Point(5.5, 6.5), mappedChildPt);
    EXPECT_TRUE(RectUtils::containsPoint(child.node->getRect(), mappedChildPt));
}

namespace
{
    //--------------------------------------------------------
    class TestUIElement : public UIElement
    {
    public:
        TestUIElement()
        : m_LastReceivedTag(-1)
        {}
    
        virtual void initUIElement(const Size& parentSize, const StyleSheet& styleSheet) override {}

        virtual bool receiveTag(const int tag, UIMessageQueuePoster& msgPoster) override
        {
            m_LastReceivedTag = tag;

            return true;
        }
        
        int m_LastReceivedTag;
    };
}

//--------------------------------------------------------
TEST(UITests,testClickHandling)
{
	// ConsoleController consoleController;
	// SceneControllerPtr sceneController;
	// StyleSheet styleSheet;
	// TestResourceHandler resourceHandler;
	// TestSoundController soundController;
	// TestPlatformServices testPlatformServices;
	
	// AppHostServices appHostServices(styleSheet, consoleController, soundController, testPlatformServices, resourceHandler);
	
	// auto scene = SceneCreator::createScene(sceneController, appHostServices, Size());
    // UI ui(*scene);
	
	// styleSheet.uiFontName = "OpenSans-Regular";
	
	// ui.setStyleSheet(styleSheet);
	
    // TestUIElement testElement;
    
    // ui.pushElement(new Button(testElement, Point(100, 100), "Test Button", 1234, Size(80, 20)));
    
    // const bool clickHandled = ui.handleClick(Point(100, 100));
    // EXPECT_TRUE(clickHandled);
    
    // ui.update();
    // EXPECT_EQ(1234, testElement.m_LastReceivedTag);
}

//--------------------------------------------------------
TEST(UITests,testUIPositionCalculator)
{
	UIPositionCalculator posCalc(Size(10, 10));
	
	EXPECT_EQ(Point(1, 1), posCalc.fromTopLeftCorner(Size(1, 1)));
	EXPECT_EQ(Point(9, 1), posCalc.fromTopRightCorner(Size(1, 1)));
	EXPECT_EQ(Point(1, 9), posCalc.fromBottomLeftCorner(Size(1, 1)));
	EXPECT_EQ(Point(9, 9), posCalc.fromBottomRightCorner(Size(1, 1)));
	
	EXPECT_EQ(Point(1, 6), posCalc.fromLeftMid(Size(1, 1)));
	EXPECT_EQ(Point(9, 6), posCalc.fromRightMid(Size(1, 1)));
	EXPECT_EQ(Point(6, 1), posCalc.fromTopMid(Size(1, 1)));
	EXPECT_EQ(Point(6, 9), posCalc.fromBottomMid(Size(1, 1)));
	
	EXPECT_EQ(Point(5, 5), posCalc.atCentre());
	
	{
		const auto pts = posCalc.multipleLeftToRight(Point(0, 0), 3, 1.5);
		ASSERT_EQ((size_t)3, pts.size());
		EXPECT_EQ(Point(0, 0), pts[0]);
		EXPECT_EQ(Point(1.5, 0), pts[1]);
		EXPECT_EQ(Point(3, 0), pts[2]);
	}
	{
		const auto pts = posCalc.multipleTopToBottom(Point(0, 0), 3, 1.5);
		ASSERT_EQ((size_t)3, pts.size());
		EXPECT_EQ(Point(0, 0), pts[0]);
		EXPECT_EQ(Point(0, 1.5), pts[1]);
		EXPECT_EQ(Point(0, 3), pts[2]);
	}
	{
		const auto pts = posCalc.multipleAcrossCentre(0, 3, 1.5);
		ASSERT_EQ((size_t)3, pts.size());
		EXPECT_EQ(Point(0, 5), pts[0]);
		EXPECT_EQ(Point(1.5, 5), pts[1]);
		EXPECT_EQ(Point(3, 5), pts[2]);
	}
	{
		const auto pts = posCalc.multipleDownCentre(0, 3, 1.5);
		ASSERT_EQ((size_t)3, pts.size());
		EXPECT_EQ(Point(5, 0), pts[0]);
		EXPECT_EQ(Point(5, 1.5), pts[1]);
		EXPECT_EQ(Point(5, 3), pts[2]);
	}
}
