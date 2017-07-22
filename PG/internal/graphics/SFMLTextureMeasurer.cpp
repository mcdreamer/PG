#include "PG/internal/graphics/SFMLTextureMeasurer.h"
#include "PG/core/Rect.h"

//#import <Foundation/Foundation.h>
//#import <SpriteKit/SpriteKit.h>
//#import <CoreGraphics/CoreGraphics.h>
//#import <QuartzCore/QuartzCore.h>

#ifdef MAC
#define SKImage NSImage
#else
#define SKImage UIImage
#endif

namespace PG {
namespace Internal {

namespace
{
    ////--------------------------------------------------------
    //CGImageRef getImageRefForImage(SKImage* img)
    //{
    //#ifdef MAC
    //    return [img CGImageForProposedRect:nil context:nil hints:nil];
    //#else
    //    return img.CGImage;
    //#endif
    //}

    //--------------------------------------------------------
    class SFMLTextureMeasurer : public ITextureMeasurer
    {
    public:
        //--------------------------------------------------------
        virtual Rect getVisibleBoundsForTexture(const std::string& textureName) override
        {
            //NSString* nsTextureName = StringUtils::stdStringToNSString(textureName);
            //
            //SKImage* img = [SKImage imageNamed:nsTextureName];
            //
            //int width = [img size].width;
            //int height = [img size].height;
            //
            //CGColorSpaceRef colSpace = CGColorSpaceCreateDeviceRGB();
            //CGContextRef ctx = CGBitmapContextCreate(NULL, width, height, 8, width * 4, colSpace, (CGBitmapInfo)kCGImageAlphaPremultipliedLast);
            //CGColorSpaceRelease(colSpace);
            //
            //if (!ctx)
            //{
            //    NSLog(@"Attempt to get visible bounds for invalid texture %@", nsTextureName);
            //    return PGRect(PGPoint(0, 0), PGSize(width, height));
            //}
            //
            //CGContextSaveGState(ctx);
            //
            //CGImageRef cgImage = getImageRefForImage(img);
            //CGContextDrawImage(ctx, CGRectMake(0, 0, width, height), cgImage);
            //
            //CGContextFlush(ctx);
            //CGContextRestoreGState(ctx);
            //
            //return TextureMeasurementUtils::measureRGBABuffer((const unsigned char*)CGBitmapContextGetData(ctx), width, height);

			return Rect();
        }
    };
}

}

//--------------------------------------------------------
std::unique_ptr<ITextureMeasurer> TextureMeasurerCreator::createMeasurer()
{
    return std::unique_ptr<ITextureMeasurer>(new Internal::SFMLTextureMeasurer);
}

}
