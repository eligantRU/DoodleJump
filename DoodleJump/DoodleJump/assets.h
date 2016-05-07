#pragma once

#include "stdafx.h"

struct Assets
{
public:
	Assets();
	~Assets();
	void addTexture(sf::Texture & texture, std::string string);
	void addRepeatedTexture(sf::Texture & texture, std::string string);
	void addFont(sf::Font & font, std::string string); 
	void addImage(sf::Image & image, std::string string);
	void addSound(sf::SoundBuffer & buffer, std::string string);
	void playSound(sf::SoundBuffer & buffer);
	void pauseSound();
	void removeSoundFromPause();

	sf::Image WINDOW_ICON;
	sf::Texture BACKGROUND_TEXTURE;
	sf::Texture PLATE_STATIC_TEXTURE;
	sf::Texture PLATE_DYNAMIC_TEXTURE;
	sf::Texture PLATE_CLOUD_TEXTURE;
	sf::Texture PLATE_UNSTABLE_TEXTURE;
	sf::Texture SPRING_TEXTURE;
	sf::Texture SPRING_2_TEXTURE;
	sf::Texture DOODLE_LEFT_TEXTURE;
	sf::Texture DOODLE_RIGHT_TEXTURE;
	sf::Texture DOODLE_JUMP_LEFT_TEXTURE;
	sf::Texture DOODLE_JUMP_RIGHT_TEXTURE;
	sf::Texture DOODLE_SHOOTING_TEXTURE;
	sf::Texture HAT_HELOCPTER_DIAGONAL_RIGHT_TEXTURE;
	sf::Texture HAT_HELOCPTER_DIAGONAL_LEFT_TEXTURE;
	sf::Texture HAT_HELOCPTER_FLY_RIGHT_TEXTURE;
	sf::Texture HAT_HELOCPTER_FLY_LEFT_TEXTURE;
	sf::Texture HAT_HELOCPTER_NONE_RIGHT_TEXTURE;
	sf::Texture HAT_HELOCPTER_NONE_LEFT_TEXTURE;
	sf::Texture ROCKET_NONE_TEXTURE;
	sf::Texture ROCKET_0_LEFT_TEXTURE;
	sf::Texture ROCKET_0_RIGHT_TEXTURE;
	sf::Texture ROCKET_1_LEFT_TEXTURE;
	sf::Texture ROCKET_1_RIGHT_TEXTURE;
	sf::Texture ROCKET_2_LEFT_TEXTURE;
	sf::Texture ROCKET_2_RIGHT_TEXTURE;
	sf::Texture ROCKET_3_LEFT_TEXTURE;
	sf::Texture ROCKET_3_RIGHT_TEXTURE;
	sf::Texture TRAMPOLINE_TEXTURE;
	sf::Texture PLATE_BROKEN_LEFT_TEXTURE;
	sf::Texture PLATE_BROKEN_RIGHT_TEXTURE;
	sf::Texture MAIN_TITLE_TEXTURE;
	sf::Texture GAME_OVER_TITLE_TEXTURE;
	sf::Texture STARS_1_TEXTURE;
	sf::Texture STARS_2_TEXTURE;
	sf::Texture BUTTON_ACTIVE_TEXTURE;
	sf::Texture BUTTON_INACTIVE_TEXTURE;
	sf::Texture HOLE_TEXTURE;
	sf::Texture GARBAGE_1_TEXTURE;
	sf::Texture GARBAGE_2_TEXTURE;
	sf::Texture GARBAGE_3_TEXTURE;
	sf::Texture GARBAGE_4_TEXTURE;
	sf::Texture GARBAGE_5_TEXTURE;
	sf::Texture LINE_TEXTURE;
	sf::Texture MONSTER_FLYING_1_TEXTURE;
	sf::Texture MONSTER_FLYING_2_TEXTURE;
	sf::Texture MONSTER_FLYING_3_TEXTURE;
	sf::Texture MONSTER_FLYING_4_TEXTURE;
	sf::Texture MONSTER_RED_TEXTURE;
	sf::Texture MONSTER_PURPLE_TEXTURE;
	sf::Texture MONSTER_GREEN_TEXTURE;
	sf::Texture MONSTER_BLUE_LEFT_TEXTURE;
	sf::Texture MONSTER_BLUE_RIGHT_TEXTURE;
	sf::Texture BUTTON_A_TEXTURE;
	sf::Texture BUTTON_D_TEXTURE;

	sf::Font ARIAL_FONT;

	sf::SoundBuffer HAT_HELICOPTER_SOUND;
	sf::SoundBuffer ROCKET_SOUND;
	sf::SoundBuffer TRAMPOLINE_SOUND;
	sf::SoundBuffer SPRING_SOUND;
	sf::SoundBuffer GAME_OVER_SOUND;
	sf::SoundBuffer HOLE_SOUND;
	sf::SoundBuffer JUMP_SOUND;
	sf::SoundBuffer PLATE_GHOST_SOUND;

private:
	sf::Sound m_actualSound;
};