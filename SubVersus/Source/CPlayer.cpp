/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2023] Media Design School
File Name : CPlayer.cpp
Description : Implementation for player class
Authors : Brittney Smith, Manu Easton, Glyn
**************************************************************************/

#include "CPlayer.h"
#include "CGameManager.h"
#include "CAudioManager.h"

/************************************************************************** 
* CPlayer: Base constructor for the player class
* @parameters: textureFilePath, designating where the texture .png is located, and startingPosition, identifying where the sprite should start
* @return: 
***************************************************************************/
CPlayer::CPlayer(CGameManager* _gameManager, std::shared_ptr<b2World> _box2DWorld, sf::Vector2f _startingPosition, int _playerNum)
{
	m_gameManager = _gameManager;
	m_respawnPosition = _startingPosition;

	SetSize(sf::Vector2f(10.0f, 4.0f));
	m_universalAmmo = 5; // starting ammo count

	m_damage = -1.0f; // Negative value to indicate to other objects that they are colliding with a player

	// Load texture from image file
	if (_playerNum == 1)
	{
		CreateSprite(CTextureManager::GetInstance()->GetPlayerOneTexture());
	}
	else
	{
		CreateSprite(CTextureManager::GetInstance()->GetPlayerTwoTexture());
	}
	m_filterGroup = -_playerNum;

	m_weaponEquipped = WEAPON_EQUIPPED::e_Torpedo;
	m_playerNum = _playerNum;

	SetBody(_box2DWorld, b2BodyType::b2_dynamicBody, b2Shape::Type::e_polygon, _startingPosition, 0.0f, m_filterGroup);
	// Set sprite to body
	m_sprite.setScale(m_spriteScale);
	m_sprite.setOrigin(float(m_sprite.getTexture()->getSize().x / 2), float(m_sprite.getTexture()->getSize().y / 2));
	m_sprite.setPosition(m_body->GetPosition().x * g_moveScale, m_body->GetPosition().y * g_moveScale);
	m_sprite.setPosition(m_body->GetPosition().x * g_moveScale, m_body->GetPosition().y * g_moveScale);
	m_sprite.setRotation(RadiansToDegrees(m_body->GetAngle()));
}

/**************************************************************************
* ~CPlayer: Destructor; clean up any pointers / free memory
* @parameters:
* @return:
***************************************************************************/
CPlayer::~CPlayer()
{
}

/**************************************************************************
* UpdateMovement: Update the player's movement based on input
* @parameters: moveVec refers to the vector in which to move
* @return:
***************************************************************************/
void CPlayer::Update(sf::Vector2f moveVec)
{
	// Move player
	m_velocity += (m_acceleration / 60) * b2Vec2(moveVec.x, moveVec.y);
	
	// normalize velocity
	b2Vec2 velocityNormalized = m_velocity;
	velocityNormalized.Normalize();
	float SizeofMovement =  b2Vec2(moveVec.x, moveVec.y).LengthSquared();
	if(SizeofMovement > 0)
	{
		//CAudioManager::GetInstance()->PlaySound(AudioToPlay::ShipMove);
	}
	// Apply drag & gravity
	m_velocity -= (m_drag / 60) * velocityNormalized;
	m_velocity.y += m_gravity;

	// Clamp velocity between 0 and max speed
	if (m_velocity.Length() > m_maxSpeed)
	{
		m_velocity = m_maxSpeed * velocityNormalized;
	}
	else if (m_velocity.Length() < 0.0f)
	{
		m_velocity = b2Vec2(0.0f, 0.0f);
	}

	// Apply movement to physics body with a linear impulse
	b2Vec2 changeInVelocity = m_velocity - m_body->GetLinearVelocity();
	b2Vec2 impulse = m_body->GetMass() * changeInVelocity;
	m_body->ApplyLinearImpulseToCenter(impulse, true);
	
	// Stop player from leaving window
	sf::Vector2f outsideWindow = DirectionOutsideWindow(this, m_gameManager->GetGameWindow());
	if (outsideWindow != sf::Vector2f(0, 0))
	{
		sf::Vector2f windowSize = sf::Vector2f(m_gameManager->GetGameWindow()->getSize()) / g_sizeScale;
		b2Vec2 newPos = m_body->GetPosition();
		sf::Vector2f halfPlayerSize = { m_sprite.getGlobalBounds().width / 2 / g_sizeScale, m_sprite.getGlobalBounds().height / 2 / g_sizeScale };

		if (outsideWindow.x == -1.0f)
		{
			newPos.x = halfPlayerSize.x - windowSize.x * 0.075f; // TODO: magic number
		}
		else if (outsideWindow.x == 1.0f)
		{
			newPos.x = windowSize.x * 1.075f - halfPlayerSize.x; // TODO: magic number
		}
		if (outsideWindow.y == -1.0f)
		{
			newPos.y = halfPlayerSize.y;
		}
		else if (outsideWindow.y == 1.0f)
		{
			newPos.y = windowSize.y - halfPlayerSize.y;
		}

		m_body->SetTransform(newPos, m_body->GetAngle());
	}
}

/**************************************************************************
* FireProjectile: Fire a projectile based on the current weapon equipped
* @parameters:
* @return:
***************************************************************************/
void CPlayer::FireProjectile()
{
	// get ammo cost based on weapon type
	int ammoCost = 0;
	switch (m_weaponEquipped)
	{
	case WEAPON_EQUIPPED::e_Torpedo:
		ammoCost = 1;
		break;
	case WEAPON_EQUIPPED::e_Harpoon:
		ammoCost = 2;

		break;
	case WEAPON_EQUIPPED::e_Missile:
		ammoCost = 4;

		break;
	default:
		break;
	}

	if (m_universalAmmo >= ammoCost)
	{
		m_universalAmmo -= ammoCost;
		CAudioManager::GetInstance()->PlaySound("ProjectileFire");
		sf::Vector2f projectilePosition = { m_body->GetPosition().x, m_body->GetPosition().y };
		sf::Vector2f projectileOffset = { 0.0f, 0.0f };
		if (m_playerNum == 2) projectileOffset *= -1.0f;

		m_gameManager->SpawnProjectile(m_weaponEquipped, projectilePosition + projectileOffset, m_direction, this);
	}
	else
	{
		CAudioManager::GetInstance()->PlaySound("FailedToFire");
	}
}


/**************************************************************************
* Respawn: Respawn the player
* @parameters:
* @return:
***************************************************************************/
void CPlayer::Respawn()
{
	CAudioManager::GetInstance()->PlaySound("ShipDestroyed");

	m_sprite.setPosition(m_respawnPosition);
	b2Vec2 respawnPoint = { m_respawnPosition.x, m_respawnPosition.y };
	m_body->SetTransform(respawnPoint, 0.0f);

	m_markedForRespawn = false;
}

/**************************************************************************
* Damage: Apply damage to the player, and respawn the player if possible
* @parameters: damage to apply to the player
* @return:
***************************************************************************/
void CPlayer::Damage(float _damage)
{
	if (_damage > 0)
	{
		m_health -= (int)_damage;
	}

	if (m_health <= 0.0f)
	{
		m_lives -= 1;
		m_health = 100;
		m_markedForRespawn = true;
	}
	else
	{
		CAudioManager::GetInstance()->PlaySound("ShipDamage");
	}
}

/**************************************************************************
* RecieveImpact: Overridden function from base class that is called from the 
*	contact listener when this object collides with another object
* @parameters: damage to apply to the player
* @return:
***************************************************************************/
void CPlayer::RecieveImpact(float _damage)
{
	if (_damage > 0.0f)
	{
		Damage(_damage);
	}
}