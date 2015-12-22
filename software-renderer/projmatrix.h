//[header]
// A simple program to demonstrate how to build and use a simple perspective projection matrix
//[/header]
//[compile]
// Download the projmatrix.cpp, vertexdata.h and geometry.h files to the same folder.
// Open a shell/terminal, and run the following command where the files are saved:
//
// c++ -o projmatrix projmatrix.cpp -std=c++11 -O3
//
// Run with: ./projmatrix. Open the file ./out.png in Photoshop or any program
// reading PPM files.
//[/compile]
//[ignore]
// Copyright (C) 2012  www.scratchapixel.com
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//[/ignore]

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include "geometry.h"
#include "vertexdata.h"

class projmatrix
{
public:
    projmatrix()
    {
        
    }
    void setProjectionMatrix(const float &angleOfView, const float &near, const float &far, Matrix44f &M);

    
    void multPointMatrix(const Vec3f &in, Vec3f &out, const Matrix44f &M);
    
    void startProjection();
    
};

