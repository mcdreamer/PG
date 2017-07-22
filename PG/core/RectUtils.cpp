#include "PG/core/RectUtils.h"

#include <cmath>

#ifdef __APPLE__

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wsign-conversion"
#pragma clang diagnostic ignored "-Wconversion"
#pragma clang diagnostic ignored "-Wshadow"

#endif

#include <boost/geometry.hpp>

#ifdef __APPLE__

#pragma clang diagnostic pop

#endif

namespace PG {

namespace
{
    using bPoint = boost::geometry::model::point<double, 2, boost::geometry::cs::cartesian>;
    using bRect = boost::geometry::model::box<bPoint>;

    //--------------------------------------------------------
    bPoint toBPoint(const Point& pt)
    {
        return bPoint(pt.x, pt.y);
    }

    //--------------------------------------------------------
    bRect toBRect(const Rect& r)
    {
        return bRect(bPoint(r.origin.x - (r.size.width / 2.0), r.origin.y - (r.size.height / 2.0)),
                     bPoint(r.origin.x + (r.size.width / 2.0), r.origin.y + r.size.height / 2.0));
    }
    
    //--------------------------------------------------------
    Rect toPGRect(const bRect& r)
    {
        auto ox = r.min_corner().get<0>();
        auto oy = r.min_corner().get<1>();
        
        auto w = r.max_corner().get<0>() - ox;
        auto h = r.max_corner().get<1>() - oy;
        
        return Rect(Point(ox, oy), Size(w, h));
    }
}

//--------------------------------------------------------
namespace RectUtils
{
    //--------------------------------------------------------
    Rect getIntersection(const Rect& rectOne, const Rect& rectTwo)
    {
        auto bRectOne = toBRect(rectOne);
        auto bRectTwo = toBRect(rectTwo);
    
        if (!boost::geometry::intersects(bRectOne, bRectTwo))
        {
            return Rect();
        }
    
        bRect intersection;
        boost::geometry::intersection(bRectOne, bRectTwo, intersection);
        
        return toPGRect(intersection);
   }
	
   //--------------------------------------------------------
   bool isEmpty(const Rect& r)
   {
       return isEmpty(r.size);
   }
   
   //--------------------------------------------------------
   bool isEmpty(const Size& s)
   {
       return s.width == 0 || s.height == 0;
   }
   
   //--------------------------------------------------------
   bool containsPoint(const Rect& r, const Point& pt)
   {
        return boost::geometry::covered_by(toBPoint(pt), toBRect(r));
   }
   
   //--------------------------------------------------------
   Rect combineRects(const Rect& r1, const Rect& r2)
   {
       if (isEmpty(r1))
       {
           return r2;
       }
       
       if (isEmpty(r2))
       {
           return r1;
       }
   
       auto minLeft = std::min(r1.left(), r2.left());
       auto maxRight = std::max(r1.right(), r2.right());
       auto minTop = std::min(r1.top(), r2.top());
       auto maxBottom = std::max(r1.bottom(), r2.bottom());
       
       Size combinedSize(maxRight - minLeft, maxBottom - minTop);
       Point newOrigin(minLeft + (combinedSize.width / 2.0), maxBottom - (combinedSize.height / 2.0));
    
       return Rect(newOrigin, combinedSize);
   }
}

}
