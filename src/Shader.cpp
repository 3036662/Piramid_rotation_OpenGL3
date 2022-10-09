#include "Shader.h"

Shader::Shader()
{
}

Shader::~Shader()
{
    //dtor
}


bool Shader::vertexShader(const char* vertexShaderPtr){
    vertexShader_id = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader_id, 1, &vertexShaderPtr, NULL);
    glCompileShader(vertexShader_id);
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader_id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader_id, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        return false;
    }
    return true;
}

bool Shader::fragmentShader(const char* fragmentShaderPtr){
    fragmentShader_id=glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader_id, 1, &fragmentShaderPtr, NULL);
    glCompileShader(fragmentShader_id);
    int success;
    glGetShaderiv(fragmentShader_id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader_id, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        return false;
    }
    return true;
}

bool Shader::deleteVertexShader(){
     glDeleteShader(vertexShader_id);
     return true;
}

 bool Shader::deleteFragmentShader(){
    glDeleteShader(fragmentShader_id);
    return true;
 };

 bool Shader::deleteShaders(){
    deleteVertexShader();
    deleteFragmentShader();
    return true;
 }



bool Shader::compileShaderProgram(){

    // связать шейдеры в программу
    shaderProgram_id=glCreateProgram();
    glAttachShader(shaderProgram_id, vertexShader_id);
    glAttachShader(shaderProgram_id, fragmentShader_id);
    glLinkProgram(shaderProgram_id);
    int success;
    // проверка на ошибки
    glGetShaderiv(vertexShader_id, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram_id, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        return false;
    }
    return true;
};

void Shader::deleteShaderProgram(){
    glDeleteProgram(shaderProgram_id);
}


unsigned int  Shader::getShaderProgramID(){
    return shaderProgram_id;
}

bool  Shader::useShaderProgram(){
    glUseProgram(shaderProgram_id);
    return true;
}

bool Shader::findModelMatrixLocation(const char* uniform_name){
   modelLoc=glGetUniformLocation(shaderProgram_id, uniform_name);
   if (modelLoc==-1u){return false;}
   return true;
}

bool Shader::setModelMatrix(const float* matrix_prt){
     glUniformMatrix4fv(modelLoc, 1, GL_FALSE,matrix_prt);
     return true;
}

bool Shader::findViewMatrixLocation(const char* uniform_name){
     viewLoc=glGetUniformLocation(shaderProgram_id, uniform_name);
     if (viewLoc==-1u){return false;}
     return true;
}

bool Shader::setViewMatrix(const float* matrix_prt){
     glUniformMatrix4fv(viewLoc, 1, GL_FALSE,matrix_prt);
     return true;
}

bool Shader::findProjMatrixLocation(const char* uniform_name){
      projLoc=glGetUniformLocation(shaderProgram_id, uniform_name);
     if (projLoc==-1u){return false;}
     return true;
}

bool Shader::setProjMatrix(const float* matrix_prt){
     glUniformMatrix4fv(projLoc, 1, GL_FALSE,matrix_prt);
     return true;
}


