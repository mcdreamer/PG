#pragma once

#include "PG/app/IPlatformServices.h"

namespace PG {
namespace Internal {

//--------------------------------------------------------
class MacAppController : public IPlatformServices
{
public:
    virtual void exitApp() override;
};

}
}
