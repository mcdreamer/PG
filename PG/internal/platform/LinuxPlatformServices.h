#pragma once

#include "PG/app/IPlatformServices.h"

namespace PG {
namespace Internal {

//--------------------------------------------------------
class LinuxPlatformServices : public IPlatformServices
{
public:
    virtual void exitApp() override;
};

}
}
