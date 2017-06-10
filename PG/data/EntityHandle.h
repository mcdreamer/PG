#pragma once

#include <boost/optional.hpp>

namespace PG {

template <typename T>
class EntityHandle
{
public:
    EntityHandle()
    {}
    
    EntityHandle(const T& entity)
    : m_Entity(entity)
    {}

    const T*            getEntity() const { return m_Entity ? &(*m_Entity) : nullptr; }
    T*                  getEntity() { return m_Entity ? &(*m_Entity) : nullptr; }

    void                setEntity(const T& entity) { m_Entity = entity; }
    void                clearEntity() { m_Entity.reset(); }

    //--------------------------------------------------------
    void swap(EntityHandle& other)
    {
        auto otherEntity = other.m_Entity;
        other.m_Entity = m_Entity;
        m_Entity = otherEntity;
    }

private:
    boost::optional<T>  m_Entity;
};

}
