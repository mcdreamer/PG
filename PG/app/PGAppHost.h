#pragma once

#include <string>

namespace PG {

class IGameController;

//--------------------------------------------------------
class PGAppHost
{
public:
    void runApp(IGameController& gameController);
};

}
