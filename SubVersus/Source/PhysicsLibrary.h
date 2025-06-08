/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2022] Media Design School
File Name : CPhysicsLibrary.h
Description : Header file for physics library, contains static functions for physics calculations
Authors : Manu Easton
**************************************************************************/

#pragma once
#include "box2d/box2d.h"
#include "CDrawableObject.h"

const inline b2Vec2 g_gravityValue(0.0f, 0.0f);
const inline float g_sizeScale = 10.0f;
const inline float g_moveScale = 10.0f;
const inline float g_frameRate = 60.0f;

/**************************************************************************
* DetectCollision: Detects collision between two CDrawableObjects using sprite bounds
* @parameters: Pointers to the two objects to check
* @return: boolean, objects colliding
***************************************************************************/
inline bool DetectCollision(CDrawableObject* _objectA, CDrawableObject* _objectB)
{
	bool colliding = _objectA->GetSprite()->getGlobalBounds().intersects(_objectB->GetSprite()->getGlobalBounds());

	if (colliding)
	{
		//std::cout << "Colliding" << std::endl;
	}

	return colliding;
}

/**************************************************************************
* CalculateDistance: Finds distance betweem two CDrawableObjects
* @parameters: Pointers to the two objects to find distance between
* @return: float, distance between centers of objects
***************************************************************************/
inline float CalculateDistance(CDrawableObject* _objectA, CDrawableObject* _objectB)
{
	return sqrtf(powf(_objectA->GetBody()->GetPosition().x - _objectB->GetBody()->GetPosition().x, 2) +
		powf(_objectA->GetBody()->GetPosition().y - _objectB->GetBody()->GetPosition().y, 2));
}

/**************************************************************************
* RadiansToDegrees: Converts a radian value to degrees
* @parameters: float, radian value
* @return: float, value in degrees
***************************************************************************/
inline float RadiansToDegrees(float _radians)
{
	return _radians * (float)(180.0f / b2_pi);
}

/**************************************************************************
* DegreesToRadians: Converts a degree value to radians
* @parameters: float, degree value
* @return: float, value in radians
***************************************************************************/
inline float DegreesToRadians(float _degrees)
{
	return _degrees * (float)(b2_pi / 180.0f);
}

/**************************************************************************
* WithinWindow: Checks whether an object is within a window
* @parameters: Pointer to object to check, reference to window to check in
* @return: bool, whether object is within window
***************************************************************************/
inline bool WithinWindow(CDrawableObject* _object, sf::RenderWindow* _window)
{
	// Basing check off sprite position and size inside SFML window
	sf::Vector2f position = _object->GetSprite()->getPosition();
	sf::Vector2f size = sf::Vector2f(_object->GetSprite()->getGlobalBounds().width, _object->GetSprite()->getGlobalBounds().height);

	if (position.x + size.x / 2 < 0 || position.x - size.x / 2 > _window->getSize().x || position.y + size.y / 2 < 0 || position.y - size.y / 2 > _window->getSize().y)
	{
		// Outside of window
		return false;
	}
	
	// Inside window
	return true;

}

/**************************************************************************
* DirectionOutsideWindow: Returns direction that object is outside window
* @parameters: Pointer to object to check, reference to window to check in
* @return: sf::Vector2f, direction object is outside window, or 0,0 if fully within window
***************************************************************************/
inline sf::Vector2f DirectionOutsideWindow(CDrawableObject* _object, sf::RenderWindow* _window, bool _fullyWithin = false)
{
	// Basing check off sprite position and size inside SFML window
	sf::Vector2f position = _object->GetSprite()->getPosition();
	sf::Vector2f size = sf::Vector2f(_object->GetSprite()->getGlobalBounds().width, _object->GetSprite()->getGlobalBounds().height);

	sf::Vector2f dirVector = { 0, 0 };

	if (position.x - size.x / 2 < 0 - ((float)_window->getSize().x * 0.075f)) // TODO: magic number - more accurate level bounds possible
	{
		dirVector.x = -1.0f;
	}
	else if (position.x + size.x / 2 > ((float)_window->getSize().x * 1.075f)) // TODO: magic number - more accurate level bounds possible
	{
		dirVector.x = 1.0f;
	}
	if (position.y - size.y / 2 < 0)
	{
		dirVector.y = -1.0f;
	}
	else if (position.y + size.y / 2 > _window->getSize().y)
	{
		dirVector.y = 1.0f;
	}

	return dirVector;
}