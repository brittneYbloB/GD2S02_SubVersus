/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2023] Media Design School
File Name : CMissile.h
Description : Implementation for missile projectile weapon
Authors : Brittney, Manu
**************************************************************************/

#include "CMissile.h"
#include "CGameManager.h"
#include "CPlayer.h"

/**************************************************************************
* CMissile: Constructor; set values
* @parameters: textureFilePath, designating where the texture .png is located, and startingPosition, identifying where the sprite should start
* @return:
***************************************************************************/
CMissile::CMissile(CPlayer* _owningPlayer, CPlayer* _targetPlayer, std::shared_ptr<b2World> _box2DWorld, sf::Vector2f _startingPosition, int _direction)
{
	// Initialize values
	m_damage = 30;
	m_movementSpeed = 20.0f;
	m_filterGroup = _owningPlayer->m_filterGroup;
	m_angleOffset = DegreesToRadians(90);
	m_angle = _owningPlayer->GetBody()->GetAngle() - m_angleOffset * _direction;
	m_direction = _direction;

	m_targetPlayer = _targetPlayer;
	m_elapsedTime = 0.0f;
	m_lockDirectionTime = 2.0f;

	SetSize(sf::Vector2f(1.0f, 2.0f));
	// Sprite setting
	CreateSprite(CTextureManager::GetInstance()->GetMissileTexture());

	// Physics body
	SetBody(_box2DWorld, b2BodyType::b2_dynamicBody, b2Shape::Type::e_polygon, _startingPosition, 0.0f, m_filterGroup);
	m_body->SetFixedRotation(false);
}

/**************************************************************************
* Update: Projectile's movement behaviour when fired
* @parameters:
* @return:
***************************************************************************/
void CMissile::Update()
{
	CProjectileBase::Update();

	m_elapsedTime += 1.0f / g_frameRate;

	if (m_elapsedTime < m_lockDirectionTime) // Stops updating velocity after time has passed;
	{
		// Move to player
		b2Vec2 velocity = m_targetPlayer->GetBody()->GetPosition() - m_body->GetPosition();
		velocity.Normalize();
		velocity *= m_movementSpeed;
		float desiredAngle = atan(velocity.y / velocity.x);
		desiredAngle += m_angleOffset;

		if (velocity.x < 0)
		{
			desiredAngle += DegreesToRadians(180);
		}

		m_body->SetTransform(m_body->GetPosition(), desiredAngle);
		m_body->SetLinearVelocity(velocity);
	}
}
