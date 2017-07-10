#pragma once

#include "PG/core/Size.h"
#include "PG/data/DataGrid.h"
#include "PG/physics/PhysicsWorldParams.h"

namespace PG {

struct PhysicsBody;
class INode;
class TileCoord;

//--------------------------------------------------------
class PhysicsWorldCallback
{
public:
    virtual ~PhysicsWorldCallback () {}
    
    virtual void bodiesDidCollide(const PhysicsBody& body,
								  const PhysicsBody& collidedWithBody,
								  const size_t nthBody)=0;
};

//--------------------------------------------------------
class PhysicsWorld
{
public:
    PhysicsWorld(const PhysicsWorldParams& params, PhysicsWorldCallback& callback)
    : m_Params(params), m_Callback(callback)
    {}
    
	const PhysicsWorldParams&   getParams() const { return m_Params; }
	void						applyPhysicsForBody(PhysicsBody& body, const DataGrid<bool>& levelGeometry, float dt) const;
	void						findCollisionsWithItems(const PhysicsBody& body, const std::vector<PhysicsBody>& bodiesToCheck) const;
	
private:
    PhysicsWorldParams			m_Params;
    PhysicsWorldCallback&		m_Callback;
};

}
