#pragma once
#define _USE_MATH_DEFINES
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <string.h>
#include <cmath>
#include <vector>
#include <random>
#include <fstream>
#include <sstream>
#include <unordered_map>


//ImGui--------------------------------------------------------

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"
#include <stdio.h>
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

// This example can also compile and run with Emscripten! See 'Makefile.emscripten' for details.
#ifdef __EMSCRIPTEN__
#include "../libs/emscripten/emscripten_mainloop_stub.h"
#endif

//-------------------------------------------------------------



#include "stb_image.h"
#include "CMatrix.h"
#include "CVector.h"
#include "GLFWKeyListener.h"
#include "GLFWMouseListener.h"
#include "App.h"
#include "Shader.h"
#include "CTexture.h"
#include "Renderer.h"
#include "OpenGLRenderer.h"
#include "Batch.h"
#include "OpenGLTexture.h"
//#include "IndexBuffer.h"
//#include "VertexBuffer.h"
//#include "VertexBufferLayout.h"
//#include "VertexArray.h"
//#include "RenderBatch.h"
//#include "RectRenderBatch.h"
//#include "DrawRectRenderBatch.h"
//#include "CircleRenderBatch.h"
//#include "DrawCircleRenderBatch.h"
//#include "LineRenderBatch.h"
//#include "ModernOpenGLRenderer.h"
#include "Window.h"
#include "GLFWWindow.h"
#include "CFriends.h"







