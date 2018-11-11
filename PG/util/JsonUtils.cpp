#include "PG/util/JsonUtils.h"
#include "PG/core/Point.h"

#include <json/json.h>

namespace PG {
namespace JsonUtils
{
    //--------------------------------------------------------
    std::string getChildStringWithKey(const Json::Value& val, const std::string& key)
    {
        auto strVal = val.get(key, Json::Value());
    
        return (strVal.isString() ? strVal.asString() : "");
    }
    
    //--------------------------------------------------------
    double getChildDoubleWithKey(const Json::Value& val, const std::string& key)
    {
        auto doubleVal = val.get(key, Json::Value());
        
        return (doubleVal.isDouble() ? doubleVal.asDouble() : 0);
    }
    
    //--------------------------------------------------------
    int getChildIntWithKey(const Json::Value& val, const std::string& key)
    {
        auto intValue = val.get(key, Json::Value());
        
        return (intValue.isIntegral() ? intValue.asInt() : 0);
    }
    
    //--------------------------------------------------------
    bool getChildBoolWithKey(const Json::Value& val, const std::string& key)
    {
        auto boolValue = val.get(key, Json::Value());
        
        return (boolValue.isBool() ? boolValue.asBool() : false);
    }
    
    //--------------------------------------------------------
    Point getChildPointWithKey(const Json::Value& val, const std::string& key)
    {
        auto pt = val.get(key, Json::Value());
    
        double x = getChildDoubleWithKey(pt, "x");
        double y = getChildDoubleWithKey(pt, "y");
        
        return Point(x, y);
    }
    
    //--------------------------------------------------------
    Json::Value valueWithPoint(const Point& pt)
    {
        Json::Value jsonPt;
        jsonPt["x"] = pt.x;
        jsonPt["y"] = pt.y;
        
        return jsonPt;
    }
        
    //--------------------------------------------------------
    bool hasChildWithKey(const Json::Value& val, const std::string& key)
    {
        auto child = val.get(key, Json::Value(Json::nullValue));
        return !child.isNull();
    }
}

}
