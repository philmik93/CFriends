#pragma once
#include "Include.h"

class GLFWKeyListener
{

private:
	static GLFWKeyListener* instance;
	bool keysPressed[350];
	bool blocked;



public:
	static bool isKeyPressed(int keycode);
	static GLFWKeyListener* get();
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void block(bool b);
	static void refreshKeys();

private:
	GLFWKeyListener();

};

