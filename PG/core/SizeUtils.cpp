#include "PG/core/SizeUtils.h"

namespace PG {
namespace SizeUtils {

//--------------------------------------------------------
PGSize scaleSize(PGSize sz, float scale)
{
	return PGSize(sz.width * scale, sz.height * scale);
}

}
}
