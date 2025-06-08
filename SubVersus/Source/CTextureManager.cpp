/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2023] Media Design School
File Name : CTextureManager.cpp
Description : Implementation for texture manager class
Authors : Glyn, Brittney
**************************************************************************/

#include "CTextureManager.h"
#include <iostream>

CTextureManager* CTextureManager::m_instance = nullptr;

/**************************************************************************
* GetInstance: Singleton implementation for texture manager
* @parameters:
* @return:
***************************************************************************/
CTextureManager* CTextureManager::GetInstance()
{
    if (m_instance == nullptr)
    {
        m_instance = new CTextureManager();
    }
    return m_instance;
}

/**************************************************************************
* CTextureManager: Constructor; set up all textures for game
* @parameters:
* @return:
***************************************************************************/
CTextureManager::CTextureManager()
{
    if (!m_font.loadFromFile("C:/Windows/Fonts/arial.ttf"))
    {
        std::cout << "Error loading font!" << std::endl;
    }
    if (!m_stylizedFont.loadFromFile("Font/Spaceton.otf"))
    {
        std::cout << "Error loading font!" << std::endl;
    }

    m_playerOneTex.loadFromFile("./Sprites/spaceRockets_001.png");
    m_playerTwoTex.loadFromFile("./Sprites/spaceRockets_003.png");
    m_stalactiteTex.loadFromFile("./Sprites/rockIceDown.png");
    m_navalMineTex.loadFromFile("./Sprites/mine.png");
    m_healthTex.loadFromFile("./Sprites/healthResource.png");
    m_oxygenTex.loadFromFile("./Sprites/chick.png");
    m_ammunitionTex.loadFromFile("./Sprites/ammoResource.png");
    m_harpoonTex.loadFromFile("./Sprites/Harpoon.png");
    m_missileTex.loadFromFile("./Sprites/Missile.png");
    m_torpedoTex.loadFromFile("./Sprites/Torpedo.png");
    m_playerLivesTex.loadFromFile("./Sprites/bluePixelHeart.png");
    m_noControllerTex.loadFromFile("./Sprites/gamepad_solid.png");
    m_foundControllerTex.loadFromFile("./Sprites/gamepad_green.png");
}