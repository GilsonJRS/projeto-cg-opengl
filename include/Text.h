#ifndef TEXT_H
#define TEXT_H

//CPP libs
#include <map>
#include <iostream>
//GLEW
#define GLEW_STATIC
#include <GL/glew.h>
//GLFW
#include <GLFW/glfw3.h>
//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//freetype
#include <freetype2/ft2build.h>
#include FT_FREETYPE_H

#include "../include/VertexArray.h"
#include "../include/VertexBuffer.h"

struct Character{
    GLuint TextureID;
    glm::ivec2 Size;
    glm::ivec2 Bearing;
    GLuint Advance;
};

class Text{
    private:
        std::map<char, Character>Characters;
        VertexArray *vao;
        VertexBuffer *vbo;
    public:
        Text(
            std::string font
        );
        ~Text();
        void renderText(
            glm::mat4 view,
            glm::mat4 projection,
            glm::mat4 model,
            GLuint shader, 
            std::string text,
            float y, 
            float scale, 
            glm::vec3 color
        );

};

#endif