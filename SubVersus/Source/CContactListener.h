/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2023] Media Design School
File Name : CContactListener.h
Description : Header file for contact listener class, used by the box2d world to resolve collisions
Authors : Manu Easton
**************************************************************************/

#pragma once

#include "box2d/b2_world_callbacks.h"

class CContactListener : public b2ContactListener
{
public:

	CContactListener(class b2World* _world, class CGameManager* _gameManager);

	void PreSolve(class b2Contact* _contact, const struct b2Manifold* _oldManifold);

private:

	b2World* m_box2DWorld = nullptr;
	CGameManager* m_gameManager = nullptr;
};

