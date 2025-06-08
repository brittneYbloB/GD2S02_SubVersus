/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2023] Media Design School
File Name : CEnvironmentHazard.h
Description : Header for environmental hazard base class
Authors : Brittney Smith, Manu Easton
**************************************************************************/

#pragma once
#include "CDrawableObject.h"

class CEnvironmentHazard : public CDrawableObject
{
public:
	CEnvironmentHazard(std::shared_ptr<b2World> _box2DWorld, sf::Vector2f _startingPosition);

protected:
	CEnvironmentHazard() {};

	// Functions which behave the same for all hazards
	void Update() override;

	// Functions which differ based on type of hazard
	virtual void RecieveImpact(float _damage) override;				// when hit by a projectile

	// Variables
	bool m_falling = false;
	b2Vec2 m_fallingVelocity = { 0.0f, 20.0f };
};
