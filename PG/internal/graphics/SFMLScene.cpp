#include "PG/internal/graphics/SFMLScene.h"

namespace PG {

//--------------------------------------------------------
ScenePtr SceneCreator::createScene()
{
    return std::make_unique<Internal::SFMLScene>();
}

}
