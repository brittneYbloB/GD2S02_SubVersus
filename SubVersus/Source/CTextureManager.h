/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2023] Media Design School
File Name : CTextureManager.h
Description : Header for texture management class
Authors : Glyn Fleming-Bone, Brittney Smith
**************************************************************************/

#pragma once
#include "SFML/Graphics.hpp"

class CTextureManager
{
private:
	// singleton
	static CTextureManager* m_instance;
	CTextureManager();

	// Player textures
	sf::Texture m_playerOneTex;
	sf::Texture m_playerTwoTex;
	// Environmental Hazard textures
	sf::Texture m_stalactiteTex;
	sf::Texture m_navalMineTex;
	// Resource textures
	sf::Texture m_healthTex;
	sf::Texture m_oxygenTex;
	sf::Texture m_ammunitionTex;
	// Projectile textures
	sf::Texture m_harpoonTex;
	sf::Texture m_missileTex;
	sf::Texture m_torpedoTex;

	// UI
	sf::Texture m_playerLivesTex;
	sf::Font m_font;
	sf::Font m_stylizedFont;
	// Menu textures
	sf::Texture m_noControllerTex;
	sf::Texture m_foundControllerTex;

public:
	static CTextureManager* GetInstance();

	~CTextureManager() {};

	// Getters
	sf::Texture* GetPlayerOneTexture() { return &m_playerOneTex; };
	sf::Texture* GetPlayerTwoTexture() { return &m_playerTwoTex; };
	sf::Texture* GetStalactiteTexture() { return &m_stalactiteTex; };
	sf::Texture* GetNavalMineTexture() { return &m_navalMineTex; };
	sf::Texture* GetHealthResTexture() { return &m_healthTex; };
	sf::Texture* GetOxygenResTexture() { return &m_oxygenTex; };
	sf::Texture* GetAmmoResTexture() { return &m_ammunitionTex; };
	sf::Texture* GetHarpoonTexture() { return &m_harpoonTex; };
	sf::Texture* GetMissileTexture() { return &m_missileTex; };
	sf::Texture* GetTorpedoTexture() { return &m_torpedoTex; };
	sf::Texture* GetLivesTexture() { return &m_playerLivesTex; };
	sf::Texture* GetNoControllerTexture() { return &m_noControllerTex; };
	sf::Texture* GetFoundControllerTexture() { return &m_foundControllerTex; };

	sf::Font* GetFont() { return &m_font; };
	sf::Font* GetStylizedFont() { return &m_stylizedFont; };
};