/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2023] Media Design School
File Name : CDrawableObject.h
Description : Header for drawable object base class
Authors : Brittney, Glyn, Manu
**************************************************************************/

#pragma once
// Library
#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"
#include "CTextureManager.h"

class CDrawableObject
{
protected:
	// Variables
	sf::Sprite m_sprite;
	sf::Vector2f m_size;
	sf::Vector2f m_spriteScale;
	int m_direction = 1;

	bool m_visible = true;
	float m_movementSpeed = 1.0f;
	float m_damage = 0.0f;


	CTextureManager* m_textureManager = nullptr;

	// Box2d variables
	b2Body* m_body;
	std::shared_ptr<b2World> m_box2DWorld;
	bool m_indestructible = false;
	bool m_markedForDestroy = false;
	bool m_markedForRespawn = false;

	void CreateSprite(sf::Texture* _texture);

public:
	// Functions
	CDrawableObject();
	~CDrawableObject();

	void Draw(sf::RenderWindow& _window);
	virtual void Update() {};

	sf::Vector2f GetSize();
	void SetSize(sf::Vector2f _size);
	sf::Sprite* GetSprite() { return &m_sprite; };
	void SetDirection(int _direction);

	float GetDamage();

	// Box2D functions
	void SetBody(std::shared_ptr<b2World> _box2DWorld, b2BodyType _bodyType, b2Shape::Type _shapeType, 
		sf::Vector2f _position, float _rotation, int16 _filterGroup = 0);
	b2Body* GetBody();
	virtual void RecieveImpact(float _damage);
	bool IsMarkedForDestruction();
	bool IsMarkedForRespawn();

	// References to other objects in scene
	CDrawableObject* m_playerOneRef;
	CDrawableObject* m_playerTwoRef;

	// Box2D parameter for ignoring collisions
	int m_filterGroup = 0;

	// Position set and used to validate spawn locations for hazards and/or resources
	sf::Vector2f m_spawnPosition;
};

