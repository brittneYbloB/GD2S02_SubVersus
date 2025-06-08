/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2023] Media Design School
File Name : CResourceSpawner.cpp
Description : Resource spawner class to spawn resources
Author : Brittney Smith
**************************************************************************/

#include "CResourceSpawner.h"
#include "CGameManager.h"
#include "CEnvironmentHazard.h"
#include "CResourceObject.h"
#include "CAmmoResource.h"
#include "CHealthResource.h"
#include "CNavalMineHazard.h"

#define MIN_HEALTHRESOURCE 1
#define MIN_AMMORESOURCE 1
#define MIN_STALACTITE 4
#define MIN_NAVALMINE 4

/**************************************************************************
* CResourceSpawner:  Constructor for resource spawner
* @parameters: Object to spawn, rate to spawn at, locations to spawn at, range from locations to spawn at
*
***************************************************************************/
CResourceSpawner::CResourceSpawner(CGameManager* _gameManager, std::shared_ptr<b2World> _box2DWorld, std::vector<sf::Vector2f> _resourceSpawnLocations, std::vector<sf::Vector2f> _hazardSpawnLocations)
{
	m_gameManager = _gameManager;
	m_box2DWorld = _box2DWorld;

	m_hazardSpawnLocations = _hazardSpawnLocations;
	m_resourceSpawnLocations = _resourceSpawnLocations;

	m_resourceClock =  new sf::Clock();
	m_hazardClock = new sf::Clock();
}

/**************************************************************************
* SaveRespawnObjectType: Determine the type of resource which requires replacing
* @parameters: Object (just deleted)
* @return: 
***************************************************************************/
void CResourceSpawner::SaveRespawnObjectType(CDrawableObject* _object)
{
	if (_object != nullptr)
	{
		// Check if spawning resource
		if (dynamic_cast<CResourceObject*>(_object) != nullptr)
		{
			m_typeToSpawn = OBJECTTYPE::e_RESOURCE;
		}
		// Check if spawning hazard
		else if (dynamic_cast<CEnvironmentHazard*>(_object) != nullptr)
		{
			m_typeToSpawn = OBJECTTYPE::e_HAZARD;
		}
	}
}


/**************************************************************************
* CheckIfSpawnRequired: Check if the minimum amount of objects exist in the arena, and 
*	respawn if not
* @parameters: Vector of existing rendering objects
* @return: New (spawned) object, or nullptr if unsuccessful/uneccessary
***************************************************************************/
CDrawableObject* CResourceSpawner::CheckIfSpawnRequired(std::vector<CDrawableObject*> _objectsInScene)
{
	int numHealth = 0;
	int numAmmo = 0;
	int numStalactite = 0;
	int numMines = 0;

	// Clear the stored occupied locations (reseting vector)
	m_occupiedLocations.clear();

	// Delay of 8 seconds before each respawn (check)
	if (m_resourceClock->getElapsedTime() > sf::seconds(m_spawnDelay))
	{
		// Iterate through the object, tracking which TYPE it is and HOW MANY there are
		for (auto IterObjects : _objectsInScene)
		{
			// Check if spawning HEALTH resource
			if (dynamic_cast<CHealthResource*>(IterObjects) != nullptr)
			{
				numHealth++;
			}
			// Check if spawning AMMO resource
			else if (dynamic_cast<CAmmoResource*>(IterObjects) != nullptr)
			{
				numAmmo++;
			}
		}

		// Reset timer
		m_resourceClock->restart();

		/* Check if the existing types meet the minimum, otherwise spawn
		NOTE: This does get overridden, returning the first type only if it is less than required ammount (IE: ORDERED BY PRIORITY) */
		if (numAmmo < MIN_AMMORESOURCE) { return SpawnAmmo(); }
		if (numHealth < MIN_HEALTHRESOURCE) { return SpawnHealth(); }
	}

	if (m_hazardClock->getElapsedTime() > sf::seconds(m_spawnDelay))
	{
		for (auto IterObjects : _objectsInScene)
		{
			// Check if spawning NAVAL MINE hazard
			if (dynamic_cast<CNavalMineHazard*>(IterObjects) != nullptr)
			{
				numMines++;
				m_occupiedLocations.push_back(IterObjects->m_spawnPosition);
			}
			// Check if spawning STALACTITE hazard
			else if (dynamic_cast<CEnvironmentHazard*>(IterObjects) != nullptr)
			{
				numStalactite++;
				m_occupiedLocations.push_back(IterObjects->m_spawnPosition);
			}
		}

		m_hazardClock->restart();

		if (numStalactite < MIN_STALACTITE) { return SpawnStalactite(); }
		if (numMines < MIN_NAVALMINE) { return SpawnNavalMine(); }
	}
	
	return nullptr;	// if nothing requires respawn (this is checked for in GM)
}

/**************************************************************************
* SpawnHazard: Spawn new random hazard object
* @parameters: 
* @return: object created
***************************************************************************/
CDrawableObject* CResourceSpawner::SpawnHazard()
{	
	CDrawableObject* newHazard;
	
	// Random number to determine which hazard type to spawn
	int randomNum = rand() % static_cast<int>(2);	// eiter 0 or 1
	
	// Randomly decide which hazard to spawn
	if (randomNum == 0)
	{
		// Spawn stalactite
		newHazard = SpawnStalactite();
	}
	else
	{
		// Spawn naval mine
		newHazard = SpawnNavalMine();
	}
	
	return newHazard;
}

/**************************************************************************
* SpawnResource: Spawn new random resource object
* @parameters:
* @return: object created
***************************************************************************/
CDrawableObject* CResourceSpawner::SpawnResource()
{
	CDrawableObject* newResource;

	// Random number to determine which hazard type to spawn
	int randomNum = rand() % static_cast<int>(2);	// eiter 0 or 1

	// Randomly decide which resource to spawn
	if (randomNum == 0)
	{
		// Spawn ammo
		newResource = SpawnAmmo();
	}
	else
	{
		// Spawn health
		newResource = SpawnHealth();
	}

	return newResource;
}

/**************************************************************************
* SpawnHealth: Spawn health
* @parameters:
* @return: object created
***************************************************************************/
CDrawableObject* CResourceSpawner::SpawnHealth()
{
	// Generate random spawn location based on existing hazard spawn locations
	int randomResourceLoc = rand() % static_cast<int>(m_resourceSpawnLocations.size());
	sf::Vector2f spawnLocation = m_resourceSpawnLocations[randomResourceLoc];

	return new CHealthResource(m_box2DWorld, spawnLocation);
}


/**************************************************************************
* SpawnAmmo: Spawn ammo
* @parameters:
* @return: object created
***************************************************************************/
CDrawableObject* CResourceSpawner::SpawnAmmo()
{
	// Generate random spawn location based on existing hazard spawn locations
	int randomResourceLoc = rand() % static_cast<int>(m_resourceSpawnLocations.size());
	sf::Vector2f spawnLocation = m_resourceSpawnLocations[randomResourceLoc];

	return new CAmmoResource(m_box2DWorld, spawnLocation); ;
}


/**************************************************************************
* SpawnStalactite: Spawn a stalactite
* @parameters:
* @return: object created
***************************************************************************/
CDrawableObject* CResourceSpawner::SpawnStalactite()
{
	CDrawableObject* newHazard;

	bool validPos = false;
	sf::Vector2f spawnLocation;

	int loopCounter = 0;

	// While I haven't found a valid position yet...
	while (!validPos)
	{
		validPos = false;

		// Generate random spawn location based on existing hazard spawn locations
		int randomHazardLoc = rand() % static_cast<int>(m_hazardSpawnLocations.size());
		spawnLocation = m_hazardSpawnLocations[randomHazardLoc];

		// Check if the spawn location is valid for a stalactite (NOT a mine depth)
		if (spawnLocation.y < 50.0f) // is high enough enough
		{
			validPos = true;	// there is hope! you're at the right depth!
		}
		// Check if spawn location is already occupied
		if (validPos)
		{
			for (unsigned int i = 0; i < m_occupiedLocations.size(); i++)
			{
				if (spawnLocation.x == m_occupiedLocations[i].x && m_occupiedLocations[i].y < 50.0f)
				{
					validPos = false;	// uh oh! you share the same X :[
					break;
				}
			}
		}
	}


	// Spawn stalactite
	return newHazard = new CEnvironmentHazard(m_box2DWorld, spawnLocation);
}


/**************************************************************************
* SpawnNavalMine: Spawn a naval mine
* @parameters:
* @return: object created
***************************************************************************/
CDrawableObject* CResourceSpawner::SpawnNavalMine()
{
	CDrawableObject* newHazard;

	bool validPos = false;
	sf::Vector2f spawnLocation;

	// While I haven't found a valid position yet...
	while (!validPos)
	{
		// Generate random spawn location based on existing hazard spawn locations
		int randomHazardLoc = rand() % static_cast<int>(m_hazardSpawnLocations.size());
		spawnLocation = m_hazardSpawnLocations[randomHazardLoc];

		// Check if the spawn location is valid for a mine (NOT a stalactite depth)
		if (spawnLocation.y > 50.0f) // is low enough enough
		{
			validPos = true;	// there is hope! you're at the right depth!
		}
		// Check if spawn location is already occupied
		if (validPos)
		{
			for (unsigned int i = 0; i < m_occupiedLocations.size(); i++)
			{
				if (spawnLocation.x == m_occupiedLocations[i].x && m_occupiedLocations[i].y > 50.0f)
				{
					validPos = false;	// uh oh! you share the same X :[
					break;
				}
			}
		}
	}

	// Spawn naval mine
	return newHazard = new CNavalMineHazard(m_gameManager, m_box2DWorld, spawnLocation);
}
