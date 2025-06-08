/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2023] Media Design School
File Name : CAmmoResource.h
Description : Implementation for ammo collectible item
Authors : Brittney Smith
**************************************************************************/

#include "CAmmoResource.h"
#include "CPlayer.h"
#include "CAudioManager.h"

/**************************************************************************
* CAmmoResource: Constructor; set ammo type at random
* @parameters: world, starting position
* @return:
***************************************************************************/
CAmmoResource::CAmmoResource(std::shared_ptr<b2World> _box2DWorld, sf::Vector2f _startingPosition)
{
	// Value of ammo
	m_ammoValue = 10;

	// Size
	SetSize(sf::Vector2f(4.0f, 4.0f));

	// Sprite setting
	CreateSprite(CTextureManager::GetInstance()->GetAmmoResTexture());

	// Physics body
	SetBody(_box2DWorld, b2BodyType::b2_kinematicBody, b2Shape::Type::e_polygon, _startingPosition, 0.0f);

	// Spawn falling
	m_body->SetLinearVelocity(b2Vec2(0.0f, 5.0f));

	// Set position reference (for position spawning validation checks)
	m_spawnPosition = _startingPosition;
}

/**************************************************************************
* ResourceCollected: Adjust the colliding-player's ammo (add)
* @parameters: Player reference
* @return:
***************************************************************************/
void CAmmoResource::ResourceCollected(CDrawableObject* _playerRef)
{
	// Cast collided object as player
	m_collidedPlayerReference = dynamic_cast<CPlayer*>(_playerRef);

	// Check if player reference is valid
	if (m_collidedPlayerReference)
	{
		CAudioManager::GetInstance()->PlaySound("Pickup");

		// Increase player's ammo by a set amount
		m_collidedPlayerReference->m_universalAmmo += m_ammoValue;
	}
}