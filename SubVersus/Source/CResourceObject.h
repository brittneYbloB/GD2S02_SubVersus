/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2023] Media Design School
File Name : CResourceObject.h
Description : Header for base resource object class
Authors : Brittney Smith
**************************************************************************/

#pragma once
#include "CDrawableObject.h"
#include "CPlayer.h"

class CResourceObject 
	: public CDrawableObject
{
protected:
	// Variables
	bool m_isCollected;
	int m_resourceValue;
	CPlayer* m_collidedPlayerReference = nullptr;	// sets once a player has collided with this resource

	// Functions
	virtual void ResourceCollected(CDrawableObject* _playerRef) {};
	void RecieveImpact(float _damage) override;

public:
	CResourceObject();
	virtual ~CResourceObject();
};

