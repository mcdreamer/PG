#pragma once

#include <vector>

namespace PG {

//--------------------------------------------------------
template <typename T>
class DataGrid
{
public:
    DataGrid(int width, int height)
    : m_Width(width), m_Height(height)
    {
        m_Data.resize((size_t)(width * height));
    }
    
    //--------------------------------------------------------
    T at(int x, int y) const
    {
        auto i = getIndex(x, y);
        return m_Data[i];
    }
    
    //--------------------------------------------------------
    T at(int x, int y)
    {
        auto i = getIndex(x, y);
        return m_Data[i];
    }
    
    //--------------------------------------------------------
    void set(int x, int y, const T& v)
    {
        m_Data[getIndex(x, y)] = v;
    }

    const int       getWidth() const { return m_Width; }
    const int       getHeight() const { return m_Height; }

private:
    int				m_Width;
    int		       	m_Height;
    std::vector<T>  m_Data;
    
    //--------------------------------------------------------
    size_t getIndex(int x, int y) const
    {
        const auto i = static_cast<size_t>((y * m_Width) + x);
        return (i < m_Data.size() ? i : 0);
    }
};

}
