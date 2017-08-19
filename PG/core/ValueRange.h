#pragma once

namespace PG {

//--------------------------------------------------------
template <typename T>
struct ValueRange
{
    ValueRange(const T start_, const T end_)
    : start(start_), end(end_)
    {}
	
    T start;
    T end;
	
	T size() const
	{
		return end - start;
	}
};

using IntRange = ValueRange<int>;

}
