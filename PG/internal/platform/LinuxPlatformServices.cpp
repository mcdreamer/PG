#include "PG/internal/platform/LinuxPlatformServices.h"

#include <stdlib.h> 

namespace PG {
namespace Internal {

//--------------------------------------------------------
void LinuxPlatformServices::exitApp()
{
  exit(0);
}

}
}
