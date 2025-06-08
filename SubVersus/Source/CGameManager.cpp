/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2023] Media Design School
File Name : CGameManager.cpp
Description : Implementation file for game manager
Authors : Brittney Smith, Manu Easton, Glyn Fleming-Bone
**************************************************************************/

#include "CGameManager.h"
#include "UI.h"
#include "CMenuUI.h"
#include "PhysicsLibrary.h"
#include <iostream>
#include <algorithm>


/**************************************************************************
* CGameManager: Constructor for game manager class
* @parameters:
* @return:
***************************************************************************/
CGameManager::CGameManager()
{
	m_textureManager = CTextureManager::GetInstance();

	PlayGame();
}

/**************************************************************************
* ~CGameManager: Destructor for game manager class, free up memory
* @parameters:
* @return:
***************************************************************************/
CGameManager::~CGameManager()
{
	for (auto iter : m_objectsToRender)
	{
		delete iter;
	}
	m_objectsToRender.clear();

	// Player objects deleted in m_objectsToRender vector
	m_playersInScene.clear();
}

/**************************************************************************
* InitialiseGame: Initialise variables in game manager before the game starts
* @parameters:
* @return:
***************************************************************************/
void CGameManager::InitialiseGame()
{
	/* initialize random seed: */
	srand((int)time(NULL));

	// Create rendering window
	m_outputWindow = std::make_shared<sf::RenderWindow>(sf::VideoMode(m_screenWidth, m_screenHeight), "SubVersus");
	// Limit framerate
	m_outputWindow->setFramerateLimit((int)g_frameRate);
	// Create game camera (view)
	m_view = sf::View(sf::Vector2f((float)m_screenWidth / 2.0f, (float)m_screenHeight / 2.0f), sf::Vector2f((float)m_screenWidth, (float)m_screenHeight));
	m_outputWindow->setView(m_view);

	// Create box2d world
	m_box2DWorld = std::make_shared<b2World>(g_gravityValue);
	
	// Set world contact listener to listen for contacts between objects
	m_box2DContactListener = std::make_shared<CContactListener>(m_box2DWorld.get(), this);
	m_box2DWorld->SetContactListener(m_box2DContactListener.get());


	//set menu music to play
	m_audioPlayer = CAudioManager::GetInstance();
	m_audioPlayer->PlayMusic("underwater_ambient");

	// Game object initialisation
	// Background
	m_caveTexture.loadFromFile("./Sprites/seaCave.png");
	m_caveBackground.setTexture(m_caveTexture);

	sf::Vector2f backgroundScale = { (m_screenWidth * 1.5f) / m_caveBackground.getGlobalBounds().width, m_screenHeight / m_caveBackground.getGlobalBounds().height }; // TODO: 1.125f = magic number
	m_caveBackground.setScale(backgroundScale);
	m_caveBackground.setPosition(sf::Vector2f(-(m_screenWidth * 0.25f), 0.0f)); // TODO: 0.075f = magic number

	// Player 1
	CDrawableObject* playerOne = new CPlayer(this, m_box2DWorld, sf::Vector2f(20.0f, 40.0f), 1);
	m_objectsToRender.push_back(playerOne);
	m_playersInScene.push_back(dynamic_cast<CPlayer*>(playerOne));

	// Player 2
	CDrawableObject* playerTwo = new CPlayer(this, m_box2DWorld, sf::Vector2f(60.0f, 40.0f), 2);
	m_objectsToRender.push_back(playerTwo);
	m_playersInScene.push_back(dynamic_cast<CPlayer*>(playerTwo));

	// Game UI
	m_gameUI = new UI();
	m_gameUI->m_activePlayers = m_playersInScene;
	m_gameUI->CreateUISprites();

	// Menu UI
	m_menuUI = new CMenuUI();
	m_menuUI->CreateUISprites();

	// Input manager
	m_inputManager = CInputManager();
	m_inputManager.InitialiseInputManager(m_playersInScene[0], m_playersInScene[1]);

	LoadLevel();
}

/**************************************************************************
* LoadLevel: Creates all objects to make up the game level
* @parameters:
* @return:
***************************************************************************/
void CGameManager::LoadLevel()
{
	// Creation of stalactite objects for testing
	for (int i = 1; i < 5; i++)
	{
		CDrawableObject* newStalactite = new CEnvironmentHazard(m_box2DWorld, sf::Vector2f(i * 17.5f, 10.0f));
		m_objectsToRender.push_back(newStalactite);
	}

	// Creation of naval mine objects for testing
	for (int i = 1; i < 5; i++)
	{
		CDrawableObject* newMine = new CNavalMineHazard(this, m_box2DWorld, sf::Vector2f(i * 17.5f, 80.0f));
		m_objectsToRender.push_back(newMine);
	}

	// Health resource for testing
	CDrawableObject* newHealthRes = new CHealthResource(m_box2DWorld, sf::Vector2f(20.0f, 10.0f));
	m_objectsToRender.push_back(newHealthRes);

	// Ammo resource for testing
	CDrawableObject* newAmmoRes = new CAmmoResource(m_box2DWorld, sf::Vector2f(40.0f, 10.0f));
	m_objectsToRender.push_back(newAmmoRes);

	// Set possible spawn locations
	std::vector<sf::Vector2f> resourceSpawnLocations;
	for (int i = 1; i < 5; i++)
	{
		resourceSpawnLocations.push_back(sf::Vector2f(i * 17.5f, 10.0f));	// resource positions
	}
	std::vector<sf::Vector2f> hazardSpawnLocations;
	for (int i = 1; i < 5; i++)
	{
		hazardSpawnLocations.push_back(sf::Vector2f(i * 17.5f, 10.0f));	// stalactie positions
	}
	for (int j = 1; j < 5; j++)
	{
		hazardSpawnLocations.push_back(sf::Vector2f(j * 17.5f, 80.0f));	// naval mine positions
	}
	// Initiate spawner with these possible spawn locations
	m_objectSpawner = new CResourceSpawner(this, m_box2DWorld, resourceSpawnLocations, hazardSpawnLocations);
}

/**************************************************************************
* RestartLevel: After game is finished, clear objects, reload players and go to menu
* @parameters:
* @return:
***************************************************************************/
void CGameManager::RestartLevel()
{
	for (CDrawableObject* obj : m_objectsToRender)
	{
		if (dynamic_cast<CPlayer*>(obj)) continue;
		delete obj;
	}
	m_objectsToRender.clear();
	LoadLevel();
	for (CPlayer* player : m_playersInScene)
	{
		m_objectsToRender.push_back(player);
		player->m_lives = 3;
		player->m_universalAmmo = 5;
		player->Respawn();
	}
	m_state = GameState::Menu;
}

/**************************************************************************
* PlayGame: Contains game loop for running game
* @parameters:
* @return:
***************************************************************************/
void CGameManager::PlayGame()
{
	InitialiseGame();

	while (m_outputWindow->isOpen())
	{
		// Window Events
		sf::Event event;
		while (m_outputWindow->pollEvent(event))
		{
			// Check if the window .exe is closed
			if (event.type == sf::Event::Closed)
			{
				m_outputWindow->close();
			}
			// Resize canvas window without changing anything
			if (event.type == sf::Event::Resized)
			{
				sf::FloatRect OutputWindowArea(0.0f, 0.0f, float(event.size.width), float(event.size.height));
				m_outputWindow->setView(sf::View(OutputWindowArea));
			}
			// Debug mode: Test game using keyboard controls
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Enter)
				{
					m_debugMode = true;
					m_audioPlayer->PlayMusic("ActionMusic_David_Fesliyan");

					m_state = GameState::Playing;
				}
			}
		}

		Tick();
	}
}

/**************************************************************************
* GetGameObjects: Getter for all game objects to be affected by physics
* @parameters:
* @return: vector of pointers to drawable objects
***************************************************************************/
std::vector<CDrawableObject*> CGameManager::GetGameObjects()
{
	return m_objectsToRender;
}

/**************************************************************************
* GetGameWindow: Getter for game RenderWindow
* @parameters:
* @return: pointer to m_outputWindow
***************************************************************************/
sf::RenderWindow* CGameManager::GetGameWindow()
{
	return m_outputWindow.get();
}

/**************************************************************************
* Tick: Updates world, checks for input and draws all objects each tick
* @parameters:
* @return:
***************************************************************************/
void CGameManager::Tick()
{
	m_state = CheckGameState();

	// if using debug mode, use keyboard input
	if (m_debugMode)
	{
		// 1 = player requested restart
		if (m_inputManager.PollDebugInput(m_state) == 1)
		{
			m_state = GameState::Menu;
		}
	}
	// if not using debug mode, use controller input
	else
	{
		// check for input
		unsigned int controllerCount = m_inputManager.PollInput(m_state);

		if (m_state == GameState::MatchComplete && controllerCount == 1)
		{
			m_state = GameState::Menu;
		}

		// if not enough controllers, display menu & warnings
		if (m_state == GameState::Menu)
		{
			// stop playing (currently empty so testing with keyboard is possible) & print msg needing controller
			DrawMenu(controllerCount);

			// if trying to play game
			if (controllerCount == 2 && m_inputManager.PollMenuInput() == 1)
			{
				RestartLevel();
				m_state = GameState::Playing;
				return;
			}
			// if trying to quit game
			if (m_inputManager.PollMenuInput() == 2)
			{
				m_outputWindow->close();
			}

			return;
		}
	}

	if (m_state != GameState::MatchComplete)
	{
		// Step simulation forward one frame
		m_box2DWorld->Step(1.0f / g_frameRate, 8, 3);	// TODO: magic numbers

		//// Check if respawner has respawned an object. If so, add to vector of rendering objects
		//CDrawableObject* respawnObject = m_objectSpawner->Update();
		//if (respawnObject) {
		//	m_objectsToRender.push_back(respawnObject);
		//}
		// Check if a resource/harzard spawn if required
		CDrawableObject* respawnObject = m_objectSpawner->CheckIfSpawnRequired(m_objectsToRender);
		if (respawnObject) {
			m_objectsToRender.push_back(respawnObject);
		}

		for (unsigned int i = 0; i < m_objectsToRender.size(); i++)
		{
			if (m_objectsToRender[i] != nullptr)
			{
				m_objectsToRender[i]->Update();

				if (m_objectsToRender[i]->IsMarkedForDestruction() || !WithinWindow(m_objectsToRender[i], m_outputWindow.get()))
				{
					// Respawn hazard/resource, depending on what is currently being deleted
					m_objectSpawner->SaveRespawnObjectType(m_objectsToRender[i]);
					m_objectSpawner->m_canSpawnObject = true;

					// Destroy
					delete m_objectsToRender[i];
					m_objectsToRender.erase(m_objectsToRender.begin() + i);
					i--;
				}
				else if (m_objectsToRender[i]->IsMarkedForRespawn())
				{
					// respawn a player marked for respawning
					dynamic_cast<CPlayer*>(m_objectsToRender[i])->Respawn();
				}
			}
		}
	}

	DrawAll();
}

/**************************************************************************
* DrawAll: Render all game objects to screen
* @parameters:
* @return:
***************************************************************************/
void CGameManager::DrawAll()
{
	// Clear the output window
	m_outputWindow->clear();

	// Draw background
	m_outputWindow->draw(m_caveBackground);

	// Update drawable objects
	for (CDrawableObject* drawableObjectIter : m_objectsToRender)
	{
		if (drawableObjectIter != nullptr)
		{
			drawableObjectIter->Draw(*m_outputWindow);
		}
	}

	// Update Gameplay UI
	if (m_state == GameState::Playing)
	{
		m_gameUI->UpdateUI(*m_outputWindow);
	}
	// draw end screen, winner based on if player 1 exists or not
	else if (m_state == GameState::MatchComplete)
	{
		m_gameUI->DrawEndScreen(*m_outputWindow, m_playersInScene[0] == m_winningPlayer ? 1 : 2);
	}

	// Camera & Display
	if (m_state == GameState::Playing)
	{
		float p1Pos = m_playersInScene[1]->GetSprite()->getPosition().x;
		float p2Pos = m_playersInScene[0]->GetSprite()->getPosition().x;
		float dist = abs(m_playersInScene[1]->GetSprite()->getPosition().x - p2Pos);
		m_view.setCenter(sf::Vector2f(
			std::clamp((p2Pos > p1Pos ? p2Pos : p1Pos) - dist / 2, 250.0f, 550.0f),
			m_view.getCenter().y
		));
	}
	m_outputWindow->setView(m_view);
	m_outputWindow->display();
}

/**************************************************************************
* DrawMenu: Render menu objects to screen
* @parameters:
* @return:
***************************************************************************/
void CGameManager::DrawMenu(int _controllerCount)
{
	// Clear the output window
	m_outputWindow->clear();

	// Draw background
	m_outputWindow->draw(m_caveBackground);

	m_menuUI->DrawMenu(*m_outputWindow, m_inputManager.GetControllerCount());

	// Display
	m_view.setCenter(sf::Vector2f(400.0f, 400.0f));
	m_outputWindow->setView(m_view);
	m_outputWindow->display();
}

/**************************************************************************
* CheckGameState: Check what players are alive/dead and return the state of the game
* @parameters:
* @return: enum of game state relating to how many players are alive
***************************************************************************/
GameState CGameManager::CheckGameState()
{
	// early out if not enough controllers or already on menu
	if (m_state == GameState::Menu || (!m_debugMode && m_inputManager.GetControllerCount() < 2))
	{
		return GameState::Menu;
	}

	int numPlayersAlive = 0;

	for (auto iter : m_playersInScene)
	{
		if (iter->m_lives > 0) // Player is alive
		{
			numPlayersAlive++;
			m_winningPlayer = iter;
		}
	}

	// return game state
	if (numPlayersAlive == 1)
	{
		// End game
		return GameState::MatchComplete;
	}
	else if (numPlayersAlive == 0)
	{
		return GameState::Menu;
	}
	return GameState::Playing;
}


/**************************************************************************
* SpawnProjectile: Spawn a projectile in the scene
* @parameters: Type of projectile weapon to spawn, position and angle to spawn at, and pointer to player that fired the projectile
* @return:
***************************************************************************/
void CGameManager::SpawnProjectile(WEAPON_EQUIPPED _weapon, sf::Vector2f _startPos, int _direction, CPlayer* _owningPlayer)
{
	// flip direction for player 2
	(_owningPlayer->m_playerNum == 1) ? _direction = _direction : _direction = -_direction;

	switch (_weapon)
	{
	case WEAPON_EQUIPPED::e_Harpoon:
	{
		CHarpoon* newHarpoon = new CHarpoon(_owningPlayer, m_box2DWorld, _startPos, _direction);
		m_objectsToRender.push_back(newHarpoon);

		break;
	}
	case WEAPON_EQUIPPED::e_Missile:
	{
		CPlayer* targetPlayer;
		// Determine which player is target player - player who does not own the missile
		_owningPlayer == m_playersInScene[0] ? targetPlayer = m_playersInScene[1] : targetPlayer = m_playersInScene[0];

		CMissile* newMissile = new CMissile(_owningPlayer, targetPlayer, m_box2DWorld, _startPos, _direction);
		m_objectsToRender.push_back(newMissile);

		break;
	}
	case WEAPON_EQUIPPED::e_Torpedo:
	{
		CTorpedo* newTorpedo = new CTorpedo(_owningPlayer, m_box2DWorld, _startPos, _direction);
		m_objectsToRender.push_back(newTorpedo);

		break;
	}

	default:
		break;
	}
}

/**************************************************************************
* Explode: 
* @parameters: b2Vec2 _explosionPos
* @return:
***************************************************************************/
void CGameManager::Explode(b2Vec2 _explosionPos)
{
	for (auto player : m_playersInScene)
	{
		if (player)
		{
			float scalar = 20.0f;

			b2Vec2 distance(1 / abs(player->GetBody()->GetPosition().x - _explosionPos.x), 1 / abs(player->GetBody()->GetPosition().y - _explosionPos.y));
			player->Damage(distance.Length() * scalar);
		}
	}
}