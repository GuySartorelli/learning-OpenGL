#include <cstring>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

#include "ShaderProgram.h"
#include "Util.h"


ShaderProgram::ShaderProgram(const std::string& shaderPath)
{
	std::string vertPath = shaderPath + ".vs";
	std::string fragPath = shaderPath + ".fs";
	std::string geomPath = shaderPath + ".gs";
    if (!Util::fileExists(vertPath) || !Util::fileExists(fragPath))
    {
        throw (std::runtime_error("No vertex shader (.vs) or fragment shader (.fs) found at " + shaderPath));
    }
    if (!Util::fileExists(geomPath))
    {
        geomPath = "";
    }
    init(vertPath, fragPath, geomPath);
}

ShaderProgram::ShaderProgram(const std::string& vertPath, const std::string& fragPath)
{
	std::string geomPath = "";
    init(vertPath, fragPath, geomPath);
}

ShaderProgram::ShaderProgram(const std::string& vertPath, const std::string& fragPath, const std::string& geomPath)
{
	init(vertPath, fragPath, geomPath);
}

void ShaderProgram::init(const std::string& vertPath, const std::string& fragPath, const std::string& geomPath)
{
    GLuint vertexShaderID = createShader(GL_VERTEX_SHADER, vertPath);
    GLuint fragmentShaderID = createShader(GL_FRAGMENT_SHADER, fragPath);
    GLuint geometryShaderID = createShader(GL_GEOMETRY_SHADER, geomPath);
    link(vertexShaderID, fragmentShaderID, geometryShaderID);
}

void ShaderProgram::use()
{
    glUseProgram(ID);
}

void ShaderProgram::setBool(const std::string& name, bool value)
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void ShaderProgram::setInt(const std::string& name, int value)
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void ShaderProgram::setFloat(const std::string& name, float value)
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void ShaderProgram::setFloat(const std::string& name, float value1, float value2)
{
    glUniform2f(glGetUniformLocation(ID, name.c_str()), value1, value2);
}

void ShaderProgram::setFloat(const std::string& name, float value1, float value2, float value3)
{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), value1, value2, value3);
}

void ShaderProgram::setFloat(const std::string& name, float value1, float value2, float value3, float value4)
{
    glUniform4f(glGetUniformLocation(ID, name.c_str()), value1, value2, value3, value4);
}

GLuint ShaderProgram::createShader(GLenum type, const std::string& path)
{
    if (path.empty())
    {
        return NULL;
    }
    //setup
    std::string source;
    const GLchar* code; //needed to pull source from c_str, as stream is destroyed after try/catch
    std::ifstream file;
    //allow ifstream to throw exceptions
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    //read from file
    try
    {
    	std::stringstream stream;
        file.open(path.c_str());
        stream << file.rdbuf();
        file.close();
        source = stream.str();
    }
    catch (std::ifstream::failure& e)
    {
        //std::errno is an integer holding the most recent error number on this thread
        reportFileError(errno);
    }
    code = source.c_str();

    //shove source at GPU and compile
    GLuint shaderID = glCreateShader(type);
    glShaderSource(shaderID, 1, &code, NULL);
    glCompileShader(shaderID);

    //check for compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
        reportCompileError(std::string(infoLog), type);
    }

    return shaderID;
}

void ShaderProgram::link(GLuint vertID, GLuint fragID, GLuint geomID)
{
    this->ID = glCreateProgram();

    //attach and link
    glAttachShader(ID, vertID);
    glAttachShader(ID, fragID);
    if (geomID) glAttachShader(ID, geomID);
    glLinkProgram(ID);

    //check for linking errors
    int success;
    char infoLog[512];
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        reportLinkingError(std::string(infoLog));
    }

    //cleanup
    glDetachShader(ID, vertID);
    glDetachShader(ID, fragID);
    glDeleteShader(vertID);
    glDeleteShader(fragID);
    if (geomID)
    {
        glDetachShader(ID, geomID);
        glDeleteShader(geomID);
    }
}

void ShaderProgram::reportFileError(int errNum)
{
	std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ:\n" << strerror( errNum ) << std::endl;
}

void ShaderProgram::reportCompileError(std::string errText, GLenum type)
{
	std::string typeStr;
    switch(type)
    {
        case GL_VERTEX_SHADER:
            typeStr = "VERTEX";
            break;
        case GL_FRAGMENT_SHADER:
            typeStr = "FRAGMENT";
            break;
        case GL_GEOMETRY_SHADER:
            typeStr = "GEOMETRY";
            break;
    }
    std::cerr << "ERROR::" << typeStr << "_SHADER::COMPILE_ERROR:\n" << errText << std::endl;
}

void ShaderProgram::reportLinkingError(std::string errText)
{
	std::cerr << "ERROR::SHADER::LINKING_ERROR:\n" << errText << std::endl;
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(ID);
}
