#pragma once

#include <string>
#include <vector>

namespace PG {

class Attributes;

//--------------------------------------------------------
class EntityLoader
{
public:
    std::vector<Attributes> loadEntityFile(const std::string& filename) const;
};

}
