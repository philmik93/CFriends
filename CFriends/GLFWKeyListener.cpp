#include "Include.h"

GLFWKeyListener* GLFWKeyListener::instance = nullptr;


GLFWKeyListener::GLFWKeyListener() : blocked(false)
{
    for (int i = 0; i < 350; i++)
    {
        keysPressed[i] = false;
    }
}



bool GLFWKeyListener::isKeyPressed(int keycode)
{
    return get()->keysPressed[keycode];
}




GLFWKeyListener* GLFWKeyListener::get()
{
    if (instance == nullptr)
    {
        instance = new GLFWKeyListener();
    }
    return instance;
}




void GLFWKeyListener::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (get()->blocked) return;
    if (action == GLFW_PRESS)
    {
        get()->keysPressed[key] = true;
    }
    else if (action == GLFW_RELEASE)
    {
        get()->keysPressed[key] = false;
    }
}

void GLFWKeyListener::block(bool b)
{
    get()->blocked = b;
}

void GLFWKeyListener::refreshKeys()
{
	for (int i = 0; i < 350; i++)
	{
		get()->keysPressed[i] = false;
	}
}







