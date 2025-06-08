/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2023] Media Design School
File Name : CHarpoon.cpp
Description : Implementation for harpoon projectile weapon
Authors : Brittney, Manu
**************************************************************************/

#include "CHarpoon.h"
#include "CGameManager.h"
#include "CPlayer.h"

/**************************************************************************
* CHarpoon: Constructor; set values
* @parameters: textureFilePath, designating where the texture .png is located, and startingPosition, identifying where the sprite should start
* @return:
***************************************************************************/
CHarpoon::CHarpoon(CPlayer* _owningPlayer, std::shared_ptr<b2World> _box2DWorld, sf::Vector2f _startingPosition, int _direction)
{
	// Initialize values
	m_damage = 20;
	m_movementSpeed = 25.0f;
	m_filterGroup = _owningPlayer->m_filterGroup;
	m_angleOffset = DegreesToRadians(90);
	m_directionMultiplier = _direction;
	m_angle = _owningPlayer->GetBody()->GetAngle() - m_angleOffset * m_directionMultiplier;

	m_downwardForce = b2Vec2(0.0f, 2.0f * g_moveScale);

	SetSize(sf::Vector2f(1.0f, 2.0f));
	// Sprite setting
	CreateSprite(CTextureManager::GetInstance()->GetHarpoonTexture());

	// Physics body
	SetBody(_box2DWorld, b2BodyType::b2_dynamicBody, b2Shape::Type::e_polygon, _startingPosition, 0.0f, m_filterGroup);
}

/**************************************************************************
* Update: Projectile's movement behaviour when fired
* @parameters:
* @return:
***************************************************************************/
void CHarpoon::Update()
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

	// Apply downward force to harpoon
	m_body->ApplyForceToCenter(m_downwardForce, true);

	// Change angle based on new velocity
	m_angle = atan2(m_body->GetLinearVelocity().y, m_body->GetLinearVelocity().x) - m_angleOffset * m_directionMultiplier;
	m_body->SetTransform(m_body->GetPosition(), m_angle);
}
