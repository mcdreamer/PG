#pragma once

#include "PG/thirdparty/jsoncpp/include/json/json.h"

#include <string>

namespace PG {

class Point;

namespace JsonUtils
{
    std::string         getChildStringWithKey(const Json::Value& val, const std::string& key);
    double              getChildDoubleWithKey(const Json::Value& val, const std::string& key);
    int                 getChildIntWithKey(const Json::Value& val, const std::string& key);
    bool                getChildBoolWithKey(const Json::Value& val, const std::string& key);
    Point             getChildPointWithKey(const Json::Value& val, const std::string& key);
    
    Json::Value         valueWithPoint(const Point& pt);
    
    bool                hasChildWithKey(const Json::Value& val, const std::string& key);
}
}
