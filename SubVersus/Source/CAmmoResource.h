/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2023] Media Design School
File Name : CAmmoResource.h
Description : Header for ammo collectible item
Authors : Brittney Smith
**************************************************************************/

#pragma once
#include "CResourceObject.h"


class CAmmoResource :
    public CResourceObject
{
private:
    int m_ammoValue = 0;

public:
    CAmmoResource(std::shared_ptr<b2World> _box2DWorld, sf::Vector2f _startingPosition);
    ~CAmmoResource() { delete m_collidedPlayerReference; };

    void ResourceCollected(CDrawableObject* _playerRef) override;
};

