/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2023] Media Design School
File Name : CMissile.h
Description : Header for missile projectile weapon
Authors : Brittney, Manu
**************************************************************************/

#pragma once
#include "CProjectileBase.h"

class CMissile :
    public CProjectileBase
{
public:
    CMissile(class CPlayer* _owningPlayer, CPlayer* _targetPlayer, std::shared_ptr<b2World> _box2DWorld, sf::Vector2f _startingPosition, int _direction);

    void Update() override;

protected:
    CPlayer* m_targetPlayer;
    int m_direction;
    float m_lockDirectionTime;
    float m_elapsedTime;
};

