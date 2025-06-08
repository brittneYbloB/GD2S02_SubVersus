/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2023] Media Design School
File Name : CDrawableObject.cpp
Description : Implementation for drawable object base class
Authors : Brittney, Glyn, Manu
**************************************************************************/

#include "CDrawableObject.h"
#include "PhysicsLibrary.h"
#include <iostream>

/**************************************************************************
* CDrawableObject: Constructor for drawable object class
* @parameters:
* @return:
***************************************************************************/
CDrawableObject::CDrawableObject()
{
	m_size = sf::Vector2f(1.0f, 1.0f) * g_sizeScale; // Default size
}

/**************************************************************************
* ~CDrawableObject: Destructor; destroy physics body
* @parameters:
* @return:
***************************************************************************/
CDrawableObject::~CDrawableObject()
{
	m_box2DWorld->DestroyBody(m_body);
}

/**************************************************************************
* GetSize: Getter for object size
* @parameters:
* @return: 2d vector of floats: size
***************************************************************************/
sf::Vector2f CDrawableObject::GetSize()
{
	return m_size / g_sizeScale;
}

/**************************************************************************
* SetSize: Setter for object size
* @parameters: 2d vector of floats: size
* @return:
***************************************************************************/
void CDrawableObject::SetSize(sf::Vector2f _size)
{
	m_size = _size * g_sizeScale;
}

/**************************************************************************
* SetDirection: Set the sprite's direction (sprite polarity)
* @parameters: New direction to face
* @return:
***************************************************************************/
void CDrawableObject::SetDirection(int _direction)
{
	if (_direction == 0) return;
	m_direction = _direction;
}

/**************************************************************************
* CreateSprite: Set the sprite's properties (texture, scale of sprite based on object size and texture size)
* @parameters: Pointer to texture and size of object
* @return:
***************************************************************************/
void CDrawableObject::CreateSprite(sf::Texture* _texture)
{
	// Set sprite's texture to loaded texture
	m_sprite.setTexture(*_texture);

	// Set sprite scale
	m_spriteScale = sf::Vector2f(m_size.x / m_sprite.getTexture()->getSize().x, m_size.y / m_sprite.getTexture()->getSize().y);
	m_sprite.setScale(m_spriteScale);
}

/**************************************************************************
* Draw: Render the sprite to the screen
* @parameters: window, giving an address to the main game window
* @return:
***************************************************************************/
void CDrawableObject::Draw(sf::RenderWindow& _window)
{
	// Set scale of sprite
	m_sprite.setScale(sf::Vector2f(m_spriteScale.x * m_direction, m_spriteScale.y));

	// Set sprite's origin
	m_sprite.setOrigin(float(m_sprite.getTexture()->getSize().x / 2), float(m_sprite.getTexture()->getSize().y / 2));

	// Set position
	m_sprite.setPosition(m_body->GetPosition().x * g_moveScale, m_body->GetPosition().y * g_moveScale);

	// Set rotation
	m_sprite.setRotation(RadiansToDegrees(m_body->GetAngle()));

	if (m_visible)
	{
		_window.draw(m_sprite);
	}
}

/**************************************************************************
* GetBody: Getter for box2d body of object
* @parameters:
* @return: pointer to body
***************************************************************************/
b2Body* CDrawableObject::GetBody()
{
	return m_body;
}

/**************************************************************************
* SetBody: Creates box2d body for object
* @parameters: body type, object shape type, position, rotation and size, 
			   and filter group that allows objects of same negative index to not collide
* @return:
***************************************************************************/
void CDrawableObject::SetBody(std::shared_ptr<b2World> _box2DWorld, b2BodyType _bodyType, b2Shape::Type _shapeType, 
	sf::Vector2f _position, float _rotation, int16 _filterGroup)
{
	m_box2DWorld = _box2DWorld;

	b2BodyDef bodyDef;
	bodyDef.position = b2Vec2((_position.x * g_sizeScale) / g_moveScale, (_position.y * g_sizeScale) / g_moveScale);
	bodyDef.type = _bodyType;
	bodyDef.fixedRotation = true;
	m_body = m_box2DWorld->CreateBody(&bodyDef);

	b2FixtureDef fixtureDef;

	b2PolygonShape polyShape;
	b2CircleShape circleShape;
	switch (_shapeType)
	{
		case b2Shape::Type::e_polygon:
		{
			polyShape.SetAsBox(m_size.x / 2 / g_moveScale, m_size.y / 2 / g_moveScale);
			fixtureDef.shape = &polyShape;
			break;
		}
		case b2Shape::Type::e_circle:
		{
			circleShape.m_radius = m_size.x / 2 / g_moveScale;
			fixtureDef.shape = &circleShape;
			break;
		}
	}

	fixtureDef.friction = 0.5f;
	fixtureDef.density = 1.0f;
	fixtureDef.restitution = 0.3f;
	fixtureDef.filter.groupIndex = _filterGroup; // Allows objects of the same negative index to not collide with one another
	m_body->CreateFixture(&fixtureDef);
}

/**************************************************************************
* RecieveImpact: Resolve collisions with other drawable objects
* @parameters: strength of impact
* @return:
***************************************************************************/
void CDrawableObject::RecieveImpact(float _damage)
{
	if (m_indestructible) return;
	if (GetBody()->GetType() == b2_staticBody) return;

	// resolve collision
	std::cout << "RecieveImpact" << std::endl;
}

/**************************************************************************
* IsMarkedForDestruction: Getter for m_markedForDestruction
* @parameters:
* @return: boolean, whether object is marked for destruction
***************************************************************************/
bool CDrawableObject::IsMarkedForDestruction()
{
	return m_markedForDestroy;
}

/**************************************************************************
* IsMarkedForRespawn: Getter for m_markedForRespawn
* @parameters:
* @return: boolean, whether object is marked to respawn
***************************************************************************/
bool CDrawableObject::IsMarkedForRespawn()
{
	return m_markedForRespawn;
}

/**************************************************************************
* GetDamage: Getter for m_damage
* @parameters:
* @return: float damage caused to colliding objects
***************************************************************************/
float CDrawableObject::GetDamage()
{
	return m_damage;
}
