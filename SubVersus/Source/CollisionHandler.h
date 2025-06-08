/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2023] Media Design School
File Name : CollisionHandler.h
Description : Header file for static collision management class
Authors : Brittney Smith
**************************************************************************/

#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"

static class CollisionHandler
{
public:
	/***********************************************
	* ResolveXCollisions: Resolve collisions on the X axis with walls
	* @author: Brittney Smith
	* @parameter: Player collider, wall collider
	* @return:
	************************************************/
	static void ResolveXCollisions(sf::Shape* _CharacterObject, sf::FloatRect* _Collider)
	{
		sf::Vector2f EntityPlayerCenter{ (_CharacterObject->getGlobalBounds().left + _CharacterObject->getGlobalBounds().width / 2.0f),
										(_CharacterObject->getGlobalBounds().top + _CharacterObject->getGlobalBounds().height / 2.0f) };

		sf::Vector2f EntityColliderCenter{ (_Collider->left + _Collider->width / 2.0f),
										(_Collider->top + _Collider->height / 2.0f) };

		if (EntityPlayerCenter.x <= EntityColliderCenter.x)
		{
			float fOffset = -(_CharacterObject->getGlobalBounds().left + _CharacterObject->getGlobalBounds().width - _Collider->left);
			_CharacterObject->move(fOffset, 0.0f);
		}

		if (EntityPlayerCenter.x >= EntityColliderCenter.x)
		{
			float fOffset = (_Collider->left + _Collider->width) - _CharacterObject->getGlobalBounds().left;
			_CharacterObject->move(fOffset, 0.0f);
		}
	};

	/***********************************************
	* ResolveYCollisions: Resolve collisions on the Y axis with walls
	* @author: Brittney Smith
	* @parameter: Player collider, wall collider
	* @return:
	************************************************/
	static void ResolveYCollisions(sf::Shape* _PlayerObject, sf::FloatRect* _Collider)
	{
		sf::Vector2f EntityPlayerCenter{ (_PlayerObject->getGlobalBounds().left + _PlayerObject->getGlobalBounds().width / 2.0f),
										(_PlayerObject->getGlobalBounds().top + _PlayerObject->getGlobalBounds().height / 2.0f) };

		sf::Vector2f EntityColliderCenter{ (_Collider->left + _Collider->width / 2.0f),
										(_Collider->top + _Collider->height / 2.0f) };

		if (EntityPlayerCenter.y <= EntityColliderCenter.y)
		{
			float fOffset = -(_PlayerObject->getGlobalBounds().top + _PlayerObject->getGlobalBounds().height - _Collider->top);
			_PlayerObject->move(0.0f, fOffset);
		}

		if (EntityPlayerCenter.y >= EntityColliderCenter.y)
		{
			float fOffset = (_Collider->top + _Collider->height) - _PlayerObject->getGlobalBounds().top;
			_PlayerObject->move(0.0f, fOffset);
		}
	};

	/***********************************************
	* LoadNextLevel: Check which side the player is colliding with the level loading tile to determine
	* which level to load
	* @author: Brittney Smith
	* @parameter: Player collider, level-loader collider, output window
	* @return: True (Level 2) or False (level 1)
	************************************************/
	static bool LoadNextLevel(sf::Shape* _PlayerObject, sf::FloatRect* _NextLevelCollider, sf::RenderWindow& _RenderWindow)
	{
		sf::Vector2f EntityPlayerCenter{
			(_PlayerObject->getGlobalBounds().left + _PlayerObject->getGlobalBounds().width),
			(_PlayerObject->getGlobalBounds().top + _PlayerObject->getGlobalBounds().height) };

		sf::Vector2f EntityColliderCenter{
			(_NextLevelCollider->left + _NextLevelCollider->width),
			(_NextLevelCollider->top + _NextLevelCollider->height) };

		sf::Vector2f EntityColliderRight{
			(_NextLevelCollider->left + _NextLevelCollider->width),
			(_NextLevelCollider->top + _NextLevelCollider->height) };



		if (EntityPlayerCenter.x <= EntityColliderCenter.x) // collisioin on left of collider
		{
			//std::cout << "Collided with NEXT LEVEL collider" << std::endl;
			// Load Level 2
			return true;
		}
		else if (EntityPlayerCenter.x >= EntityColliderCenter.x)
		{
			//std::cout << "Collided with PREVIOUS LEVEL collider" << std::endl;
			// Load Level 1
			return false;
		}

	}

	/***********************************************
	* OpenDoor: Collision with door
	* @author: Brittney Smith
	* @parameter: Player collider, door collider, output window
	* @return:
	************************************************/
	static void OpenDoor(sf::Shape* _PlayerObject, sf::FloatRect* _DoorCollider, sf::RenderWindow& _RenderWindow)
	{
		sf::Vector2f EntityPlayerCenter{ (_PlayerObject->getGlobalBounds().left + _PlayerObject->getGlobalBounds().width / 2.0f),
								(_PlayerObject->getGlobalBounds().top + _PlayerObject->getGlobalBounds().height / 2.0f) };

		sf::Vector2f EntityColliderCenter{ (_DoorCollider->left + _DoorCollider->width / 2.0f),
										(_DoorCollider->top + _DoorCollider->height / 2.0f) };

		if (EntityPlayerCenter.y <= EntityColliderCenter.y)
		{
			float fOffset = -(_PlayerObject->getGlobalBounds().top + _PlayerObject->getGlobalBounds().height - _DoorCollider->top);
			_PlayerObject->move(0.0f, fOffset);
		}

		if (EntityPlayerCenter.y >= EntityColliderCenter.y)
		{
			float fOffset = (_DoorCollider->top + _DoorCollider->height) - _PlayerObject->getGlobalBounds().top;
			_PlayerObject->move(0.0f, fOffset);
		}
	}
};