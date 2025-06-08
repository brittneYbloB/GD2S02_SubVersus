/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2023] Media Design School
File Name : CProjectileBase.h
Description : Header for base projectile class
Authors : Brittney, Manu
**************************************************************************/

#pragma once
#include "CDrawableObject.h"
#include <iostream>

class CProjectileBase : public CDrawableObject
{
public:
    CProjectileBase();

    void RecieveImpact(float _damage) override;

protected:
    float m_angle;
    float m_angleOffset;
    bool m_moving;
};

