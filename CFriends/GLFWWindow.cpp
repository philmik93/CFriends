#include "Include.h"




GLFWWindow::GLFWWindow(int width, int height, const char* title, Renderer* r, App* app) :
    Window(width, height, title, r, app), windowId(nullptr), transparency(false), refreshRate(-1)
{
    this->keyListener = GLFWKeyListener::get();
    this->mouseListener = GLFWMouseListener::get();
}

GLFWWindow::~GLFWWindow()
{
    delete  windowId;
    delete keyListener;
    delete mouseListener;
}






int GLFWWindow::init()
{
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_SAMPLES, 8);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    
    windowId = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!windowId)
    {
        glfwTerminate();
        return -1;
    }

    
    glfwSetKeyCallback(windowId, GLFWKeyListener::keyCallback);
    glfwSetCursorPosCallback(windowId, GLFWMouseListener::cursorPositionCallback);
    glfwSetMouseButtonCallback(windowId, GLFWMouseListener::mouseButtonCallback);
    glfwSetFramebufferSizeCallback(windowId, framebufferSizeCallback);
    glfwSetWindowSizeCallback(windowId, windowResizedCallback);
    // TODO: Callback erstellen
    

	const GLFWvidmode* vidMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwSetWindowPos(windowId, vidMode->width / 2 - width / 2, vidMode->height / 2 - height / 2);
    refreshRate = vidMode->refreshRate;

    glfwMakeContextCurrent(windowId);
    glfwSwapInterval(1);
    
    if (glewInit() != GLEW_OK) std::cout << "warning: cant initialize glew\n";
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION);

    renderer->init();
	

	this->app->setup();
	glfwShowWindow(windowId);
	return 0;
}





void GLFWWindow::loop()
{
    double beginTime = glfwGetTime(), endTime, deltaTime = 0.0065;
    while (!glfwWindowShouldClose(windowId))
    {

        this->renderer->prepareFrame();
        endTime = glfwGetTime();
		deltaTime = endTime - beginTime;
		beginTime = endTime;
        this->app->process(deltaTime * refreshRate);
        this->renderer->render();
        glfwSwapBuffers(windowId);
        glfwPollEvents();


		
        
    }

    glfwTerminate();
}


void GLFWWindow::run()
{
    init();
    loop();
}


bool GLFWWindow::isKeyPressed(int keycode)
{
    return keyListener->isKeyPressed(keycode);
}


float GLFWWindow::getMouseX()
{
    return this->mouseListener->getX();
}


float GLFWWindow::getMouseY()
{
    return this->mouseListener->getY();
}


bool GLFWWindow::isMousePressed()
{
    return this->mouseListener->isMousePressed();
}

bool GLFWWindow::isButtonPressed(int button)
{
    return this->mouseListener->isButtonPressed(button);
}

void GLFWWindow::setSize(int width, int height)
{
    this->width = width;
    this->height = height;
    glfwSetWindowSize(windowId, width, height);
	const GLFWvidmode* vidMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwSetWindowPos(windowId, vidMode->width / 2 - width / 2, vidMode->height / 2 - height / 2);
}

void GLFWWindow::setTitle(const char* title)
{
    this->title = title;
    glfwSetWindowTitle(windowId, title);
}

void GLFWWindow::enableTransparency(bool b)
{
    if (b != transparency)
    {
        
        glfwDestroyWindow(windowId);
        glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, b);
        transparency = b;
        keyListener->block(true);
        mouseListener->block(true);
        keyListener->refreshKeys();
        mouseListener->refreshButtons();
        init();
        keyListener->block(false);
        mouseListener->block(false);
        
    }

   
}



void GLFWWindow::framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    
   Window::mainWindow->renderer->refreshFramebuffer(width, height);

}

void GLFWWindow::windowResizedCallback(GLFWwindow* window, int width, int height)
{
    Window::mainWindow->width = width;
    Window::mainWindow->height = height;
    Window::mainWindow->renderer->refreshFramebuffer(width, height);
}








