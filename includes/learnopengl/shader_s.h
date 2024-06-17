#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    unsigned int ID;
    // constructor generates the shader on the fly
    // ------------------------------------------------------------------------
    Shader(const char* vertexShaderFilePath, const char* fragmentShaderFilePath)
    {
        // Read the vertex shader's source code.
        std::string vertexShaderSourceCode;
        std::ifstream vertexShaderFile;
        vertexShaderFile.open(vertexShaderFilePath);
        if (!vertexShaderFile)
        {
            std::cout << "Failed to open the vertex shader file." << std::endl;
        }
        else
        {
            std::stringstream stringStream;
            stringStream << vertexShaderFile.rdbuf();
            vertexShaderFile.close();
            vertexShaderSourceCode = stringStream.str();
        }

        // Compile the vertex shader.
        const char* rawVertexShaderSourceCode = vertexShaderSourceCode.c_str();
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &rawVertexShaderSourceCode, nullptr);
        glCompileShader(vertexShader);
        checkCompileErrors(vertexShader, "VERTEX");

        // Read the fragmentShader shader's source code.
        std::string fragmentShaderSourceCode;
        std::ifstream fragmentShaderFile;
        fragmentShaderFile.open(fragmentShaderFilePath);
        if (!fragmentShaderFile)
        {
            std::cout << "Failed to open the fragment shader file." << std::endl;
        }
        else
        {
            std::stringstream stringStream;
            stringStream << fragmentShaderFile.rdbuf();
            fragmentShaderFile.close();
            fragmentShaderSourceCode = stringStream.str();
        }

        // Compile the fragment shader.
        const char * rawFragmentShaderSourceCode = fragmentShaderSourceCode.c_str();
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &rawFragmentShaderSourceCode, NULL);
        glCompileShader(fragmentShader);
        checkCompileErrors(fragmentShader, "FRAGMENT");

        // Create a shader program.
        ID = glCreateProgram();
        glAttachShader(ID, vertexShader);
        glAttachShader(ID, fragmentShader);
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");

        // Delete the shaders as they're linked into our program now and no longer necessary.
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    // activate the shader
    // ------------------------------------------------------------------------
    void use() 
    { 
        glUseProgram(ID); 
    }

    // utility uniform functions
    // ------------------------------------------------------------------------
    void setBool(const std::string &name, bool value) const
    {         
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
    }

    void setInt(const std::string &name, int value) const
    { 
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
    }

    void setFloat(const std::string &name, float value) const
    { 
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
    }

    void setMat4(const std::string& name, const glm::mat4& mat)
    {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
    }

private:
    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void checkCompileErrors(unsigned int shader, std::string type)
    {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }
};
