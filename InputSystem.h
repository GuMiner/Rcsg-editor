/*--------------------------------------------------------------------------
    InputSystem.h
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
#pragma once

#include "stdafx.h"

class InputSystem
{
    typedef struct 
    {
        bool resizeEvent;
        int newWidth, newHeight;
    } ResizeEventData;
    static ResizeEventData resizeEvent;

public:
    static bool ResizeEvent(int& width, int& height);

    static void KeyTyped(GLFWwindow *pWindow, unsigned int character); // GLFWcharfun
    static void KeyEvent(GLFWwindow *pWindow, int key, int scancode, int action, int mods); // GLFWkeyfun
    static void MouseButtonEvent(GLFWwindow *pWindow, int button, int action, int mods); // GLFWmousebuttonfun
    static void ScrollEvent(GLFWwindow *pWindow, double xDelta, double yDelta); // GLFWscrollfun
    static void CursorTravel(GLFWwindow *pWindow, int action); // GLFWcursorenterfun
    static void CursorMove(GLFWwindow *pWindow, double xNew, double yNew); // GLFWcursorposfun
    static void Resize(GLFWwindow *pWindow, int widthNew, int heightHew); // GLFWwindowsizefun
    
    static void ErrorCallback(int errCode, const char *pError); //GLFWerrorfun
    static void APIENTRY GLCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *pMessage, void *userParam);

    static void Initialize(void);
};

