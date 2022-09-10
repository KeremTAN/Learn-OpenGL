#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP
#include<string>
#include<unordered_map>
class ShaderProgram {
public:
    ShaderProgram();
    ~ShaderProgram();
    void attachShader(const char* fileName, unsigned int shaderType);
    void link();
    void use();
    void addUniform(const std::string& varName);
    void setFloat(const std::string& varName, float value);
private:
    std::string getShaderFromFile(const char* fileName);
    std::unordered_map<std::string, unsigned int> m_UniformVars;
    unsigned int m_ProgramId;
};
#endif