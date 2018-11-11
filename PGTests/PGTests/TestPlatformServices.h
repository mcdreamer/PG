#pragma once

#include "PG/app/IPlatformServices.h"

//--------------------------------------------------------
class TestPlatformServices : public PG::IPlatformServices
{
public:
	virtual void exitApp() override {}
	virtual float getDisplayScale() override { return 1.0; }
	virtual std::string	getResourcesFilePath() override { return ""; }
};
