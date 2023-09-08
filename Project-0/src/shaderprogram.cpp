#include "shaderprogram.hpp"
#include <glad/glad.h>
#include <fstream>
#include <iostream>

ShaderProgram::ShaderProgram(){
    m_ProgramId = glCreateProgram();
}
ShaderProgram::~ShaderProgram(){
    glDeleteProgram(m_ProgramId);
}

void ShaderProgram::link(){
    glLinkProgram(m_ProgramId);
    // Check the COMPILE proccessing of SHADER
    int isLinked;
    char log[512];
    glGetProgramiv(m_ProgramId, GL_LINK_STATUS, &isLinked);
    if(!isLinked){
        glGetProgramInfoLog(m_ProgramId,512,0,log);
        std::cout<<"ERROR -> Program Linking:"<<std::endl<<log<<std::endl;
    }
}

void ShaderProgram::use(){
    glUseProgram(m_ProgramId);
}

void ShaderProgram::addUniform(const std::string& varName){
    m_UniformVars[varName] = glGetUniformLocation(m_ProgramId, varName.c_str());
}

void ShaderProgram::setFloat(const std::string& varName, float value){
    glUniform1f(m_UniformVars[varName], value);
}

void ShaderProgram::setVec3(const std::string& varName, const glm::vec3& value){
    glUniform3f(m_UniformVars[varName], value.x,value.y,value.z);
}

void ShaderProgram::setVec4(const std::string& varName, const glm::vec4& value){
    glUniform4f(m_UniformVars[varName], value.r,value.g,value.b,value.a);
}

void ShaderProgram::setMat3(const std::string& varName, const glm::mat3* ptrValue){
    glUniformMatrix3fv(m_UniformVars[varName],1,false,(GLfloat*)ptrValue);
    // f-float,v-vector(birden fazla deger gonderilecegi icin baslangic adresi)
    // 2. parametre adet sayisi
    // 3. parametre tranform islemi olacak mı
}

void ShaderProgram::attachShader(const char* fileName, unsigned int shaderType){
    unsigned int shaderId = glCreateShader(shaderType);
    std::string sourceCode = getShaderFromFile(fileName);
    const char* souceCodePtr = &sourceCode[0];
    glShaderSource(shaderId, 1, &souceCodePtr,0);
    glCompileShader(shaderId);
    // Check the COMPILE proccessing of SHADER
    int isCompiled;
    char log[512];
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);
    if(!isCompiled){
        glGetShaderInfoLog(shaderId,512,0,log);
        std::cout<<"ERROR -> Shader Type: "<<shaderType<<std::endl<<log<<std::endl;
    }
    glAttachShader(m_ProgramId,shaderId);
    glDeleteShader(shaderId);
}

std::string ShaderProgram::getShaderFromFile(const char* fileName){
    std::ifstream file(fileName);
    std::string data;
    if (file.is_open())
    {
        char readChar;
        while ((readChar=file.get())!=EOF)
        {
            data+=readChar;
        }
        file.close();    
    }
    return data; 
}