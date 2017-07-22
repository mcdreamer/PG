#include "PG/core/SizeUtils.h"

namespace PG {
namespace SizeUtils {

//--------------------------------------------------------
Size scaleSize(Size sz, float scale)
{
	return Size(sz.width * scale, sz.height * scale);
}

}
}
