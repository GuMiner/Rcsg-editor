/*--------------------------------------------------------------------------
    Rcsgedit.h
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

// Main program entry point
// This program is structured around the game model, with a continually-updating display.
class Rcsgedit
{
    // Opengl window and matrixes (CPU)
    GLFWwindow *pWindow;
    float aspect;
    gm::mat4 proj_matrix, lookAt;

    // Application drawing data
    GLuint boringProgram;
    GLuint vao;
    
    // Veretx information
    GLuint pointBuffer;
    GLsizei vertexCount;

    // Transfered to the shader program.
    GLint mv_location, proj_location;
    
    void SetupViewport();
    bool WindowInitialization();
    void Render(double);

public:
    static const char* NAME;

    Rcsgedit();
    bool ApplicationSetup();
    bool RenderLoop();
    ~Rcsgedit();
};