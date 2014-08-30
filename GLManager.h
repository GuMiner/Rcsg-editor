/*--------------------------------------------------------------------------
    GLManager.h
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

// Includes common OpenGL constants and utility functions.
class GLManager
{
    // Using a pointer instead of a STL unique_pointer to more delicately handle OpenGL memory.
    static GLManager *m_pManager;

    // Loads a file as a really big string.
    bool LoadString(const std::string& filename, std::string& result) const;
public:
    // General constants.
    static const int OPENGL_MAJOR = 4, OPENGL_MINOR = 0;
    static const int ALIASING_LEVEL = 1;
    static const int FPS_TARGET = 60;
    static const int TEXTURE_WH = 1024; // Texture width and height (assumed).
    static float FOV_Y, NEAR_PLANE, FAR_PLANE;
    
    // Window and operational parameters
    bool running;
    bool fullscreen;
    int width, height;
    std::string title;

    GLuint CompileShaderProgram(const char rootName []);

    // Manager initialization.
    static bool Initialize(float yFov, float nearPlane, float farPlane, bool fullscreen, int width, int height, std::string title);
    static GLManager* GetManager();
    static bool Deinitialize();
};

