/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2023] Media Design School
File Name : CEnvironmentHazard.cpp
Description : Implementation for environmental hazard base class
Authors : Brittney Smith, Manu Easton
**************************************************************************/

#include "CEnvironmentHazard.h"
#include "CAudioManager.h"

/**************************************************************************
* CEnvironmentHazard: Base class constructor
* @parameters: box2DWorld, startingPosition, texture
* @return:
***************************************************************************/
CEnvironmentHazard::CEnvironmentHazard(std::shared_ptr<b2World> _box2DWorld, sf::Vector2f _startingPosition)
{
	SetSize(sf::Vector2f(3.0f, 6.0f));

	// Sprite setting
	CreateSprite(CTextureManager::GetInstance()->GetStalactiteTexture());

	// Set Box2D body
	SetBody(_box2DWorld, b2BodyType::b2_kinematicBody, b2Shape::Type::e_polygon, _startingPosition, 0.0f);

	// Set position reference (for position spawning validation checks)
	m_spawnPosition = _startingPosition;

	m_damage = 20.0f;
}

/**************************************************************************
* Update: Check for collision & such
* @parameters:
* @return:
***************************************************************************/
void CEnvironmentHazard::Update()
{
	
}

/**************************************************************************
* RecieveImpact: Sets hazard to fall on impact with other object
* @parameters: damage caused by other object
* @return:
***************************************************************************/
void CEnvironmentHazard::RecieveImpact(float _damage)
{
	CAudioManager::GetInstance()->PlaySound("StalactiteHit");

	if (!m_falling)
	{
		m_body->SetLinearVelocity(m_fallingVelocity);

		m_falling = true;
	}

	if (_damage < 0)	// Colliding with player
	{
		m_markedForDestroy = true;
	}
}