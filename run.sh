#!/bin/bash

g++ src/main.cpp src/Shader.cpp src/VertexBuffer.cpp src/VertexArray.cpp src/Sphere.cpp src/Electrosphere.cpp src/Camera.cpp src/Atom.cpp src/Texture.cpp src/stb_image.cpp src/Text.cpp -I/usr/include/freetype2 -L/usr/local/lib/ -lfreetype -lglfw -lGL -lGLEW
./a.out
rm a.out