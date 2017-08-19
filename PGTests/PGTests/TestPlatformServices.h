#pragma once

#include "PG/app/IPlatformServices.h"

//--------------------------------------------------------
class TestPlatformServices : public PG::IPlatformServices
{
public:
	virtual void exitApp() override {}
};
