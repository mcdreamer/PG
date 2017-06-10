#pragma once

#include "PG/graphics/ViewHandle.h"

namespace sf
{
    class RenderWindow;
};

namespace PG {
namespace Internal {

class SFMLScene;

//--------------------------------------------------------
class SFMLViewHandle : public IViewHandle
{
public:
    SFMLViewHandle(sf::RenderWindow* view_)
    : view(view_), currentScene(nullptr)
    {}
    
    sf::RenderWindow*   view;
    SFMLScene*          currentScene;
};

}
}
