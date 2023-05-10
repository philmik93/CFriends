#pragma once
#include "Include.h"
class GLFWMouseListener
{

private:
	static GLFWMouseListener* instance;
	static const int BUTTON_COUNT = 9;
	float x, y, oldX, oldY, scrollX, scrollY;
	bool buttonsPressed[BUTTON_COUNT];
	bool blocked;


public:

	static GLFWMouseListener* get();
	static float getX();
	static float getY();
	static bool isMousePressed();
	static bool isButtonPressed(int button);
	static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void block(bool b);
	static void refreshButtons();

private:
	GLFWMouseListener();
};

