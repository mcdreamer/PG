#include "PG/internal/graphics/SFMLNode.h"
#include "PG/graphics/NodeCreator.h"
#include "PG/io/IResourceHandler.h"

namespace PG {
namespace Internal {

IResourceHandler* resourceHandler = nullptr;
std::vector<std::pair<std::string, sf::Font>> SFMLLabelNode::s_Fonts;

}

//--------------------------------------------------------
NodePtr NodeCreator::createNode()
{
    return std::make_unique<Internal::SFMLNode>();
}

//--------------------------------------------------------
NodePtr NodeCreator::createSpriteNode(const std::string& imageName)
{
    return std::make_unique<Internal::SFMLSpriteNode>(Internal::resourceHandler->getResourcePath(imageName, "png"));
}

//--------------------------------------------------------
NodePtr NodeCreator::createColourNode(unsigned char r, unsigned char g, unsigned char b, float a, const PGSize& size)
{
    return std::make_unique<Internal::SFMLColourNode>(r, g, b, a, size);
}

//--------------------------------------------------------
NodePtr NodeCreator::createTextNode(const std::string& fontName, double fontSize)
{
    return std::make_unique<Internal::SFMLLabelNode>(Internal::resourceHandler->getResourcePath(fontName, "ttf"), fontSize);
}

}
