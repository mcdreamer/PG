#pragma once

#include "PG/app/IPlatformServices.h"

namespace PG {
namespace Internal {

//--------------------------------------------------------
class WinPlatformServices : public IPlatformServices
{
public:
	virtual void exitApp() override;
};

}
}