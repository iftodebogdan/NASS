/*
 * Screen.h
 *
 *  Created on: Jun 7, 2013
 *      Author: Bogdan
 */

#ifndef SCREEN_H_
#define SCREEN_H_

class Screen
{
public:
	void RenderTitleScreen();
	void RenderGameScreen();
	void RenderGameOverScreen();
	void SetSkillsScreenCursorPosition(unsigned newSkillsScreenCursorPosition);
	void RenderSkillsScreen();
	void RenderControlsScreen();

	void DebugScreen();

private:
	void DisplaySkillLevel(unsigned skillLevel, int posX, int posY);

	int mSkillsScreenCursor;
};

#endif /* SCREEN_H_ */
