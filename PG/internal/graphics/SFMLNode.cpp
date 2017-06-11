#include "PG/internal/graphics/SFMLNode.h"
#include "PG/graphics/NodeCreator.h"
#include "PG/io/IResourceHandler.h"

namespace PG {
namespace Internal {

IResourceHandler* g_ResourceHandler = nullptr;
SFMLFontCache* g_FontCache = nullptr;

//--------------------------------------------------------
SFMLLabelNode::SFMLLabelNode(const std::string& fontName, int fontSize)
{
	const auto* font = g_FontCache->getOrCreateFont(fontName);
	if (font)
	{
		m_Node = sf::Text("", *font, (unsigned int)fontSize);
		m_Node.setFillColor(sf::Color(255, 0, 0));
	}
}

}

//--------------------------------------------------------
NodePtr NodeCreator::createNode()
{
    return std::make_unique<Internal::SFMLNode>();
}

//--------------------------------------------------------
NodePtr NodeCreator::createSpriteNode(const std::string& imageName)
{
    return std::make_unique<Internal::SFMLSpriteNode>(Internal::g_ResourceHandler->getResourcePath(imageName, "png"));
}

//--------------------------------------------------------
NodePtr NodeCreator::createColourNode(const Colour& colour, const PGSize& size)
{
    return std::make_unique<Internal::SFMLColourNode>(colour, size);
}

//--------------------------------------------------------
NodePtr NodeCreator::createTextNode(const std::string& fontName, double fontSize)
{
    return std::make_unique<Internal::SFMLLabelNode>(Internal::g_ResourceHandler->getResourcePath(fontName, "ttf"), fontSize);
}

}
