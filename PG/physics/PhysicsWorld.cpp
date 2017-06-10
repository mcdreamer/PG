#include "PG/physics/PhysicsWorld.h"
#include "PG/physics/PhysicsBody.h"

//#include <iostream>

namespace PG {

namespace
{
//    //--------------------------------------------------------
//    void getCollisionTestPoints(PGPoint* ptsToTest, PGPoint levPt)
//    {
//        for (int i = 0; i < 9; ++i)
//        {
//            ptsToTest[i] = levPt;
//        }
//        
//        // Aligned points
//        ++ptsToTest;
//        ptsToTest->y -= 1;
//        
//        ++ptsToTest;
//        ptsToTest->y += 1;
//        
//        ++ptsToTest;
//        ptsToTest->x -= 1;
//        
//        ++ptsToTest;
//        ptsToTest->x += 1;
//        
//        // Diagonal points
//        ++ptsToTest;
//        ptsToTest->x -= 1;
//        ptsToTest->y += 1;
//        
//        ++ptsToTest;
//        ptsToTest->x += 1;
//        ptsToTest->y += 1;
//        
//        ++ptsToTest;
//        ptsToTest->x -= 1;
//        ptsToTest->y -= 1;
//        
//        ++ptsToTest;
//        ptsToTest->x += 1;
//        ptsToTest->y -= 1;
//    }
//    
//    //--------------------------------------------------------
//    bool findIntersectionAndResolveForBody(PhysicsBody* body, INode* bodyNode, const PGRect& nodeRect)
//    {
//        auto charRect = getRectFromBounds(body->bounds, body->desiredPosition);
//        
//        auto intersection = PGRectUtils::getIntersection(charRect, nodeRect);
//        if (!PGRectUtils::isEmpty(intersection))
//        {
//            PGPoint removeIntersectionPt;
//            PGPoint adjustedVelocity;
//            
//            if (intersection.size.height < intersection.size.width)
//            {
//                bool collisionBelow = (nodeRect.origin.y < charRect.origin.y);
//                if (collisionBelow)
//                {
//                    body->hasHitGround(true);
//                }
//                
//                int dir = collisionBelow ? 1 : -1;
//                removeIntersectionPt = PGPoint(0, dir * intersection.size.height);
//                adjustedVelocity = PGPoint(body->velocity.x, collisionBelow ? 0 : -100); // enough force not to stick when hitting top
//            }
//            else
//            {
//                int dir = (nodeRect.origin.x < charRect.origin.x) ? 1 : -1;
//                removeIntersectionPt = PGPoint(dir * intersection.size.width, 0);
//                adjustedVelocity = PGPoint(0, body->velocity.y);
//            }
//            
//            body->velocity = adjustedVelocity;
//            body->desiredPosition = PGPointAdd(body->desiredPosition, removeIntersectionPt);
//            
//            return true;
//        }
//        
//        return false;
//    }
//    
//    //--------------------------------------------------------
//    void resolveCollisionAtPoint(const PGPoint& levPtToTest, PhysicsBody* body, INode* bodyNode,
//                                 EntityState* state, INode& parent, double levelWidth, PhysicsWorldDelegate* delegate)
//    {
//        for (auto* node : nodes)
//        {
//            if (node == bodyNode)
//            {
//                continue;
//            }
//            
//            LevelBlock* blk = node ? LevelBlockUtils::getBlockForNode(*node) : nullptr;
//            if (node && blk && blk->getTexture()->getBlocksPlayer())
//            {
//                auto containerFrameOrigin = container->getFrameOrigin();
//                auto nodeFrameOrigin = node->getFrameOrigin();
//                
//                auto pt = PGPoint(containerFrameOrigin.x + nodeFrameOrigin.x, containerFrameOrigin.y + nodeFrameOrigin.y);
//                auto nodeRect = getRectFromBounds(blk->getTexture()->getBounds(), pt);
//                
//                bool wasOnGround = body->onGround;
//                if (findIntersectionAndResolveForBody(body, bodyNode, nodeRect))
//                {
//                    return;
//                }
//            }
//        }
//    }
}

//--------------------------------------------------------
void PhysicsWorld::applyPhysicsForBody(PhysicsBody* body, INode* node, INode& parent) const
{
//    auto levPt = LevelUtils::levelPointFromPoint(body->desiredPosition);
//    
//    auto halfTileSize = LevelUtils::tileSize() / 2.0;
//    
//    // Collision detection
//    PGPoint ptsToTest[9];
//    getCollisionTestPoints(ptsToTest, levPt);
//    for (int i = 0; i < 9; ++i)
//    {
//        resolveCollisionAtPoint(ptsToTest[i], body, node, state, parent, levelWidth, m_Delegate);
//    }
//    
//    // Apply updated desired position
//    body->desiredPosition = PGPoint(body->desiredPosition.x + halfTileSize, body->desiredPosition.y + halfTileSize);
//    node->setPosition(body->desiredPosition.x, body->desiredPosition.y);
}

}
