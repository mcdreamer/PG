#include <string>

namespace PG {
namespace Internal {

//--------------------------------------------------------
class ResourceHandler
{
public:
  std::string getResourcePath(const std::string& exeDir,
                              const std::string& name,
                              const std::string& type);
};

}
}
