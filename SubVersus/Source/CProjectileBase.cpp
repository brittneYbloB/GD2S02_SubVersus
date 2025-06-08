/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2023] Media Design School
File Name : CProjectileBase.cpp
Description : Implementation for base projectile class
Authors : Brittney
**************************************************************************/

#include "CProjectileBase.h"
#include "CAudioManager.h"

/**************************************************************************
* CProjectileBase: Base class constructor
* @parameters:
* @return:
***************************************************************************/
CProjectileBase::CProjectileBase()
{
	// Initialize values
	m_angle = 0.0f;
	m_angleOffset = 0.0f;
	m_damage = 0;
	m_moving = false;
}

void CProjectileBase::RecieveImpact(float _damage)
{
	CAudioManager::GetInstance()->PlaySound("ProjectileHit");
	m_markedForDestroy = true;
}
