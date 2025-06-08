/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2023] Media Design School
File Name : CHealthResource.h
Description : Header for health collectible resource
Authors : Brittney Smith
**************************************************************************/

#pragma once
#include "CResourceObject.h"

class CHealthResource :
    public CResourceObject
{
public:
    CHealthResource(std::shared_ptr<b2World> _box2DWorld, sf::Vector2f _startingPosition);

    void ResourceCollected(CDrawableObject* _playerRef) override;
};

