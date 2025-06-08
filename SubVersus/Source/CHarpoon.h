/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2023] Media Design School
File Name : CHarpoon.h
Description : Header for harpoon projectile weapon
Authors : Brittney, Manu
**************************************************************************/

#pragma once
#include "CProjectileBase.h"

class CHarpoon :
    public CProjectileBase
{
public:
    CHarpoon(class CPlayer* _owningPlayer, std::shared_ptr<b2World> _box2DWorld, sf::Vector2f _startingPosition, int _direction);

    void Update() override;
    
private:
    b2Vec2 m_downwardForce;
    int m_directionMultiplier;
};

