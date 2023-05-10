#include "Include.h"


GLFWMouseListener* GLFWMouseListener::instance = nullptr;

GLFWMouseListener::GLFWMouseListener() : x(0), y(0), oldX(0), oldY(0), scrollX(0), scrollY(0), blocked(false)
{
	for (int i = 0; i < BUTTON_COUNT; i++)
	{
		buttonsPressed[i] = false;
	}
}


GLFWMouseListener* GLFWMouseListener::get()
{
	if (instance == nullptr)
	{
		instance = new GLFWMouseListener();
	}
	return instance;
}



float GLFWMouseListener::getX()
{
	return get()->x;
}



float GLFWMouseListener::getY()
{
	return get()->y;
}



bool GLFWMouseListener::isMousePressed()
{
	for (int i = 0; i < BUTTON_COUNT; i++)
	{
		if (get()->buttonsPressed[i]) return true;
	}
	return false;
}



bool GLFWMouseListener::isButtonPressed(int button)
{
	if (button < BUTTON_COUNT) return get()->buttonsPressed[button];
	return false;
}



void GLFWMouseListener::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	get()->oldX = get()->x;
	get()->oldY = get()->y;
	get()->x = xpos;
	get()->y = ypos;
}



void GLFWMouseListener::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		if (button < BUTTON_COUNT) get()->buttonsPressed[button] = true;
	}
	else if (action == GLFW_RELEASE)
	{
		if (button < BUTTON_COUNT) get()->buttonsPressed[button] = false;
	}
}

void GLFWMouseListener::block(bool b)
{
	get()->blocked = b;
}

void GLFWMouseListener::refreshButtons()
{
	for (int i = 0; i < BUTTON_COUNT; i++)
	{
		get()->buttonsPressed[i] = false;
	}
}
