/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2023] Media Design School
File Name : CAudioManager.h
Description : Header file for audio manager, singleton class
Authors : Luke Van Zuilen, Manu Easton
**************************************************************************/

#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "SFML/Audio.hpp"

struct AudioClip
{
	std::string name;
	bool isMusic;
	sf::SoundBuffer buffer;
	sf::Sound sound;

	AudioClip(std::string _name, bool _isMusic = false)
	{
		name = _name;
		isMusic = _isMusic;

		std::string fileLocation = "Sounds/Effects/";
		if (isMusic)
		{
			fileLocation = "Sounds/Music/";
			sound.setLoop(true);
		}

		if (!buffer.loadFromFile(fileLocation + _name + ".wav"))
		{
			std::cout << "Failed to find sound: " << _name << std::endl;
			buffer.loadFromFile("Sounds/Effects/Failed.wav");
		}
		sound.setBuffer(buffer);
	}
};

class CAudioManager
{
public:
	//singleton instance
	static CAudioManager* GetInstance();		

	void PlaySound(std::string _audioName);
	
	void PlayMusic(std::string _musicName);

private:
	CAudioManager();

	void LoadAllSoundFiles();

	//singleton instance
	static CAudioManager* m_pInstance;
	
	// Audio clips
	std::vector<std::shared_ptr<AudioClip>> m_soundEffects;
	std::vector<std::shared_ptr<AudioClip>> m_music;
};