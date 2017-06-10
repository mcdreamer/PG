#pragma once

#include <string>
#include <memory>

namespace PG {

class PGRect;

//--------------------------------------------------------
class ITextureMeasurer
{
public:
    virtual ~ITextureMeasurer() {}

    virtual PGRect getVisibleBoundsForTexture(const std::string& textureName)=0;
};

//--------------------------------------------------------
class TextureMeasurerCreator
{
public:
    static std::unique_ptr<ITextureMeasurer> createMeasurer();
};

//--------------------------------------------------------
namespace TextureMeasurementUtils {

PGRect measureRGBABuffer(const unsigned char* data, int width, int height);

}

}
