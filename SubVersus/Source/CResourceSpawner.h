/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2023] Media Design School
File Name : CResourceSpawner.h
Description : Header for resource spawner class to spawn resources
Author : Brittney Smith
**************************************************************************/

#pragma once
#include "CResourceObject.h"

enum class OBJECTTYPE
{
	e_NOTSELECTED,
	e_HAZARD,
	e_RESOURCE
};


class CResourceSpawner
{
public:
	CResourceSpawner(class CGameManager* _gameManager, std::shared_ptr<b2World> _box2DWorld, std::vector<sf::Vector2f> _resourceSpawnLocations, std::vector<sf::Vector2f> _hazardSpawnLocations);
	~CResourceSpawner() {};

	void SaveRespawnObjectType(CDrawableObject* _object);
	CDrawableObject* CheckIfSpawnRequired(std::vector<CDrawableObject*> _objectsInScene);

	CDrawableObject* SpawnHazard();
	CDrawableObject* SpawnResource();

	CDrawableObject* SpawnHealth();
	CDrawableObject* SpawnAmmo();
	CDrawableObject* SpawnStalactite();
	CDrawableObject* SpawnNavalMine();


	bool m_canSpawnObject = false;

private:
	std::shared_ptr<b2World> m_box2DWorld;
	CGameManager* m_gameManager;
	std::vector<sf::Vector2f> m_hazardSpawnLocations;
	std::vector<sf::Vector2f> m_resourceSpawnLocations;
	float m_spawnTimer;
	float m_spawnDelay = 4.0f;
	OBJECTTYPE m_typeToSpawn = OBJECTTYPE::e_NOTSELECTED;
	sf::Clock* m_resourceClock = nullptr;
	sf::Clock* m_hazardClock = nullptr;
	std::vector<sf::Vector2f> m_occupiedLocations;
	
};

