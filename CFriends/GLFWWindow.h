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
	double beginTime, endTime, deltaTime;
public:
	GLFWWindow(int width, int height, const char* title, Renderer* r, App* app);
	~GLFWWindow();
	int init();
	int initImGui(const char* glsl_version);
	void loop();
	void run() override;
	bool isKeyPressed(int keycode) override;
	float getMouseX() override;
	float getMouseY() override;
	bool isMousePressed() override;
	bool isButtonPressed(int button) override;
	void setSize(int width, int height) override;
	void setTitle(const char* title) override;
	void enableTransparency(bool b) override;
	float getFPS() override;
	
	
	static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
	static void windowResizedCallback(GLFWwindow* window, int width, int height);
	static void glfwErrorCallback(int error, const char* description);
};

