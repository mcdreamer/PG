#pragma once

#include "PG/io/IResourceHandler.h"

//--------------------------------------------------------
class TestResourceHandler : public PG::IResourceHandler
{
public:
	//--------------------------------------------------------
	virtual PG::ResourceData getResourceData(const std::string& resourcePath) override
	{
		return PG::ResourceData();
	}
};
