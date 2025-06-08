/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2023] Media Design School
File Name : CNavalMineHazard.h
Description : Header file for naval mine environmental hazard
Authors : Brittney Smith
**************************************************************************/

#pragma once
#include "CEnvironmentHazard.h"

class CNavalMineHazard : public CEnvironmentHazard
{
public:
	// using CEnvironmentHazard::CEnvironmentHazard;
	CNavalMineHazard(class CGameManager* _game, std::shared_ptr<b2World> _box2DWorld, sf::Vector2f _startingPosition);
protected:
	CGameManager* game;

	virtual void RecieveImpact(float _damage) override;
	void Update() override;

	float m_depth = 55.0f;
};