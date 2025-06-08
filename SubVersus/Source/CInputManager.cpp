/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2023] Media Design School
File Name : CInputManager.cpp
Description : Implementation for input management class
Authors : Glyn, Brittney
**************************************************************************/

#include "CInputManager.h"
#include "CGameManager.h"
#include "CPlayer.h"

CInputManager::CInputManager()
{
	m_players[0] = nullptr;
	m_players[1] = nullptr;

	m_player1Fired = false;
	m_player2Fired = false;

	m_player1Swapping = false;
	m_player2Swapping = false;

	m_player1LastFired = m_timer.getElapsedTime().asMilliseconds();
	m_player2LastFired = m_timer.getElapsedTime().asMilliseconds();
}

/**************************************************************************
* CInputManager: Giving the input manager access to the player objects
* @parameters: _p1 & _p2 are both pointers to the player objects
* @return:
***************************************************************************/
void CInputManager::InitialiseInputManager(CPlayer* _p1, CPlayer* _p2)
{
	m_players[0] = _p1;
	m_players[1] = _p2;
}

/**************************************************************************
* PollInput: Checking for available connected joysticks, and sending relevant actions to the GameManager depending on the joysticks' state
* @parameters:
* @return:
***************************************************************************/
unsigned int CInputManager::PollInput(GameState _state)
{
	// restart game if possible (start button)
	if (_state == GameState::MatchComplete)
	{
		return sf::Joystick::isButtonPressed(0, 7);
	}

	// needs two controllers to start the game
	unsigned int controllerCount = GetControllerCount();
	if (controllerCount < 2)
	{
		return controllerCount;
	}

	// if on menu, check menu input
	/*if (_state == GameState::Menu)
	{
		return PollMenuInput();
	}*/

	// TODO: check joystick axis counts & button counts, to see if it is a valid joystick

	// move player 1 based on joystick position
	sf::Vector2f p1Move(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X), sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y));
	// account for poor deadzones
	p1Move.x = abs(p1Move.x) > 12.0f ? p1Move.x : 0.0f;
	p1Move.y = abs(p1Move.y) > 12.0f ? p1Move.y : 0.0f;
	m_players[0]->Update(p1Move);

	// rotate player 1
	sf::Vector2f p1Rot(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::U), sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::V));
	// account for poor deadzones
	p1Rot.x = abs(p1Rot.x) > 12.0f ? p1Rot.x : 0.0f;
	p1Rot.y = abs(p1Rot.y) > 12.0f ? p1Rot.y : 0.0f;
	m_players[0]->GetBody()->SetTransform(
		m_players[0]->GetBody()->GetPosition(),
		std::clamp(
			p1Rot.x != 0.0f ? atan(p1Rot.y / p1Rot.x) / 1.5f : m_players[0]->GetBody()->GetAngle(),
			-3.14f, 3.14f
		) // angle * direction
	);
	m_players[0]->SetDirection(p1Rot.x != 0.0f ? (p1Rot.x < 0.0f ? -1 : 1) : 0);

	// fire projectile for player 1 (trigger buttons)
	if (abs(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Z)) > 20.0f)
	{
		int timeMillis = m_timer.getElapsedTime().asMilliseconds();
		if (!m_player1Fired && timeMillis >= m_player1LastFired + m_fireDelayMillis)
		{
			m_player1LastFired = timeMillis;
			m_players[0]->FireProjectile();
			m_player1Fired = true;
		}
	}
	else
	{
		m_player1Fired = false;
	}

	// switch projectile for player 1
	// decrease (left bumper)
	if (sf::Joystick::isButtonPressed(0, 4))
	{
		if (!m_player1Swapping)
		{
			m_player1Swapping = true;
			if (m_players[0]->m_weaponEquipped == WEAPON_EQUIPPED::e_Torpedo) m_players[0]->m_weaponEquipped = WEAPON_EQUIPPED::e_Harpoon;
			else if (m_players[0]->m_weaponEquipped == WEAPON_EQUIPPED::e_Missile) m_players[0]->m_weaponEquipped = WEAPON_EQUIPPED::e_Torpedo;
		}
	}
	// increase (right bumper)
	else if (sf::Joystick::isButtonPressed(0, 5))
	{
		if (!m_player1Swapping)
		{
			m_player1Swapping = true;
			if (m_players[0]->m_weaponEquipped == WEAPON_EQUIPPED::e_Harpoon) m_players[0]->m_weaponEquipped = WEAPON_EQUIPPED::e_Torpedo;
			else if (m_players[0]->m_weaponEquipped == WEAPON_EQUIPPED::e_Torpedo) m_players[0]->m_weaponEquipped = WEAPON_EQUIPPED::e_Missile;
		}
	}
	else
	{
		m_player1Swapping = false;
	}

	// move player 2 based on joystick position
	sf::Vector2f p2Move(sf::Joystick::getAxisPosition(1, sf::Joystick::Axis::X), sf::Joystick::getAxisPosition(1, sf::Joystick::Axis::Y));
	// account for poor deadzones
	p2Move.x = abs(p2Move.x) > 12.0f ? p2Move.x : 0.0f;
	p2Move.y = abs(p2Move.y) > 12.0f ? p2Move.y : 0.0f;
	m_players[1]->Update(p2Move);

	// rotate player 2
	sf::Vector2f p2Rot(sf::Joystick::getAxisPosition(1, sf::Joystick::Axis::U), sf::Joystick::getAxisPosition(1, sf::Joystick::Axis::V));
	// account for poor deadzones
	p2Rot.x = abs(p2Rot.x) > 12.0f ? p2Rot.x : 0.0f;
	p2Rot.y = abs(p2Rot.y) > 12.0f ? p2Rot.y : 0.0f;
	m_players[1]->GetBody()->SetTransform(
		m_players[1]->GetBody()->GetPosition(),
		std::clamp(
			p2Rot.x != 0.0f ? atan(p2Rot.y / p2Rot.x) / 1.5f : m_players[1]->GetBody()->GetAngle(),
			-3.14f, 3.14f
		) // angle * direction
	);
	m_players[1]->SetDirection(p2Rot.x != 0.0f ? (p2Rot.x < 0.0f ? 1 : -1) : 0);

	// fire projectile for player 2 (trigger buttons)
	if (abs(sf::Joystick::getAxisPosition(1, sf::Joystick::Axis::Z)) > 20.0f)
	{
		int timeMillis = m_timer.getElapsedTime().asMilliseconds();
		if (!m_player2Fired && timeMillis >= m_player2LastFired + m_fireDelayMillis)
		{
			m_player2LastFired = timeMillis;
			m_players[1]->FireProjectile();
			m_player2Fired = true;
		}
	}
	else
	{
		m_player2Fired = false;
	}

	// switch projectile for player 2
	// decrease (left bumper)
	if (sf::Joystick::isButtonPressed(1, 4))
	{
		if (!m_player2Swapping)
		{
			m_player2Swapping = true;
			if (m_players[1]->m_weaponEquipped == WEAPON_EQUIPPED::e_Torpedo) m_players[1]->m_weaponEquipped = WEAPON_EQUIPPED::e_Harpoon;
			else if (m_players[1]->m_weaponEquipped == WEAPON_EQUIPPED::e_Missile) m_players[1]->m_weaponEquipped = WEAPON_EQUIPPED::e_Torpedo;
		}
	}
	// increase (right bumper)
	else if (sf::Joystick::isButtonPressed(1, 5))
	{
		if (!m_player2Swapping)
		{
			m_player2Swapping = true;
			if (m_players[1]->m_weaponEquipped == WEAPON_EQUIPPED::e_Harpoon) m_players[1]->m_weaponEquipped = WEAPON_EQUIPPED::e_Torpedo;
			else if (m_players[1]->m_weaponEquipped == WEAPON_EQUIPPED::e_Torpedo) m_players[1]->m_weaponEquipped = WEAPON_EQUIPPED::e_Missile;
		}
	}
	else
	{
		m_player2Swapping = false;
	}

	return GetControllerCount();
}

/**************************************************************************
* PollDebugInput: Using keyboard input to control characters, for testing purposes
* @parameters:
* @return:
***************************************************************************/
unsigned int CInputManager::PollDebugInput(GameState _state)
{
	// restart game if possible
	if (_state == GameState::MatchComplete)
	{
		return sf::Keyboard::isKeyPressed(sf::Keyboard::A) ? 1 : 0;
	}

	// rotate the player 1
	float angleChange = 2.0f / 60.0f;
	if ((int)sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		m_players[0]->GetBody()->SetTransform(m_players[0]->GetBody()->GetPosition(), m_players[0]->GetBody()->GetAngle() - angleChange);
	}
	else if ((int)sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
		m_players[0]->GetBody()->SetTransform(m_players[0]->GetBody()->GetPosition(), m_players[0]->GetBody()->GetAngle() + angleChange);
	}

	// move player 1 based on keyboard input
	m_players[0]->Update(sf::Vector2f(
		(float)sf::Keyboard::isKeyPressed(sf::Keyboard::D) - (float)sf::Keyboard::isKeyPressed(sf::Keyboard::A),
		(float)sf::Keyboard::isKeyPressed(sf::Keyboard::S) - (float)sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	);
	// change/equip different weapon
	if ((int)sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) m_players[0]->m_weaponEquipped = WEAPON_EQUIPPED::e_Harpoon;
	if ((int)sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) m_players[0]->m_weaponEquipped = WEAPON_EQUIPPED::e_Torpedo;
	if ((int)sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) m_players[0]->m_weaponEquipped = WEAPON_EQUIPPED::e_Missile;

	// fire projectile for player 1
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		if (!m_player1Fired)
		{
			m_players[0]->FireProjectile();
			m_player1Fired = true;
		}
	}
	else
	{
		m_player1Fired = false;
	}

	// rotate the player 2
	if ((int)sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
	{
		m_players[1]->GetBody()->SetTransform(m_players[1]->GetBody()->GetPosition(), m_players[1]->GetBody()->GetAngle() - angleChange);
	}
	else if ((int)sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0)) {
		m_players[1]->GetBody()->SetTransform(m_players[1]->GetBody()->GetPosition(), m_players[1]->GetBody()->GetAngle() + angleChange);
	}
	// move player 2 based on keyboard input
	m_players[1]->Update(sf::Vector2f(
		(float)sf::Keyboard::isKeyPressed(sf::Keyboard::Right) - (float)sf::Keyboard::isKeyPressed(sf::Keyboard::Left),
		(float)sf::Keyboard::isKeyPressed(sf::Keyboard::Down) - (float)sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	);
	// change/equip different weapon
	if ((int)sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1)) m_players[1]->m_weaponEquipped = WEAPON_EQUIPPED::e_Harpoon;
	if ((int)sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)) m_players[1]->m_weaponEquipped = WEAPON_EQUIPPED::e_Torpedo;
	if ((int)sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3)) m_players[1]->m_weaponEquipped = WEAPON_EQUIPPED::e_Missile;

	// fire projectile for player 2
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Slash))
	{
		if (!m_player2Fired)
		{
			m_players[1]->FireProjectile();
			m_player2Fired = true;
		}
	}
	else
	{
		m_player2Fired = false;
	}

	return 0;
}

unsigned int CInputManager::PollMenuInput()
{
	if (GetControllerCount() == 2)
	{
		// press A to play game
		if (sf::Joystick::isButtonPressed(0, 0))
		{
			return 1; // play game
		}
	}
	// press B to quit game
	if (sf::Joystick::isButtonPressed(0, 1))
	{
		return 2; // quit game
	}

	return 0; // do nothing
}

/**************************************************************************
* GetControllerCount: Returns amount of connected controllers ranging from 0-2
* @parameters:
* @return: amount of connected controllers
***************************************************************************/
unsigned int CInputManager::GetControllerCount()
{
	return !sf::Joystick::isConnected(0) ? 0 : !sf::Joystick::isConnected(1) ? 1 : 2;
}