#pragma once

#include <string>
#include <memory>

namespace PG {

class Rect;

//--------------------------------------------------------
class ITextureMeasurer
{
public:
    virtual ~ITextureMeasurer() {}

    virtual Rect getVisibleBoundsForTexture(const std::string& textureName)=0;
};

//--------------------------------------------------------
class TextureMeasurerCreator
{
public:
    static std::unique_ptr<ITextureMeasurer> createMeasurer();
};

//--------------------------------------------------------
namespace TextureMeasurementUtils {

Rect measureRGBABuffer(const unsigned char* data, int width, int height);

}

}
