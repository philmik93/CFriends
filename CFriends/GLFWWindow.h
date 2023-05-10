#pragma once
#include "Include.h"



class GLFWWindow : public Window
{
private:
	bool transparency;
	GLFWwindow* windowId;
	GLFWKeyListener* keyListener;
	GLFWMouseListener* mouseListener;
	int refreshRate;
public:
	GLFWWindow(int width, int height, const char* title, Renderer* r, App* app);
	~GLFWWindow();
	int init();
	void loop();
	void run();
	bool isKeyPressed(int keycode);
	float getMouseX();
	float getMouseY();
	bool isMousePressed();
	bool isButtonPressed(int button);
	void setSize(int width, int height);
	void setTitle(const char* title);
	void enableTransparency(bool b);
	static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
	static void windowResizedCallback(GLFWwindow* window, int width, int height);
};

