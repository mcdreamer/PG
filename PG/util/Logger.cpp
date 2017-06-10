#include "PG/util/Logger.h"

#include <iostream>

namespace PG {

//--------------------------------------------------------
void Logger::log(const std::string& msg)
{
    std::cerr << msg << std::endl;
}

}
