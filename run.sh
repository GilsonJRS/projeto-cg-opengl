#!/bin/bash

g++ src/mainApp.cpp src/Shader.cpp src/VertexBuffer.cpp src/VertexArray.cpp src/Sphere.cpp src/Electrosphere.cpp src/Camera.cpp src/Atom.cpp -lglfw -lGL -lGLEW
./a.out
rm a.out