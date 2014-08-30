/*--------------------------------------------------------------------------
    Rcsgedit.cpp
    Copyright (C) 2014 Gustave Granroth. (gus.gran@gmail.com)

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "Rcsgedit.h"
#include "GLManager.h"
#include "InputSystem.h"
#include "Vertex.h"

// OpenGL libraries
#pragma comment(lib, "opengl32")
#pragma comment(lib, "lib/glfw3dll.lib")

#ifndef _DEBUG
#pragma comment(lib, "lib/glew32.lib")
#else
#pragma comment(lib, "lib/glew32d.lib")
#endif

const char* Rcsgedit::NAME = "RCSG-Edit v1.0";

Rcsgedit::Rcsgedit()
{}

// Performs OpenGL window initialization.
bool Rcsgedit::WindowInitialization()
{
    if (!GLManager::Initialize(50.0f, 0.1f, 1000.0f, false, 1366, 768, Rcsgedit::NAME))
    {
        std::cout << "Failed to initialize the OpenGL Manager!" << std::endl;
        return false;
    }
    GLManager *pM = GLManager::GetManager();
    
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cout << "GLFW initialization failure!" << std::endl;
        return false;
    }

    // Setup GLFW

    // Window hints
    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLManager::OPENGL_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLManager::OPENGL_MINOR);
    glfwWindowHint(GLFW_SAMPLES, GLManager::ALIASING_LEVEL);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // Window creation.
    if (pM->fullscreen)
    {
        pWindow  = glfwCreateWindow(pM->width, pM->height, pM->title.c_str(), glfwGetPrimaryMonitor(), NULL);
    }
    else
    {
        pWindow  = glfwCreateWindow(pM->width, pM->height, pM->title.c_str(), NULL, NULL);
    }

    if (pWindow == NULL)
    {
        std::cout << "GLFW window creation failure: " << glewGetErrorString(glGetError()) << std::endl;
        return false;
    }
    glfwMakeContextCurrent(pWindow);
    
    // Callback initialization.
    InputSystem::Initialize();
    glfwSetCharCallback(pWindow, InputSystem::KeyTyped);
    glfwSetKeyCallback(pWindow, InputSystem::KeyEvent);
    glfwSetMouseButtonCallback(pWindow, InputSystem::MouseButtonEvent);
    glfwSetScrollCallback(pWindow, InputSystem::ScrollEvent);
    glfwSetCursorEnterCallback(pWindow, InputSystem::CursorTravel);
    glfwSetCursorPosCallback(pWindow, InputSystem::CursorMove);
    glfwSetWindowSizeCallback(pWindow, InputSystem::Resize);
    glfwSetErrorCallback(InputSystem::ErrorCallback);

    // GLEW initialization.
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        std::cout << "GLEW initialization failure: " << glewGetErrorString(err) << std::endl;
        return false;
    }
    
    // Display debug info and enable debug mode if specified.
    std::cout << "Using OpenGL vendor " << glGetString(GL_VENDOR) << ", version " << glGetString(GL_VERSION) << std::endl;
    std::cout << "  >> System uses OpenGL renderer " << glGetString(GL_RENDERER) << " <<" << std::endl;
    return true;
}

// Performs visual OpenGL setup,
bool Rcsgedit::ApplicationSetup()
{
    if (!WindowInitialization())
    {
        std::cout << "Failed to initialize the OpenGL window!" << std::endl;
        return false;
    }

    // Only works if faces are positioned appropriately, 
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    
    SetupViewport();

    // Now actually perform application-specific setup
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Setup of vertex transfer (note we're using the "vertex" object in CodeGell)
    glGenBuffers(1, &pointBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, pointBuffer);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(colorVertex), (GLvoid*)offsetof(colorVertex, x));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(colorVertex), (GLvoid*)offsetof(colorVertex, r));
    glEnableVertexAttribArray(1);

    boringProgram = GLManager::GetManager()->CompileShaderProgram("render");
    mv_location = glGetUniformLocation(boringProgram, "mv_matrix");
    proj_location = glGetUniformLocation(boringProgram, "proj_matrix");

    return true;
}

Rcsgedit::~Rcsgedit()
{
    // Application shutdown.
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &pointBuffer);

    glDeleteProgram(boringProgram);

    // Close down GLFW
    glfwDestroyWindow(pWindow);
    glfwTerminate();

}

// Sets up the drawing viewport so we don't get a weird squished display.
void Rcsgedit::SetupViewport()
{
    GLManager *pM = GLManager::GetManager();
    // Viewing aspect ratio and projection matrix.
    aspect = (float)pM->width/ (float)pM->height;
    proj_matrix = gm::Perspective(GLManager::FOV_Y, aspect, GLManager::NEAR_PLANE, GLManager::FAR_PLANE);
    glViewport(0, 0, pM->width, pM->height);
}

void Rcsgedit::Render(double currentTime)
{
    // Drop in the OpenGL data (every-single-frame) just to verify that I still know how to do this.
    colorVertex *pVertices = new colorVertex[36];
    pVertices[0].Set(-0.25f,  0.25f, -0.25f, 0.25f,  0.25f, 0.25f);
    pVertices[1].Set(-0.25f, -0.25f, -0.25f, 0.25f,  0.25f, 0.25f);
    pVertices[2].Set(0.25f, -0.25f, -0.25f, 0.25f,  0.25f, 0.25f);
        
    pVertices[3].Set(0.25f, -0.25f, -0.25f, 0.25f,  0.25f, 0.25f);
    pVertices[4].Set(0.25f,  0.25f, -0.25f, 0.25f,  0.25f, 0.25f);
    pVertices[5].Set(-0.25f,  0.25f, -0.25f, 0.25f,  0.25f, 0.25f);

    pVertices[6].Set(0.25f, -0.25f, -0.25f, 0.25f,  0.25f, 0.25f);
    pVertices[7].Set(0.25f, -0.25f,  0.25f, 0.25f,  0.25f, 0.25f);
    pVertices[8].Set(0.25f,  0.25f, -0.25f, 0.25f,  0.25f, 0.25f);

    pVertices[9].Set(0.25f, -0.25f,  0.25f, 0.25f,  0.25f, 0.25f);
    pVertices[10].Set(0.25f,  0.25f,  0.25f, 0.25f,  0.25f, 0.25f);
    pVertices[11].Set(0.25f,  0.25f, -0.25f, 0.25f,  0.25f, 0.25f);

    pVertices[12].Set(0.25f, -0.25f,  0.25f, 0.25f,  0.25f, 0.25f);
    pVertices[13].Set(-0.25f, -0.25f,  0.25f, 0.25f,  0.25f, 0.25f);
    pVertices[14].Set(0.25f,  0.25f,  0.25f, 0.25f,  0.25f, 0.25f);

    pVertices[15].Set(-0.25f, -0.25f,  0.25f, 0.25f,  0.25f, 0.25f);
    pVertices[16].Set(-0.25f,  0.25f,  0.25f, 0.25f,  0.25f, 0.25f);
    pVertices[17].Set(0.25f,  0.25f,  0.25f, 0.25f,  0.25f, 0.25f);

    pVertices[18].Set(-0.25f, -0.25f,  0.25f, 0.25f,  0.25f, 0.25f);
    pVertices[19].Set(-0.25f, -0.25f, -0.25f, 0.25f,  0.25f, 0.25f);
    pVertices[20].Set(-0.25f,  0.25f,  0.25f, 0.25f,  0.25f, 0.25f);

    pVertices[21].Set(-0.25f, -0.25f, -0.25f, 0.25f,  0.25f, 0.25f);
    pVertices[22].Set(-0.25f,  0.25f, -0.25f, 0.25f,  0.25f, 0.25f);
    pVertices[23].Set(-0.25f,  0.25f,  0.25f, 0.25f,  0.25f, 0.25f);

    pVertices[24].Set(-0.25f, -0.25f,  0.25f, 0.25f,  0.25f, 0.25f);
    pVertices[25].Set(0.25f, -0.25f,  0.25f, 0.25f,  0.25f, 0.25f);
    pVertices[26].Set(0.25f, -0.25f, -0.25f, 0.25f,  0.25f, 0.25f);

    pVertices[27].Set(0.25f, -0.25f, -0.25f, 0.25f,  0.25f, 0.25f);
    pVertices[28].Set(-0.25f, -0.25f, -0.25f, 0.25f,  0.25f, 0.25f);
    pVertices[29].Set(-0.25f, -0.25f,  0.25f, 0.25f,  0.25f, 0.25f);

    pVertices[30].Set(-0.25f,  0.25f, -0.25f, 0.25f,  0.25f, 0.25f);
    pVertices[31].Set(0.25f,  0.25f, -0.25f, 0.25f,  0.25f, 0.25f);
    pVertices[32].Set(0.25f,  0.25f,  0.25f, 0.25f,  0.25f, 0.25f);

    pVertices[33].Set(0.25f,  0.25f,  0.25f, 0.25f,  0.25f, 0.25f);
    pVertices[34].Set(-0.25f,  0.25f,  0.25f, 0.25f,  0.25f, 0.25f);
    pVertices[35].Set(-0.25f,  0.25f, -0.25f, 0.25f,  0.25f, 0.25f);
    vertexCount = 36;
    glBufferData(GL_ARRAY_BUFFER, vertexCount*sizeof(colorVertex), pVertices, GL_DYNAMIC_DRAW);

    delete [] pVertices;

    lookAt = gm::Lookat(gm::vec3(0, 0, 0), gm::vec3(0, 0, 6), gm::vec3(0, 1, 0));
    glUseProgram(boringProgram);

    const GLfloat  color[] = {0, 0, 0, 1};
    const GLfloat  one = 1.0f;
    glClearBufferfv(GL_COLOR, 0, color);
    glClearBufferfv(GL_DEPTH, 0, &one);

    gm::mat4 result = proj_matrix*lookAt;
    glUniformMatrix4fv(proj_location, 1, GL_FALSE, result);

    for (int i = 0; i < 1; i++)
    {
        for (int j = 0; j < 1; j++)
        {
            for (int k = 0; k < 1; k++)
            {
                gm::mat4 mv_matrix = gm::Rotate((float)currentTime/5.0f, gm::vec3(0.0f, 1.0f, 0.0f));
                glUniformMatrix4fv(mv_location, 1, GL_FALSE, mv_matrix);
                glDrawArraysInstanced(GL_TRIANGLES, 0, vertexCount, 100);
            }
        }
    }
}

bool Rcsgedit::RenderLoop()
{
    double timeDelta = 1.0f/(double)GLManager::FPS_TARGET;
    double lastTime = (double)glfwGetTime();
    while (GLManager::GetManager()->running)
    {
        // Draw and swap buffers
        Render(glfwGetTime());
        glfwSwapBuffers(pWindow);
       
        // Handle events.
        glfwPollEvents();
        if (glfwGetKey(pWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(pWindow))
        {
            GLManager::GetManager()->running = false;
        }

        if (InputSystem::ResizeEvent(GLManager::GetManager()->width, GLManager::GetManager()->height))
        {
            SetupViewport();
        }

        // Update timer and try to sleep for the FPS Target.
        timeDelta = (double)glfwGetTime() - lastTime;
        lastTime  = (double)glfwGetTime();

        std::chrono::milliseconds sleepTime ((int)(1.0/(double)GLManager::FPS_TARGET - 1000*timeDelta));
        if (sleepTime > std::chrono::milliseconds(0))
        {
            std::this_thread::sleep_for(sleepTime);
        }
    }

    return true;
}


// Runs the main application.
int main(int argc, char* argv [])
{
    int runStatus;
    do
    {
        std::unique_ptr<Rcsgedit> rcsgEdit(new Rcsgedit());
        runStatus = rcsgEdit->ApplicationSetup();
        if (!runStatus)
        {
            std::cout << std::endl << "Error initializing Rcsg-edit!" << std::endl;
            break;
        }
        runStatus = rcsgEdit->RenderLoop();
    } while (false);

    // Wait before closing for display purposes.
    std::cout << std::endl << "End of application. " << std::endl;
    std::chrono::milliseconds sleepTime(1000);
    std::this_thread::sleep_for(sleepTime);

    return runStatus;
}