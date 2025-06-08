/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2023] Media Design School
File Name : CNavalMineHazard.cpp
Description : Implementation file for naval mine environmental hazard
Authors : Brittney Smith
**************************************************************************/

#include "CNavalMineHazard.h"
#include "CGameManager.h"
#include "CAudioManager.h"

/**************************************************************************
* CNavalMineHazard: Create Box2D body & initialize naval mine hazard
* @parameters: pointer to game manager, box2d world & position
* @return:
***************************************************************************/
CNavalMineHazard::CNavalMineHazard(CGameManager* _game, std::shared_ptr<b2World> _box2DWorld, sf::Vector2f _startingPosition)
{
	game = _game;

	SetSize(sf::Vector2f(4.0f, 4.0f));

	// Sprite setting
	CreateSprite(CTextureManager::GetInstance()->GetNavalMineTexture());

	// Set Box2D body
	SetBody(_box2DWorld, b2BodyType::b2_kinematicBody, b2Shape::Type::e_polygon, _startingPosition, 0.0f);

	// Set mine to rise
	m_body->SetLinearVelocity(b2Vec2(0.0f, -5.0f));

	// Set position reference (for position spawning validation checks)
	m_spawnPosition = _startingPosition;

	// Damage value
	m_damage = 20.0f;


	// Random depth (for variance)
	m_depth = float(45 + (rand() % (80 - 60 + 1)));
}

/**************************************************************************
* RecieveImpact: Overridden function from base drawable - explode on impact
* @parameters: damage of impact
* @return:
***************************************************************************/
void CNavalMineHazard::RecieveImpact(float _damage)
{
	CAudioManager::GetInstance()->PlaySound("NavalMineHit");

	if (game)
	{
		game->Explode(GetBody()->GetPosition());
		m_markedForDestroy = true;
	}
}

/**************************************************************************
* Update: Stops mine from rising once it reaches specific height
* @parameters:
* @return:
***************************************************************************/
void CNavalMineHazard::Update()
{
	if (m_body->GetPosition().y < m_depth)
	{
		m_body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
	}
}
