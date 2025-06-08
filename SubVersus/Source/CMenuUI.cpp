/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2023] Media Design School
File Name : CMenuUI.cpp
Description : Implementation for menu user interface
Authors : Glyn Fleming-Bone
**************************************************************************/

#include "CMenuUI.h"
#include "CTextureManager.h"

/**************************************************************************
* CMenuUI: Constructor; set necessary objects
* @parameters:
* @return:
***************************************************************************/
CMenuUI::CMenuUI()
{
}

/**************************************************************************
* CreateUISprites: Generate SFML sprites to render menu
* @parameters:
* @return:
***************************************************************************/
void CMenuUI::CreateUISprites()
{
	sf::Font* font = CTextureManager::GetInstance()->GetStylizedFont();

	m_menuBackground = sf::RectangleShape(sf::Vector2f(340.0f, 340.0f));
	m_menuBackground.setPosition(sf::Vector2f(230.0f, 335.0f));
	m_menuBackground.setFillColor(sf::Color(0, 0, 0, 125));

	m_title = sf::Text("SUBVERSUS", *font, 50);
	// centering text
	sf::FloatRect textRect = m_title.getLocalBounds();
	m_title.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	m_title.setPosition(sf::Vector2f(400.0f, 200.0f));

	m_startButtonLabel = sf::Text("Play (A)", *font);
	m_startButtonLabel.setPosition(sf::Vector2f(345.0f, 450.0f));

	m_quitButtonLabel = sf::Text("Quit (B)", *font);
	m_quitButtonLabel.setPosition(sf::Vector2f(345.0f, 500.0f));

	m_controlsText = sf::Text("Controls:\nLeft stick: Move\nRight stick: Rotate\nLT/RT: Fire projectile\nLB/RB: Change projectile", *font, 15);
	// centering text
	textRect = m_controlsText.getLocalBounds();
	m_controlsText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	m_controlsText.setPosition(sf::Vector2f(400.0f, 600.0f));

	m_controller1Icon.setPosition(sf::Vector2f(240.0f, 330.0f));
	m_controller1Icon.setScale(0.15f, 0.15f);
	m_controller1Icon.setTexture(*CTextureManager::GetInstance()->GetNoControllerTexture());

	m_controller2Icon.setPosition(sf::Vector2f(420.0f, 330.0f));
	m_controller2Icon.setScale(0.15f, 0.15f);
	m_controller2Icon.setTexture(*CTextureManager::GetInstance()->GetNoControllerTexture());
}

/**************************************************************************
* DrawMenu: Draws menu sprites to the SFML window
* @parameters: the SFML window to draw to, and amount of controllers connected
* @return:
***************************************************************************/
void CMenuUI::DrawMenu(sf::RenderWindow& _window, int _controllers)
{
	_controllers >= 1 ? m_controller1Icon.setTexture(*CTextureManager::GetInstance()->GetFoundControllerTexture()) : m_controller1Icon.setTexture(*CTextureManager::GetInstance()->GetNoControllerTexture());
	_controllers >= 2 ? m_controller2Icon.setTexture(*CTextureManager::GetInstance()->GetFoundControllerTexture()) : m_controller2Icon.setTexture(*CTextureManager::GetInstance()->GetNoControllerTexture());

	_window.draw(m_title);
	_window.draw(m_menuBackground);
	_window.draw(m_startButtonLabel);
	_window.draw(m_quitButtonLabel);
	_window.draw(m_controller1Icon);
	_window.draw(m_controller2Icon);
	_window.draw(m_controlsText);
}