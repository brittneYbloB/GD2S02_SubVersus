/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2023] Media Design School
File Name : CInputManager.h
Description : Header file for input management class
Authors : Glyn
**************************************************************************/

#pragma once
// Library
#include "SFML/Graphics.hpp"
// Classes
#include "CPlayer.h"

enum class GameState
{
	Menu,
	Playing,
	MatchComplete,
};

class CInputManager
{
private:
	CPlayer* m_players[2];

	bool m_player1Fired;
	bool m_player2Fired;

	bool m_player1Swapping;
	bool m_player2Swapping;

	int m_fireDelayMillis = 150;
	int m_player1LastFired;
	int m_player2LastFired;

	sf::Clock m_timer;
public:
	// Functions
	CInputManager();
	void InitialiseInputManager(CPlayer* _p1, CPlayer* _p2);
	virtual ~CInputManager() {};

	unsigned int PollInput(GameState _state);
	unsigned int PollDebugInput(GameState _state);
	unsigned int PollMenuInput();

	unsigned int GetControllerCount();
};