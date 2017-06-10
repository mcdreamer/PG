#pragma once

#include "PG/app/IAppController.h"

namespace PG {
namespace Internal {

//--------------------------------------------------------
class MacAppController : public IAppController
{
public:
    virtual void exitApp() override;
};

}
}
