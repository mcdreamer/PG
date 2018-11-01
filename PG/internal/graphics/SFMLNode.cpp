#include "PG/internal/graphics/SFMLNode.h"
#include "PG/graphics/NodeCreator.h"
#include "PG/io/IResourceHandler.h"

namespace PG {
namespace Internal {

IResourceHandler* g_ResourceHandler = nullptr;
SFMLFontCache* g_FontCache = nullptr;

//--------------------------------------------------------
SFMLLabelNode::SFMLLabelNode(const std::string& fontName, const char* data, const size_t size, int fontSize, Alignment alignment)
: m_Alignment(alignment)
{
	const auto* font = g_FontCache->getOrCreateFont(fontName, data, size);
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
	const auto imageData = Internal::g_ResourceHandler->getResourceData(imageName);
	if (imageData.data)
	{
		return std::make_unique<Internal::SFMLSpriteNode>(imageData.data, imageData.size);
	}

	return {};
}

//--------------------------------------------------------
NodePtr NodeCreator::createColourNode(const Colour& colour, const Size& size)
{
    return std::make_unique<Internal::SFMLColourNode>(colour, size);
}

//--------------------------------------------------------
NodePtr NodeCreator::createTextNode(const std::string& fontName, double fontSize)
{
	const auto fontData = Internal::g_ResourceHandler->getResourceData(fontName);
	if (fontData.data)
	{
		return std::make_unique<Internal::SFMLLabelNode>(fontName,
														fontData.data,
														fontData.size,
														fontSize,
														Alignment::kCentre);
	}

	return {};
}

//--------------------------------------------------------
NodePtr NodeCreator::createTextNode(const std::string& fontName, double fontSize, Alignment alignment)
{
	const auto fontData = Internal::g_ResourceHandler->getResourceData(fontName);
	if (fontData.data)
	{
		return std::make_unique<Internal::SFMLLabelNode>(fontName,
														fontData.data,
														fontData.size,
														fontSize,
														alignment);
	}

	return {};
}

}
