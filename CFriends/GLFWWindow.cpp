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
    glfwSetErrorCallback(glfwErrorCallback);
    if (!glfwInit())
        return -1;




    // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char* glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif





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
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    renderer->init();
	
    if (!initImGui(glsl_version)) return -1;

	this->app->setup();
	glfwShowWindow(windowId);
	return 0;
}






int GLFWWindow::initImGui(const char* glsl_version)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    if (ImGui_ImplGlfw_InitForOpenGL(windowId, true) && ImGui_ImplOpenGL3_Init(glsl_version)) return 1;
    return 0;
}





void GLFWWindow::loop()
{
    beginTime = glfwGetTime();
    deltaTime = 0.0065;
    while (!glfwWindowShouldClose(windowId))
    {

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


        this->renderer->prepareFrame();
        endTime = glfwGetTime();
		deltaTime = endTime - beginTime;
		beginTime = endTime;
        this->app->process(deltaTime);
        this->renderer->render();



        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


        glfwSwapBuffers(windowId);
        glfwPollEvents();
		
        
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(windowId);
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

float GLFWWindow::getFPS()
{
    return 1.0 / deltaTime;
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
    Window::mainWindow->renderer->resizeWindow(width, height);
}


void GLFWWindow::glfwErrorCallback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}








