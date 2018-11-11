#include "PG/data/EntityLoader.h"
#include "PG/data/Attributes.h"
#include "PG/data/AttributeConstants.h"
#include "PG/util/JsonUtils.h"

#include <json/json.h>

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <algorithm>

namespace PG {

using ConstantsMap = std::map<std::string, std::string>;

namespace
{
    //--------------------------------------------------------
    ConstantsMap getConstants(const Json::Value& root)
    {
        ConstantsMap constantsMap;
        
        auto constantsRoot = root.get("constants", Json::Value());
        if (constantsRoot.type() == Json::objectValue)
        {
            auto constants = constantsRoot.getMemberNames();
            for (const auto& name : constants)
            {
                auto value = constantsRoot.get(name, Json::Value());
                
                constantsMap[name] = value.asString();
            }
        }
        
        return constantsMap;
    }

    //--------------------------------------------------------
    Attributes getEntity(const Json::Value& entity)
    {
        Attributes attributes;
        
        auto atts = entity.getMemberNames();
        for (const auto& att : atts)
        {
            auto value = entity.get(att, Json::Value());
            
            attributes.setAttributeString(att, value.asString());
        }
        
        return attributes;
    }
    
    //--------------------------------------------------------
    std::vector<Attributes> getEntities(const Json::Value& root)
    {
        std::vector<Attributes> attributes;
        
        auto entitiesRoot = root.get("entities", Json::Value());
        if (entitiesRoot.type() == Json::arrayValue)
        {
            for (const auto& entity : entitiesRoot)
            {
                attributes.push_back(getEntity(entity));
            }
        }
        
        return attributes;
    }
    
    //--------------------------------------------------------
    void substituteConstants(std::vector<Attributes>& entities, const ConstantsMap& constantsMap)
    {
        for (auto& entity : entities)
        {
            for (auto& value : entity)
            {
                auto constIt = constantsMap.find(value.second);
                if (constIt != constantsMap.end())
                {
                    value.second = constIt->second;
                }
            }
        }
    }

    //--------------------------------------------------------
    const Attributes* findParent(const std::string& name, const std::vector<Attributes>& entities)
    {
        auto it = std::find_if(entities.begin(), entities.end(), [&](const Attributes& entity) { return entity.getAttributeString(AttributeConstants::kName) == name; });
        return (it != entities.end() ? &(*it) : nullptr);
    }
    
    //--------------------------------------------------------
    void setParentEntities(std::vector<Attributes>& entities)
    {
        for (auto& entity : entities)
        {
            auto parentName = entity.getAttributeString("parent");
            if (parentName && !parentName->empty())
            {
                const auto* parent = findParent(*parentName, entities);
                if (parent)
                {
                    for (const auto& parentAtt : *parent)
                    {
                        if (parentAtt.first != AttributeConstants::kName && !entity.hasAttribute(parentAtt.first))
                        {
                            entity.setAttributeString(parentAtt.first, parentAtt.second);
                        }
                    }
                }
                
                entity.removeAttribute("parent");
            }
        }
    }
}

//--------------------------------------------------------
std::vector<Attributes> EntityLoader::loadEntityFile(const std::string& filename) const
{
    std::vector<Attributes> entities;

    std::fstream fs;
    fs.open(filename, std::fstream::in);
    
    Json::Value root;
    Json::Reader reader;
    if (reader.parse(fs, root))
    {
        auto constantsMap = getConstants(root);
        entities = getEntities(root);
        
        substituteConstants(entities, constantsMap);
        setParentEntities(entities);
    }
    
    fs.close();
    
    return entities;
}

}
