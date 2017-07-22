#include "PG/graphics/TextureMeasurer.h"
#include "PG/core/Rect.h"

namespace PG {
namespace TextureMeasurementUtils {

//--------------------------------------------------------
Rect measureRGBABuffer(const unsigned char* data, int width, int height)
{
	int xMin = -1;
	int xMax = -1;

	int yMin = -1;
	int yMax = -1;

	struct Pixel { uint8_t r, g, b, a; };
	struct Pixel* pixels = (struct Pixel*)data;

	for (int y = 0; y < height; y++)
	{
		bool foundOpaquePixel = false;

		for (int x = 0; x < width; x++)
		{
			int index = x + y * width;
			foundOpaquePixel |= pixels[index].a != 0;

			if (pixels[index].a != 0 && (x < xMin || xMin == -1))
			{
				xMin = x;
			}
			if (pixels[index].a != 0 && (x >= xMax || xMax == -1))
			{
				xMax = x + 1;
			}
		}

		if (foundOpaquePixel && yMin == -1)
		{
			yMin = y;
		}
		if (foundOpaquePixel && (y >= yMax || yMax == -1))
		{
			yMax = y + 1;
		}
	}

	return Rect(Point(xMin, height - yMax), Size(xMax - xMin, yMax - yMin));
}
	
}
}
