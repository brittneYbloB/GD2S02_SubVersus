/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2023] Media Design School
File Name : CHealthResource.cpp
Description : Implementation for health collectible resource
Authors : Brittney Smith
**************************************************************************/

#include "CHealthResource.h"
#include "CPlayer.h"
#include "CAudioManager.h"

#define MAX_HEALTH 100
#define MAX_LIVES 3

/**************************************************************************
* CHealthResource: Constructor; set-up health additive value
* @parameters: world, starting position
* @return:
***************************************************************************/
CHealthResource::CHealthResource(std::shared_ptr<b2World> _box2DWorld, sf::Vector2f _startingPosition)
{
	// Health value
	m_resourceValue = 15;

	// Size
	SetSize(sf::Vector2f(4.0f, 4.0f));

	// Load texture from image file
	CreateSprite(CTextureManager::GetInstance()->GetHealthResTexture());

	// Set Box2D body
	SetBody(_box2DWorld, b2BodyType::b2_kinematicBody, b2Shape::Type::e_polygon, _startingPosition, 0.0f);

	// Spawn falling
	m_body->SetLinearVelocity(b2Vec2(0.0f, 5.0f));

	// Set position reference (for position spawning validation checks)
	m_spawnPosition = _startingPosition;
}

/**************************************************************************
* ResourceCollected: Adjust the colliding-player's health (add)
* @parameters: Player reference
* @return:
***************************************************************************/
void CHealthResource::ResourceCollected(CDrawableObject* _playerRef)
{
	m_collidedPlayerReference = dynamic_cast<CPlayer*>(_playerRef);

	// Check if player ref is valid
	if (m_collidedPlayerReference != nullptr)
	{
		CAudioManager::GetInstance()->PlaySound("Pickup");

		// Check if player's health isn't already full (cap it to max)
		if (m_collidedPlayerReference->m_health < MAX_HEALTH)
		{
			m_collidedPlayerReference->m_health += m_resourceValue;
		}
	}
}
