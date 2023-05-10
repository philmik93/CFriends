#include "Include.h"

int Renderer::getWindowWidth()
{
    return window->width;
}

int Renderer::getWindowHeight()
{
    return window->height;
}

Renderer::~Renderer()
{
    delete window;
}
