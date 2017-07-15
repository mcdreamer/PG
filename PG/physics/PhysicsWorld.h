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
    PhysicsWorld(const PhysicsWorldParams& params)
    : m_Params(params)
    {}
    
	const PhysicsWorldParams&   getParams() const { return m_Params; }
	void						applyPhysicsForBody(PhysicsBody& body, const DataGrid<bool>& levelGeometry, float dt) const;
	void						findCollisionsWithBody(const PhysicsBody& body, const std::vector<PhysicsBody>& bodiesToCheck, PhysicsWorldCallback& callback) const;
	
private:
    PhysicsWorldParams			m_Params;
};

}
