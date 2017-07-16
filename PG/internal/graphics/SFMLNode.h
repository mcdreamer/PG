#pragma once

#include "PG/graphics/Node.h"
#include "PG/core/Rect.h"
#include "PG/core/Size.h"

#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>

namespace PG {
namespace Internal {

//--------------------------------------------------------
class ISFMLNodeProvider
{
public:
    virtual ~ISFMLNodeProvider() {}
    
    virtual sf::Drawable*   getNode()=0;
    virtual const bool      isRemoved() const=0;
    
    NodePtrArray            m_ChildNodes;
};

//--------------------------------------------------------
template <typename TNode>
class SFMLNodeBase : public INode, public ISFMLNodeProvider
{
public:
    SFMLNodeBase()
    : m_Removed(false)
    {}

    virtual sf::Drawable* getNode() override { return &m_Node; }
    
    virtual void setPosition(PGPoint point) override
    {
        m_Node.setPosition((float)point.x, (float)point.y);
    }
	
	virtual void setSize(PGSize size) override
	{
	}
    
    virtual PGPoint getPosition() const override
    {
        return PGPoint(m_Node.getPosition().x, m_Node.getPosition().y);
    }
    
    virtual PGRect getRect() const override
    {
        return PGRect(getPosition(), getSize());
    }
    
    virtual NodeHandle addChild(std::unique_ptr<INode>& node) override
    {
        m_ChildNodes.emplace_back(node.release());

        return NodeHandle(m_ChildNodes.back().get());
    }
    
    virtual std::vector<INode*> getChildren() override
    {
        // AD#: !!!
        std::vector<INode*> children;
        children.reserve(m_ChildNodes.size());
    
        for (const auto& child : m_ChildNodes)
        {
            children.push_back(child.get());
        }
    
        return children;
    }
    
    virtual void clearChildren() override
    {
        for (auto& child : m_ChildNodes)
        {
            child->removeFromParent();
        }
        
        m_ChildNodes.clear();
    }
    
    virtual void addUserData(const std::string& key, const std::string& value) override
    {
//        [m_Node.userData setValue:StringUtils::stdStringToNSString(value) forKey:StringUtils::stdStringToNSString(key)];
    }
    
    virtual void addUserData(const std::string& key, const void* value) override
    {
//        [m_Node.userData setValue:[NSValue valueWithPointer:value] forKey:StringUtils::stdStringToNSString(key)];
    }
    
    virtual void addUserDataInt(const std::string& key, const int value) override
    {
//        [m_Node.userData setValue:[NSNumber numberWithInt:value] forKey:StringUtils::stdStringToNSString(key)];
    }
    
    virtual std::string getUserDataString(const std::string& key) const override
    {
//        if (m_Node.userData)
//        {
//            NSString* s = [m_Node.userData valueForKey:StringUtils::stdStringToNSString(key)];
//            return StringUtils::nsStringToStdString(s);
//        }

        return "";
    }

    virtual void* getUserDataPtr(const std::string& key) const override
    {
        void* ptr = nullptr;

//        if (m_Node.userData)
//        {
//            NSValue* v = [m_Node.userData valueForKey:StringUtils::stdStringToNSString(key)];
//            [v getValue:&ptr];
//        }

        return ptr;
    }
    
    virtual int getUserDataInt(const std::string& key) const override
    {
//        if (m_Node.userData)
//        {
//            NSNumber* i = [m_Node.userData valueForKey:StringUtils::stdStringToNSString(key)];
//            return [i intValue];
//        }
        
        return 0;
    }

    virtual void removeFromParent() override
    {
        m_Removed = true;
    }
    
    virtual std::vector<INode*> findNodesAtPoint(double x, double y) override
    {
        return {};
    }
    
    virtual void setText(const std::string& text) override {}

    virtual void setColour(const Colour& colour) override {}
    virtual void removeColour() override {}

    virtual const bool isRemoved() const override { return m_Removed; }

protected:
    friend class SFMLScene;

    TNode                               m_Node;
    std::map<std::string, std::string>  m_Data; // AD: !!!
    bool                                m_Removed;
};

//--------------------------------------------------------
class SFMLNode : public SFMLNodeBase<sf::Sprite>
{
public:
    virtual NodeType getType() const override { return NodeType::kNode; }
    
    virtual PGSize getSize() const override
    {
        return PGSize(0, 0);
    }
};

//--------------------------------------------------------
class SFMLSpriteNode : public SFMLNodeBase<sf::Sprite>
{
public:
    SFMLSpriteNode(const std::string& imageName)
    {
        if (texture.loadFromFile(imageName))
        {
            m_Node = sf::Sprite(texture);
            m_Node.setOrigin((float)getSize().width / 2.0f, (float)getSize().height / 2.0f);
        }
    }
    
    virtual PGSize getSize() const override
    {
        return PGSize(m_Node.getTextureRect().width, m_Node.getTextureRect().height);
    }

    virtual NodeType getType() const override { return NodeType::kSprite; }

    virtual void setColour(const Colour& colour) override
    {
        m_Node.setColor(sf::Color(colour.r, colour.g, colour.b));
    }

    virtual void removeColour() override
    {
        m_Node.setColor(sf::Color());
    }
	
private:
	sf::Texture texture;
};

//--------------------------------------------------------
class SFMLColourNode : public SFMLNodeBase<sf::RectangleShape>
{
public:
    SFMLColourNode(const Colour& colour, const PGSize& size)
    {
        m_Node = sf::RectangleShape(sf::Vector2f((float)size.width, (float)size.height));
        m_Node.setOrigin((float)size.width / 2.0f, (float)size.height / 2.0f);
        setColour(colour);
    }
	
	virtual void setSize(PGSize size) override
	{
		m_Node.setSize(sf::Vector2f((float)size.width, (float)size.height));
	}
    
    virtual PGSize getSize() const override
    {
        return PGSize(m_Node.getSize().x, m_Node.getSize().y);
    }
    
    virtual NodeType getType() const override { return NodeType::kSprite; }
    
    virtual void setColour(const Colour& colour) override
    {
        m_Node.setFillColor(sf::Color(colour.r, colour.g, colour.b));
    }
    
    virtual void removeColour() override
    {
        m_Node.setFillColor(sf::Color());
    }
};

//--------------------------------------------------------
class SFMLFontCache
{
public:
	//--------------------------------------------------------
	const sf::Font* getOrCreateFont(const std::string& fontName)
	{
		auto fontIt = std::find_if(m_Fonts.begin(), m_Fonts.end(), [&](const auto& font) { return font.first == fontName; });
		if (fontIt != m_Fonts.end())
		{
			return &fontIt->second;
		}

		m_Fonts.emplace_back(fontName, sf::Font());
		auto* font = &m_Fonts.back().second;
		font->loadFromFile(fontName);

		return font;
	}

private:
	std::vector<std::pair<std::string, sf::Font>> m_Fonts;
};

//--------------------------------------------------------
class SFMLLabelNode : public SFMLNodeBase<sf::Text>
{
public:
    SFMLLabelNode(const std::string& fontName, int fontSize);

    virtual PGSize getSize() const override
    {
        return PGSize(m_Node.getGlobalBounds().width, m_Node.getGlobalBounds().height);
    }
    
    virtual NodeType getType() const override { return NodeType::kText; }

    virtual void setText(const std::string& text) override
    {
        auto oldPos = getPosition();
        m_Node.setString(sf::String(text));
        setPosition(oldPos);
        m_Node.setOrigin((float)getSize().width / 2.0f, (float)getSize().height / 2.0f);
    }
    
    virtual void setPosition(PGPoint point) override
    {
        m_Node.setPosition((float)point.x - m_Node.getLocalBounds().left,
                           (float)point.y - m_Node.getLocalBounds().top);
    }
    
    virtual PGPoint getPosition() const override
    {
        return PGPoint(m_Node.getPosition().x + m_Node.getLocalBounds().left,
                       m_Node.getPosition().y + m_Node.getLocalBounds().top);
    }
    
    virtual void setColour(const Colour& colour) override
    {
        m_Node.setFillColor(sf::Color(colour.r, colour.g, colour.b));
    }
    
    virtual void removeColour() override
    {
        m_Node.setFillColor(sf::Color());
    }
};

}
}
