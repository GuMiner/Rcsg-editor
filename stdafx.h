/*--------------------------------------------------------------------------
    stdafx.h
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
/*--------------------------------------------------------------------------
    stdafx.h
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

// Precompiled header file to speed up compilations

// Standard C includes
#include <cstdlib>

// Data structures
#include <vector>
#include <map>

// File and console IO
#include <iostream>
#include <fstream>

// String management
#include <sstream>
#include <string>

// Time and thread management
#include <chrono>
#include <thread>

// Miscellaneous
#include <limits>
#include <memory>

// GLEW library
#include <GL/glew.h>

// GLFW library
#define GLFW_DLL 1
#include <GLFW/glfw3.h>

// General Math 'library'.
#include "gm.h"