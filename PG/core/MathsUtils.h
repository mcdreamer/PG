#pragma once

namespace PG {
namespace MathsUtils {

//--------------------------------------------------------
template <typename T>
T clamp(T value, T min, T max)
{
    if (value > max)
    {
        value = max;
    }
    if (value < min)
    {
        value = min;
    }
    
    return value;
}

}
}
