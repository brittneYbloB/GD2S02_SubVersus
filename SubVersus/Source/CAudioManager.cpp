/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2023] Media Design School
File Name : CAudioManager.cpp
Description : Cpp file for audio
Authors : Luke Van Zuilen, Manu Easton
**************************************************************************/

#include "CAudioManager.h"

CAudioManager* CAudioManager::m_pInstance = nullptr;

/**************************************************************************
* CAudioManager: Constructor for audio manager 
* @parameters:
* @return:
***************************************************************************/
CAudioManager::CAudioManager()
{
	LoadAllSoundFiles();
}

/**************************************************************************
* LoadAllSoundFiles: Creates AudioClip object for every sound needed in the game
* @parameters:
* @return:
***************************************************************************/
void CAudioManager::LoadAllSoundFiles()
{
	// Load Sound Effects
	auto projectileFireSound = std::make_shared<AudioClip>("ProjectileFire");
	m_soundEffects.push_back(projectileFireSound);

	auto projectileHitSound = std::make_shared<AudioClip>("ProjectileHit");
	m_soundEffects.push_back(projectileHitSound);

	auto shipDamageSound = std::make_shared<AudioClip>("ShipDamage");
	m_soundEffects.push_back(shipDamageSound);

	auto shipDestroyedSound = std::make_shared<AudioClip>("ShipDestroyed");
	m_soundEffects.push_back(shipDestroyedSound);

	auto shipMoveSound = std::make_shared<AudioClip>("ShipMove");
	m_soundEffects.push_back(shipMoveSound);

	auto stalactiteHitSound = std::make_shared<AudioClip>("StalactiteHit");
	m_soundEffects.push_back(stalactiteHitSound);

	auto navalMineHitSound = std::make_shared<AudioClip>("NavalMineHit");
	m_soundEffects.push_back(navalMineHitSound);

	auto pickupSound = std::make_shared<AudioClip>("Pickup");
	m_soundEffects.push_back(pickupSound);

	auto failedToFireSound = std::make_shared<AudioClip>("FailedToFire");
	m_soundEffects.push_back(failedToFireSound);

	// Load Music
	auto menuMusic = std::make_shared<AudioClip>("underwater_ambient", true);
	m_music.push_back(menuMusic);

	auto fightMusic = std::make_shared<AudioClip>("ActionMusic_David_Fesliyan", true);
	m_music.push_back(fightMusic);
}

/**************************************************************************
* GetInstance: Instantiates an instance of the audio manager if it does not
*	exist, otherwise returns existing instance: Singleton class
* @parameters:
* @return:
***************************************************************************/
CAudioManager* CAudioManager::GetInstance()
{
    if(m_pInstance == nullptr)
	{
		m_pInstance = new CAudioManager();
	}
    return m_pInstance;
}

/**************************************************************************
* PlaySound: Plays a sound effect
* @parameters: string, name of sound
* @return:
***************************************************************************/
void CAudioManager::PlaySound(std::string _audioName)
{
	AudioClip* soundEffect = nullptr;

	for (auto audio : m_soundEffects)
	{
		if (audio->name == _audioName)
		{
			soundEffect = audio.get();
			break;
		}
	}

	if (soundEffect == nullptr)
	{
		std::cout << "Sound " << _audioName << " does not exist" << std::endl;
		return;
	}

	soundEffect->sound.play();
}

/**************************************************************************
* PlayMusic: Plays background music
* @parameters: string, required music
* @return:
***************************************************************************/
void CAudioManager::PlayMusic(std::string _musicName)
{
	AudioClip* music = nullptr;

	for (auto audio : m_music)
	{
		if (audio->name == _musicName)
		{
			music = audio.get();
			break;
		}
		else
		{
			// Stop all other music playing
			audio->sound.stop();
		}
	}

	if (music == nullptr)
	{
		std::cout << "Sound " << _musicName << " does not exist" << std::endl;
		return;
	}

	music->sound.play();
}