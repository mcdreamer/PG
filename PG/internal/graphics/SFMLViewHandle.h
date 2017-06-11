#pragma once

#include "PG/graphics/ViewHandle.h"
#include "PG/app/StyleSheet.h"

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
    SFMLViewHandle(sf::RenderWindow* view_, const StyleSheet& styleSheet_)
    : view(view_), currentScene(nullptr), styleSheet(styleSheet_)
    {}
    
    sf::RenderWindow*   view;
    SFMLScene*          currentScene;
	const StyleSheet	styleSheet;
};

}
}
