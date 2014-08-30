/*--------------------------------------------------------------------------
    vertex.h
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

// Just a lot of different potential vertex types
struct colorVertex
{
    float x;
    float y;
    float z;
    float r;
    float g;
    float b;

    void Set(float xx, float yy, float zz, float rr, float gg, float bb)
    {
        x = xx;
        y = yy;
        z = zz;
        r = rr;
        g = gg;
        b = bb;
    }
};