/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2023] Media Design School
File Name : UI.cpp
Description : Implementation for game user interface
Authors : Brittney Smith
**************************************************************************/

#define WINDOW_HEIGHT 800;
#define WINDOW_WIDTH 800

#include "UI.h"

/**************************************************************************
* UI: Constructor; set lives texture
* @parameters:
* @return:
***************************************************************************/
UI::UI()
{
	// Set icon sprites
	m_iconManager.SetSprites();

	// Load font
	m_fontHUD = CTextureManager::GetInstance()->GetStylizedFont();
	m_textHUD.setFont(*m_fontHUD);
	m_textHUD.setCharacterSize(30);
	m_textHUD.setFillColor(sf::Color::White);
	m_textHUD.setOrigin(0.0f, 20.0f);

	m_healthBar.setFillColor(sf::Color::Green);
}

/**************************************************************************
* CreateUISprites: Create sprites needed for UI
* @parameters:
* @return:
***************************************************************************/
void UI::CreateUISprites()
{
	SetSize(sf::Vector2f(6.0f, 5.0f));

	// Heart icon
	CreateSprite(CTextureManager::GetInstance()->GetLivesTexture());

	// initialize end screen objects
	m_endScreen1Txt = sf::Text("", *CTextureManager::GetInstance()->GetFont());
	m_endScreen2Txt = sf::Text("", *CTextureManager::GetInstance()->GetFont());
	m_endScreenBg = sf::RectangleShape(sf::Vector2f(2000.0f, 2000.0f));
	m_endScreenBg.setFillColor(sf::Color(25, 25, 25, 125));
}


/**************************************************************************
* Update: Update gameplay UI
* @parameters: window to render to
* @return:
***************************************************************************/
void UI::UpdateUI(sf::RenderWindow& _window)
{
	m_offset = _window.getView().getCenter().x - _window.getView().getSize().x / 2.0f;

	DrawPlayerHealth(_window);
	DrawPlayerLives(_window);
	DrawWeaponIcons(_window);
	DrawAmmoCounts(_window);
}

/**************************************************************************
* DrawPlayerHealth: Draw health bar for each player in either corner of window
* @parameters: rendering window
* @return:
***************************************************************************/
void UI::DrawPlayerHealth(sf::RenderWindow& _window)
{
	int offset = 675;

	// Get players
	for (unsigned int i = 0; i < m_activePlayers.size(); i++)
	{
		// set origin?
		m_healthBar.setSize(sf::Vector2f((float)m_activePlayers[i]->m_health, 30.0f));
		m_healthBar.setPosition(sf::Vector2f(i * offset + 10.0f + m_offset, 60.0f));
		_window.draw(m_healthBar);
	}
}

/**************************************************************************
* DrawPlayerLives: Draw lives for each player in either corner of window
* @parameters: rendering window
* @return:
***************************************************************************/
void UI::DrawPlayerLives(sf::RenderWindow& _window)
{
	int offset = 700;

	// Get players
	for (unsigned int i = 0; i < m_activePlayers.size(); i++)
	{ 
		// For each life this player has...
		for (int iterHealth = 0; iterHealth < m_activePlayers[i]->m_lives; iterHealth++)
		{
			// Draw
			m_sprite.setPosition(sf::Vector2f(iterHealth * 25 + (i * offset) + m_offset, 10.0f));
			_window.draw(m_sprite);
		}
	}
}


/**************************************************************************
* DrawWeaponIcons: Update and draw weapon icons
* @parameters: rendering window
* @return:
***************************************************************************/
void UI::DrawWeaponIcons(sf::RenderWindow& _window)
{
	CPlayer* player1 = (CPlayer*)m_activePlayers[0];
	CPlayer* player2 = (CPlayer*)m_activePlayers[1];

	m_iconManager.SetPositions(m_offset);

	// First player's weapon icons
	switch (player1->m_weaponEquipped)
	{
		case WEAPON_EQUIPPED::e_Harpoon:
		{
			_window.draw(m_iconManager.s_eHarpoonIcon_1);
			_window.draw(m_iconManager.s_ueTorpedoIcon_1);
			_window.draw(m_iconManager.s_ueMissileIcon_1);
			break;
		}
		case WEAPON_EQUIPPED::e_Missile:
		{
			_window.draw(m_iconManager.s_eMissileIcon_1);
			_window.draw(m_iconManager.s_ueTorpedoIcon_1);
			_window.draw(m_iconManager.s_ueHarpoonIcon_1);
			break;
		}
		case WEAPON_EQUIPPED::e_Torpedo:
		{
			_window.draw(m_iconManager.s_ueHarpoonIcon_1);
			_window.draw(m_iconManager.s_ueMissileIcon_1);
			_window.draw(m_iconManager.s_eTorpedoIcon_1);
			break;
		}
	}

	// Second player's weapon icons
	switch (player2->m_weaponEquipped)
	{
		case WEAPON_EQUIPPED::e_Harpoon:
		{
			_window.draw(m_iconManager.s_eHarpoonIcon_2);
			_window.draw(m_iconManager.s_ueTorpedoIcon_2);
			_window.draw(m_iconManager.s_ueMissileIcon_2);
			break;
		}
		case WEAPON_EQUIPPED::e_Missile:
		{
			_window.draw(m_iconManager.s_eMissileIcon_2);
			_window.draw(m_iconManager.s_ueHarpoonIcon_2);
			_window.draw(m_iconManager.s_ueTorpedoIcon_2);
			break;
		}
		case WEAPON_EQUIPPED::e_Torpedo:
		{
			_window.draw(m_iconManager.s_ueHarpoonIcon_2);
			_window.draw(m_iconManager.s_ueMissileIcon_2);
			_window.draw(m_iconManager.s_eTorpedoIcon_2);
			break;
		}
	}
}


/**************************************************************************
* DrawEndScreen: Display match results
* @parameters: rendering window, winner (int ID)
* @return:
***************************************************************************/
void UI::DrawEndScreen(sf::RenderWindow& _window, unsigned int _winner)
{
	m_endScreenBg.setPosition(sf::Vector2f(m_offset, 0.0f));
	_window.draw(m_endScreenBg);

	m_endScreen1Txt.setString("Player " + std::to_string(_winner) + " wins!");
	// centering text
	sf::FloatRect textRect = m_endScreen1Txt.getLocalBounds();
	m_endScreen1Txt.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	m_endScreen1Txt.setPosition(sf::Vector2f(400.0f + m_offset, 380.0f));
	_window.draw(m_endScreen1Txt);

	m_endScreen2Txt.setString("Press the Start button to restart...");
	// centering text
	textRect = m_endScreen2Txt.getLocalBounds();
	m_endScreen2Txt.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	m_endScreen2Txt.setPosition(sf::Vector2f(400.0f + m_offset, 430.0f));
	_window.draw(m_endScreen2Txt);
}



/**************************************************************************
* DrawAmmoCounts: Display ammo count for both players
* @parameters:
* @return:
***************************************************************************/
void UI::DrawAmmoCounts(sf::RenderWindow& _window)
{
	// Set position of ammo counts on screen
	sf::Vector2f player1AmmoCount = sf::Vector2f(570.0f, 25.0f);
	sf::Vector2f player2AmmoCount = sf::Vector2f(100.0f, 25.0f);

	// Player 1 ammo count
	m_textHUD.setString("gunpowder: " + std::to_string(m_activePlayers[0]->m_universalAmmo));
	m_textHUD.setPosition(WINDOW_WIDTH - player1AmmoCount.x + 40 + m_offset, player1AmmoCount.y);
	m_textHUD.setOrigin(m_textHUD.getLocalBounds().width, 15.0f);
	m_textHUD.setScale(sf::Vector2f(0.75f, 0.75f));
	// Draw
	_window.draw(m_textHUD);

	// Player 2 ammo count
	m_textHUD.setString("gunpowder: " + std::to_string(m_activePlayers[1]->m_universalAmmo));
	m_textHUD.setPosition(WINDOW_WIDTH - player2AmmoCount.x + m_offset, player2AmmoCount.y);
	m_textHUD.setOrigin(m_textHUD.getLocalBounds().width, 15.0f);
	// Draw
	_window.draw(m_textHUD);

	/*
		Display the amount of projectiles the player can fire for each weapon type, 
		based on their ammo amount
	*/

	// P1 harpoon
	m_textHUD.setString("x" + std::to_string(m_activePlayers[0]->m_universalAmmo / 2));
	m_textHUD.setPosition(sf::Vector2f(50.0f + m_offset, 710.0f));
	m_textHUD.setOrigin(m_textHUD.getLocalBounds().width, 15.0f);
	m_textHUD.setScale(sf::Vector2f(0.75f, 0.75f));
	// Draw
	_window.draw(m_textHUD);
	// P1 torpedo
	m_textHUD.setString("x" + std::to_string(m_activePlayers[0]->m_universalAmmo));
	m_textHUD.setPosition(sf::Vector2f(125.0f + m_offset, 710.0f));
	m_textHUD.setOrigin(m_textHUD.getLocalBounds().width, 15.0f);
	// Draw
	_window.draw(m_textHUD);
	// P1 missile
	m_textHUD.setString("x" + std::to_string(m_activePlayers[0]->m_universalAmmo / 4));
	m_textHUD.setPosition(sf::Vector2f(200.0f + m_offset, 710.0f));
	m_textHUD.setOrigin(m_textHUD.getLocalBounds().width, 15.0f);
	// Draw
	_window.draw(m_textHUD);


	// P2 harpoon
	m_textHUD.setString("x" + std::to_string(m_activePlayers[1]->m_universalAmmo / 2));
	m_textHUD.setPosition(sf::Vector2f(625.0f + m_offset, 710.0f));
	m_textHUD.setOrigin(m_textHUD.getLocalBounds().width, 15.0f);
	m_textHUD.setScale(sf::Vector2f(0.75f, 0.75f));
	// Draw
	_window.draw(m_textHUD);
	// P2 torpedo
	m_textHUD.setString("x" + std::to_string(m_activePlayers[1]->m_universalAmmo));
	m_textHUD.setPosition(sf::Vector2f(700.0f + m_offset, 710.0f));
	m_textHUD.setOrigin(m_textHUD.getLocalBounds().width, 15.0f);
	// Draw
	_window.draw(m_textHUD);
	// P2 missile
	m_textHUD.setString("x" + std::to_string(m_activePlayers[1]->m_universalAmmo / 4));
	m_textHUD.setPosition(sf::Vector2f(775.0f + m_offset, 710.0f));
	m_textHUD.setOrigin(m_textHUD.getLocalBounds().width, 15.0f);
	// Draw
	_window.draw(m_textHUD);


	m_textHUD.setScale(sf::Vector2f(0.75f, 0.75f));
}


/**************************************************************************
* SetSprites: Load icon textures and set sprites
* @parameters:
* @return:
***************************************************************************/
void Icons::SetSprites()
{
	// Load textures
	s_eHarpoonTex.loadFromFile("./Sprites/HarpoonIcon_Equipped.png");
	s_ueHarpoonTex.loadFromFile("./Sprites/HarpoonIcon_NotEquipped.png");
	s_eTorpedoTex.loadFromFile("./Sprites/TorpedoIcon_Equipped.png");
	s_ueTorpedoTex.loadFromFile("./Sprites/TorpedoIcon_NotEquipped.png");
	s_eMissileTex.loadFromFile("./Sprites/MissileIcon_Equipped.png");
	s_ueMissileTex.loadFromFile("./Sprites/MissileIcon_NotEquipped.png");

	// Set sprites' textures
	s_eHarpoonIcon_1.setTexture(s_eHarpoonTex);
	s_ueHarpoonIcon_1.setTexture(s_ueHarpoonTex);
	s_eTorpedoIcon_1.setTexture(s_eTorpedoTex);
	s_ueTorpedoIcon_1.setTexture(s_ueTorpedoTex);
	s_eMissileIcon_1.setTexture(s_eMissileTex);
	s_ueMissileIcon_1.setTexture(s_ueMissileTex);

	s_eHarpoonIcon_2.setTexture(s_eHarpoonTex);
	s_ueHarpoonIcon_2.setTexture(s_ueHarpoonTex);
	s_eTorpedoIcon_2.setTexture(s_eTorpedoTex);
	s_ueTorpedoIcon_2.setTexture(s_ueTorpedoTex);
	s_eMissileIcon_2.setTexture(s_eMissileTex);
	s_ueMissileIcon_2.setTexture(s_ueMissileTex);

	SetPositions(0.0f);
}

void Icons::SetPositions(float _offset)
{
	// Set position on screen
	s_eHarpoonIcon_1.setPosition(sf::Vector2f(25.0f + _offset, 725.0f));
	s_ueHarpoonIcon_1.setPosition(sf::Vector2f(25.0f + _offset, 725.0f));
	s_eTorpedoIcon_1.setPosition(sf::Vector2f(100.0f + _offset, 725.0f));
	s_ueTorpedoIcon_1.setPosition(sf::Vector2f(100.0f + _offset, 725.0f));
	s_eMissileIcon_1.setPosition(sf::Vector2f(175.0f + _offset, 725.0f));
	s_ueMissileIcon_1.setPosition(sf::Vector2f(175.0f + _offset, 725.0f));

	s_eHarpoonIcon_2.setPosition(sf::Vector2f(575.0f + _offset, 725.0f));
	s_ueHarpoonIcon_2.setPosition(sf::Vector2f(575.0f + _offset, 725.0f));
	s_eTorpedoIcon_2.setPosition(sf::Vector2f(650.0f + _offset, 725.0f));
	s_ueTorpedoIcon_2.setPosition(sf::Vector2f(650.0f + _offset, 725.0f));
	s_eMissileIcon_2.setPosition(sf::Vector2f(725.0f + _offset, 725.0f));
	s_ueMissileIcon_2.setPosition(sf::Vector2f(725.0f + _offset, 725.0f));
}