#include "PG/internal/platform/LinuxResourceHandler.h"
#include "PG/internal/platform/ResourceHandler.h"

#include <unistd.h>
#include <string.h>

#include <iostream>

#include <boost/algorithm/string.hpp>

namespace PG {
namespace Internal {

//--------------------------------------------------------
std::string LinuxResourceHandler::getResourcePath(const std::string& name, const std::string& type)
{
  const int kBuffSize = 500;
  char wdBuf[kBuffSize];
  memset(wdBuf, 0, kBuffSize);
  getcwd(wdBuf, kBuffSize);

  std::string wd(wdBuf);

  ResourceHandler rh;
  return rh.getResourcePath(wd, name, type);
}

}
}
