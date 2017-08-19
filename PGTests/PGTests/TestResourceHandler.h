#pragma once

#include "PG/io/IResourceHandler.h"

//--------------------------------------------------------
class TestResourceHandler : public PG::IResourceHandler
{
public:
	//--------------------------------------------------------
	virtual std::string getResourcePath(const std::string& name, const std::string& type) override
	{
		return name + "." + type;
	}
};
