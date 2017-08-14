#pragma once

#include "PG/graphics/Node.h"

namespace PG {

class IResourceHandler;
enum class Alignment;

//--------------------------------------------------------
class NodeCreator
{
public:
    static NodePtr  createNode();
    static NodePtr  createSpriteNode(const std::string& imageName);
    static NodePtr  createColourNode(const Colour& colour, const Size& size);
    static NodePtr  createTextNode(const std::string& fontName, double fontSize);
	static NodePtr  createTextNode(const std::string& fontName, double fontSize, Alignment alignment);
};

}
