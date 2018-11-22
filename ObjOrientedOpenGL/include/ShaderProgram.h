#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <string>

#include <glad/glad.h>

class ShaderProgram
{

    public:
        ShaderProgram(const std::string& shaderPath);
        ShaderProgram(const std::string& vertPath, const std::string& fragPath);
        ShaderProgram(const std::string& vertPath, const std::string& fragPath, const std::string& geomPath);
        void use();
        void setBool(const std::string& name, bool value);
        void setInt(const std::string& name, int value);
        void setFloat(const std::string& name, float value);
        void setFloat(const std::string& name, float value1, float value2);
        void setFloat(const std::string& name, float value1, float value2, float value3);
        void setFloat(const std::string& name, float value1, float value2, float value3, float value4);
        ~ShaderProgram();

    private:
        GLuint ID;

        void init(const std::string& vertPath, const std::string& fragPath, const std::string& geomPath);
        GLuint createShader(GLenum type, const std::string& path);
        void link(GLuint vertID, GLuint fragID, GLuint geomID);
        void reportFileError(int errNum);
        void reportCompileError(std::string errText, GLenum type);
        void reportLinkingError(std::string errText);
};

#endif // SHADERPROGRAM_H
