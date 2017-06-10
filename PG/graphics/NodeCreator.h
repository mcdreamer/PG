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
    static NodePtr  createColourNode(unsigned char r, unsigned char g, unsigned char b, float a, const PGSize& size);
    static NodePtr  createTextNode(const std::string& fontName, double fontSize);
};

}
