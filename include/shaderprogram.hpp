#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP
#include<string>
#include<unordered_map>
#include<glm/vec3.hpp>
#include<glm/vec4.hpp>
class ShaderProgram {
public:
    ShaderProgram();
    ~ShaderProgram();
    void attachShader(const char* fileName, unsigned int shaderType);
    void link();
    void use();
    void addUniform(const std::string& varName);
    void setFloat(const std::string& varName, float value);
    void setVec3(const std::string& varName, const glm::vec3& value);
    void setVec4(const std::string& varName, const glm::vec4& value);
private:
    std::string getShaderFromFile(const char* fileName);
    std::unordered_map<std::string, unsigned int> m_UniformVars;
    unsigned int m_ProgramId;
};
#endif