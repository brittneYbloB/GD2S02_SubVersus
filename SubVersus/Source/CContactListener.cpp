/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2023] Media Design School
File Name : CContactListener.h
Description : Implementation file for contact listener class
Authors : Manu Easton, Brittney Smith
**************************************************************************/

#include "CContactListener.h"
#include "box2d/box2d.h"
#include "CGameManager.h"
// Classes for casting
#include "CHealthResource.h"
#include "CAmmoResource.h"

/**************************************************************************
* CContactListener: Constructor for CContactListener class
* @parameters: pointers to box2D world and game manager
* @return:
***************************************************************************/
CContactListener::CContactListener(b2World* _world, CGameManager* _gameManager)
{
	m_box2DWorld = _world;
	m_gameManager = _gameManager;
}

/**************************************************************************
* PreSolve: Constructor for CContactListener class
* @parameters: pointers to box2d contact and old world manifold
* @return:
***************************************************************************/
void CContactListener::PreSolve(b2Contact* _contact, const b2Manifold* _oldManifold)
{
    b2WorldManifold worldManifold;
    _contact->GetWorldManifold(&worldManifold);

    b2PointState state1[2], state2[2];
    b2GetPointStates(state1, state2, _oldManifold, _contact->GetManifold());

    if (state2[0] == b2_addState)
    {
        const b2Body* bodyA = _contact->GetFixtureA()->GetBody();
        const b2Body* bodyB = _contact->GetFixtureB()->GetBody();
        //b2Vec2 point = worldManifold.points[0];
        //b2Vec2 vA = bodyA->GetLinearVelocityFromWorldPoint(point);
        //b2Vec2 vB = bodyB->GetLinearVelocityFromWorldPoint(point);

        //float approachSpeed = b2Dot(vB - vA, -worldManifold.normal);

        CDrawableObject* objectA = nullptr;
        CDrawableObject* objectB = nullptr;

        for (auto iter : m_gameManager->GetGameObjects())
        {
            if (iter->GetBody() == bodyA)
            {
                objectA = iter;
            }
            if (iter->GetBody() == bodyB)
            {
                objectB = iter;
            }
        }

        if (objectA != nullptr && objectB != nullptr)
        {
            bool playerHasCollidedWithNonPlayerA = false;    // boolean for determining if resource-allocation functionalities should be performed
            bool playerHasCollidedWithNonPlayerB = false;    // boolean for determining if resource-allocation functionalities should be performed

            // Determine which object body is a player/s
            CPlayer* player1 = dynamic_cast<CPlayer*>(objectA); 
            CPlayer* player2 = dynamic_cast<CPlayer*>(objectA); 
            if (player1 == nullptr)     // player is not object A
            {
                player1 = dynamic_cast<CPlayer*>(objectB);  // try cast object B as player
                if (player1 != nullptr)  // object B is a player
                { 
                    if (player2 == nullptr) // check object A isn't a player too (that would mean PvP collision)
                    {
                        playerHasCollidedWithNonPlayerA = true;
                    }
                }
            } 
            else  // object A is a player, so is object B also a player?
            {
                // check object B isn't a player too (that would mean PvP collision)
                player2 = dynamic_cast<CPlayer*>(objectB);
                if (player2 == nullptr)
                {
                    playerHasCollidedWithNonPlayerB = true;
                }
            }

            // Apply damage to objects
            objectA->RecieveImpact(objectB->GetDamage());
            objectB->RecieveImpact(objectA->GetDamage());
            
            // Perform resource allocation functionalities
            if (playerHasCollidedWithNonPlayerA)    // object B is a player, object A is not
            {
                CHealthResource* healthRes = dynamic_cast<CHealthResource*>(objectA);
                CAmmoResource* ammoRes = dynamic_cast<CAmmoResource*>(objectA);
                if (healthRes != nullptr)
                {
                    healthRes->ResourceCollected(objectB);
                }
                else if(ammoRes != nullptr)
                {
                    ammoRes->ResourceCollected(objectB);
                }
            }
            if (playerHasCollidedWithNonPlayerB)    // object A is a player, object B is not
            {
                CHealthResource* healthRes = dynamic_cast<CHealthResource*>(objectB);
                CAmmoResource* ammoRes = dynamic_cast<CAmmoResource*>(objectB);
                if (healthRes != nullptr)
                {
                    healthRes->ResourceCollected(objectA);
                }
                else if (ammoRes != nullptr)
                {
                    ammoRes->ResourceCollected(objectA);
                }
            }
        }
    }
}
