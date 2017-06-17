#pragma once

#include "PG/app/IPlatformServices.h"

namespace PG {
namespace Internal {

//--------------------------------------------------------
class MacPlatformServices : public IPlatformServices
{
public:
    virtual void exitApp() override;
};

}
}
