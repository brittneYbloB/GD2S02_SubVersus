/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2023] Media Design School
File Name : CTorpedo.h
Description : Header for torpedo projectile weapon
Authors : Brittney, Glyn, Manu
**************************************************************************/

#pragma once
#include "CProjectileBase.h"
#include "PhysicsLibrary.h"

class CTorpedo :
    public CProjectileBase
{
public:
    CTorpedo(
		class CPlayer* _owningPlayer, std::shared_ptr<b2World> _box2DWorld, sf::Vector2f _startingPosition, int _direction);
    ~CTorpedo() {};

    void Update() override;

};
