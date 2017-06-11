#pragma once

#include "Node.h"

namespace PG {

class IResourceHandler;

//--------------------------------------------------------
class NodeCreator
{
public:
    static NodePtr  createNode();
    static NodePtr  createSpriteNode(const std::string& imageName);
    static NodePtr  createColourNode(const Colour& colour, const PGSize& size);
    static NodePtr  createTextNode(const std::string& fontName, double fontSize);
};

}
