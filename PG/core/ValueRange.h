#pragma once

namespace PG {

//--------------------------------------------------------
template <typename T>
struct ValueRange
{
    ValueRange(const T start_, const T end_)
    : start(start_), end(end_)
    {}
    
    const T start;
    const T end;
};

using IntRange = ValueRange<int>;

}
