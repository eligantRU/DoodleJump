#include "stdafx.h"
#include "bases.h"
#include "Bonuses.cpp"
#include "Plates.cpp"
#include "Doodle.cpp"
#include "Game.cpp"

int main(void)
{   
	// это убожество в отдельную функцию неплохо бы забить молотом Тора
	if (!DOODLE_LEFT_TEXTURE.loadFromFile("images/Doodle45_45Left.png"))
	{
		printf("Error loaded file");
	}
	DOODLE_LEFT_TEXTURE.setSmooth(true);

	if (!DOODLE_RIGHT_TEXTURE.loadFromFile("images/Doodle45_45Right.png"))
	{
		printf("Error loaded file");
	}
	DOODLE_RIGHT_TEXTURE.setSmooth(true);
	
	if (!DOODLE_JUMP_LEFT_TEXTURE.loadFromFile("images/Doodle45_42Left_Jump.png"))
	{
		printf("Error loaded file");
	}
	DOODLE_JUMP_LEFT_TEXTURE.setSmooth(true);

	if (!DOODLE_JUMP_RIGHT_TEXTURE.loadFromFile("images/Doodle45_42Right_Jump.png"))
	{
		printf("Error loaded file");
	}
	DOODLE_JUMP_RIGHT_TEXTURE.setSmooth(true);
	
	if (!PLATE_STATIC_TEXTURE.loadFromFile("images/Plate_63_15_Green.png"))
	{
		printf("Error loaded file");
	}
	PLATE_STATIC_TEXTURE.setSmooth(true);

	if (!PLATE_DYNAMIC_TEXTURE.loadFromFile("images/Plate_63_15_Blue.png"))
	{
		printf("Error loaded file");
	}
	PLATE_DYNAMIC_TEXTURE.setSmooth(true);

	if (!PLATE_CLOUD_TEXTURE.loadFromFile("images/Plate_63_15_Cloud.png"))
	{
		printf("Error loaded file");
	}
	PLATE_CLOUD_TEXTURE.setSmooth(true);

	if (!SPRING_TEXTURE.loadFromFile("images/Spring16_12.png"))
	{
		printf("Error loaded file");
	}
	SPRING_TEXTURE.setSmooth(true);
	
	if (!SPRING_2_TEXTURE.loadFromFile("images/Spring16_26.png"))
	{
		printf("Error loaded file");
	}
	SPRING_2_TEXTURE.setSmooth(true);

	startGame();
	return 0;
}