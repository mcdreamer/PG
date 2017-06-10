#include "PG/internal/graphics/SFMLScene.h"

namespace PG {

//--------------------------------------------------------
ScenePtr SceneCreator::createScene(int width, int height)
{
    return std::make_unique<Internal::SFMLScene>(width, height);
}

}
