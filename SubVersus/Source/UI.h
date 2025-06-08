/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2023] Media Design School
File Name : UI.h
Description : Header for game user interface
Authors : Brittney Smith
**************************************************************************/

#pragma once
#include "CDrawableObject.h"
#include "CPlayer.h"

struct Icons {
	sf::Texture s_eHarpoonTex;
	sf::Texture s_ueHarpoonTex;
	sf::Texture s_eTorpedoTex;
	sf::Texture s_ueTorpedoTex;
	sf::Texture s_eMissileTex;
	sf::Texture s_ueMissileTex;

	sf::Sprite s_eHarpoonIcon_1;
	sf::Sprite s_ueHarpoonIcon_1;
	sf::Sprite s_eTorpedoIcon_1;
	sf::Sprite s_ueTorpedoIcon_1;
	sf::Sprite s_eMissileIcon_1;
	sf::Sprite s_ueMissileIcon_1;

	sf::Sprite s_eHarpoonIcon_2;
	sf::Sprite s_ueHarpoonIcon_2;
	sf::Sprite s_eTorpedoIcon_2;
	sf::Sprite s_ueTorpedoIcon_2;
	sf::Sprite s_eMissileIcon_2;
	sf::Sprite s_ueMissileIcon_2;

	void SetSprites();
	void SetPositions(float _offset);
};

class UI
	: public CDrawableObject
{
private:
	sf::Font* m_fontHUD;
	sf::Text m_textHUD;

public:
	UI();
	~UI() {};

	std::vector<CPlayer*> m_activePlayers;
	std::vector<sf::Sprite> m_playerHealth;

	// end screen parameters
	sf::RectangleShape m_endScreenBg;
	sf::Text m_endScreen1Txt;
	sf::Text m_endScreen2Txt;

	sf::RectangleShape m_healthBar;

	Icons m_iconManager;

	// view offset - for moving camera
	float m_offset = 0.0f;

	void CreateUISprites();
	void UpdateUI(sf::RenderWindow& _window);

	void DrawPlayerHealth(sf::RenderWindow& _window);
	void DrawPlayerLives(sf::RenderWindow& _window);
	void DrawWeaponIcons(sf::RenderWindow& _window);
	void DrawAmmoCounts(sf::RenderWindow& _window);

	void DrawEndScreen(sf::RenderWindow& _window, unsigned int _winner);
};