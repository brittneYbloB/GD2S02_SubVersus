/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2023] Media Design School
File Name : CGameManager.h
Description : Header file for game manager, manages game processes and objects
Authors : Manu Easton
**************************************************************************/

#pragma once

// Libraries
#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"
#include <vector>
#include <memory>

// Classes
#include "CPlayer.h"
#include "CTextureManager.h"
#include "CInputManager.h"
#include "CContactListener.h"
#include "CResourceSpawner.h"
#include "CAudioManager.h"
	// Resources
#include "CHealthResource.h"
#include "CAmmoResource.h"
	// Hazards
#include "CNavalMineHazard.h"
	// Projectiles
#include "CTorpedo.h"
#include "CMissile.h"
#include "CHarpoon.h"

class CGameManager
{
public:
	CGameManager();
	~CGameManager();

	void PlayGame();

	void SpawnProjectile(WEAPON_EQUIPPED _weapon, sf::Vector2f _startPos, int _direction, CPlayer* _owningPlayer);

	void Explode(b2Vec2 _explosionPos);

	std::vector<CDrawableObject*> GetGameObjects();
	sf::RenderWindow* GetGameWindow();

	class UI* m_gameUI;
	class CMenuUI* m_menuUI;

private:
	void InitialiseGame();
	void LoadLevel();
	void RestartLevel();

	void Tick();
	void DrawAll();
	void DrawMenu(int _controllerCount = 2);

	GameState CheckGameState();

private:

	// SFML
	std::shared_ptr<sf::RenderWindow> m_outputWindow;
	sf::View m_view;
	const int m_screenWidth = 800;
	const int m_screenHeight = 800;

	// Box2D
	std::shared_ptr<b2World> m_box2DWorld;
	std::shared_ptr<CContactListener> m_box2DContactListener;

	// Key Objects
	std::vector<CDrawableObject*> m_objectsToRender;	// Vector of objects to render
	std::vector<CPlayer*> m_playersInScene;				// Vector of players

	// Managers
	CInputManager m_inputManager;
	CTextureManager* m_textureManager;
	CAudioManager* m_audioPlayer;
	CResourceSpawner* m_objectSpawner = nullptr;

	// Game Variables
	bool m_debugMode = false;
	GameState m_state = GameState::Menu;
	CPlayer* m_winningPlayer = nullptr;

	sf::Sprite m_caveBackground;
	sf::Texture m_caveTexture;
};

