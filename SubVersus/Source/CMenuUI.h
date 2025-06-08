/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2023] Media Design School
File Name : CMenuUI.h
Description : Header for menu user interface
Authors : Glyn Fleming-Bone
**************************************************************************/

#pragma once
#include "CDrawableObject.h"
#include "CPlayer.h"

class CMenuUI
	: public CDrawableObject
{
public:
	CMenuUI();
	~CMenuUI() {};

	void CreateUISprites();
	void DrawMenu(sf::RenderWindow& _window, int _controllers);
private:
	sf::RectangleShape m_menuBackground;
	sf::Text m_title;
	sf::Text m_startButtonLabel;
	sf::Text m_quitButtonLabel;
	sf::Text m_controlsText;
	sf::Sprite m_controller1Icon;
	sf::Sprite m_controller2Icon;
};