/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2023] Media Design School
File Name : CTorpedo.cpp
Description : Implementation for torpedo projectile weapon
Authors : Brittney, Glyn, Manu
**************************************************************************/

#include "CGameManager.h"
#include "CTorpedo.h"
#include "CPlayer.h"

/**************************************************************************
* CTorpedo: Constructor; set values
* @parameters: textureFilePath, startingPosition, direction to face, references to both players
* @return:
***************************************************************************/
CTorpedo::CTorpedo(CPlayer* _owningPlayer, std::shared_ptr<b2World> _box2DWorld, sf::Vector2f _startingPosition, int _direction)
{
	// Initialize values
	m_damage = 10;
	m_movementSpeed = 40.0f;
	m_filterGroup = _owningPlayer->m_filterGroup;
	m_angleOffset = DegreesToRadians(90);
	m_angle = _owningPlayer->GetBody()->GetAngle() - m_angleOffset * _direction;

	SetSize(sf::Vector2f(1.0f, 2.0f));
	// Sprite setting
	CreateSprite(CTextureManager::GetInstance()->GetTorpedoTexture());

	// Physics body
	SetBody(_box2DWorld, b2BodyType::b2_dynamicBody, b2Shape::Type::e_polygon, _startingPosition, 0.0f, m_filterGroup);
}

/**************************************************************************
* UpdateMovement: Projectile's movement behaviour when fired
* @parameters:
* @return:
***************************************************************************/
void CTorpedo::Update()
{
	CProjectileBase::Update();

	if (!m_moving)
	{
		m_moving = true;

		// Set angle of movement
		m_body->SetTransform(m_body->GetPosition(), m_angle);

		b2Vec2 velocity = { cos(m_angle + m_angleOffset), sin(m_angle + m_angleOffset) };
		velocity.Normalize();
		velocity *= m_movementSpeed;

		m_body->SetLinearVelocity(velocity);
	}
}
