/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2023] Media Design School
File Name : CPlayer.h
Description : Header for player class
Authors : Brittney Smith, Manu Easton
**************************************************************************/

#pragma once
// Libraries
#include "CDrawableObject.h"
#include <iostream>	// testing purposes
	// Projectiles
#include "CTorpedo.h"
#include "CMissile.h"
#include "CHarpoon.h"

enum class WEAPON_EQUIPPED
{
	e_Torpedo,
	e_Harpoon,
	e_Missile
};

class CPlayer : public CDrawableObject
{
public:
	CPlayer(class CGameManager* _gameManager, std::shared_ptr<b2World> _box2DWorld, sf::Vector2f _startingPosition, int _playerNum);
	~CPlayer();

	void Update(sf::Vector2f moveVec);
	void FireProjectile();
	void Respawn();

	void Damage(float _damage);
	void RecieveImpact(float _damage) override;

	// Values which need to be adjusted/seen by other classes
	int m_health = 100;
	int m_lives = 3;
	int m_oxygen = 100;
	// Ammunition
	int m_universalAmmo = 0;
	int m_torpedoAmmo = 0;
	int m_missileAmmo = 0;
	int m_harpoonAmmo = 0;
	// Weapons
	WEAPON_EQUIPPED m_weaponEquipped;
	// Game information
	int m_playerNum;

private:
	CGameManager* m_gameManager;

	// Input type (checked to determine input for movement)
	sf::Vector2f m_respawnPosition;

	// Movement values
	b2Vec2 m_velocity = b2Vec2(0.0f, 0.0f);
	float m_maxSpeed = 20.0f;
	float m_acceleration = 50.0f;
	float m_gravity = 0.25f;
	float m_drag = 20.0f;
};