#include "../include/Shader.h"

Shader::Shader(const char* vs, const char* fs){
    int success;
    char infoLog[512];
    std::ifstream vsfile(vs), fsfile(fs);

    std::string vscode((std::istreambuf_iterator<char>(vsfile)),
    std::istreambuf_iterator<char>()),

    fscode((std::istreambuf_iterator<char>(fsfile)),
    std::istreambuf_iterator<char>());

    const GLchar *vscodesrc = vscode.c_str(), *fscodesrc = fscode.c_str();
    
    //Compile vertex shader and throw error if compile fail
    GLuint vers = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vers, 1, &vscodesrc, NULL);
    glCompileShader(vers);
    glGetShaderiv(vers, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vers, 512, NULL, infoLog);
        std::cout<<infoLog<<std::endl;
    }
    //Compile fragment shader and throw error if compile fail
    GLuint frags = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frags, 1, &fscodesrc, NULL);
    glCompileShader(frags);
    glGetShaderiv(frags, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(frags, 512, NULL, infoLog);
        std::cout<<infoLog<<std::endl;
    }

    GLuint program = glCreateProgram();
    glAttachShader(program, vers);
    glAttachShader(program, frags);
    glLinkProgram(program);
    glDeleteShader(vers);
    glDeleteShader(frags);
    program_id = program;
}

Shader::~Shader(){
    glDeleteProgram(program_id);
}

void Shader::bind(){
    glUseProgram(this->program_id);
}

void Shader::unbind(){
    glUseProgram(0);
}

GLuint Shader::getProgramId(){
    return this->program_id;
}