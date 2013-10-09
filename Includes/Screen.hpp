/*
 * Screen.hpp
 *
 *  Created on: Jun 7, 2013
 *      Author: Bogdan
 */

#ifndef SCREEN_H_
#define SCREEN_H_

class Screen
{
public:
	enum ScreenState	//holds the possible states of the game
	{
		TITLE_SCREEN,		//the game is at the title screen
		GAME_SCREEN,		//the game is at the game screen
		TRANSITION_GAME_OVER_SCREEN,
		GAME_OVER_SCREEN,	//the game is at the game over screen
		SKILLS_SCREEN,		//the game is at the skills screen
		CONTROLS_SCREEN
	};

	Screen();

	void RenderTitleScreen();
	void RenderGameScreen();
	void RenderGameOverScreen();
	void SetSkillsScreenCursorPosition(unsigned newSkillsScreenCursorPosition);
	void RenderSkillsScreen();
	void RenderControlsScreen();

	void SetState(ScreenState newState);
	ScreenState GetState();

private:
	void DisplaySkillLevel(unsigned skillLevel, int posX, int posY);

	int mSkillsScreenCursor;
	ScreenState mScreenState;
};

#endif /* SCREEN_H_ */
