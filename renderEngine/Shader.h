#ifndef SHADER_H
#define SHADER_H
#define GL_SILENCE_DEPRECATION


#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

typedef enum {
    VertexShader,
    FragmentShader,
    GeometryShader
} ShaderType;

class ShaderFile {
public:
    unsigned int shaderId;
    char *file;

    ShaderFile(std::string file, ShaderType type) {
        loadShader(file, type);
    }

    void loadShader(std::string path, ShaderType type) {
        std::string code;
        std::ifstream shaderFile;
        shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try {
            shaderFile.open(path);
            std::stringstream vShaderStream;
            vShaderStream << shaderFile.rdbuf();
            shaderFile.close();
            code = vShaderStream.str();
        } catch (std::ifstream::failure &e) {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }
        const char *vShaderCode = code.c_str();
        GLuint shaderBit;
        std::string debugType;
        switch (type) {
            case VertexShader:
                shaderBit = GL_VERTEX_SHADER;
                debugType = "VERTEX";
                break;
            case FragmentShader:
                shaderBit = GL_FRAGMENT_SHADER;
                debugType = "FRAGMENT";
                break;
            case GeometryShader:
                shaderBit = GL_GEOMETRY_SHADER;
                debugType = "GEOMETRY";
                break;
            default:
                break;
        }
        shaderId = glCreateShader(shaderBit);
        glShaderSource(shaderId, 1, &vShaderCode, NULL);
        glCompileShader(shaderId);
        checkCompileErrors(shaderId, debugType);
    }

private:
    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void checkCompileErrors(GLuint shader, std::string type) {
        GLint success;
        GLchar infoLog[1024];
        if (type != "PROGRAM") {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog
                          << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        } else {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog
                          << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }
};

class Shader {
public:
    unsigned int programID;
    ShaderFile *vertexShader;
    ShaderFile *fragmentShader;
    ShaderFile *geometryShader;

    // constructor generates the shader on the fly
    // ------------------------------------------------------------------------
    Shader(const char *vertexPath, const char *fragmentPath, const char *geometryPath = nullptr) {
        vertexShader = new ShaderFile(vertexPath, VertexShader);
        fragmentShader = new ShaderFile(fragmentPath, FragmentShader);
        geometryShader = nullptr;
        if (geometryPath != nullptr) {
            geometryShader = new ShaderFile(geometryPath, GeometryShader);
        }
        this->bindAttributes();
    }

    void bindAttributes() {
        // shader Program
        programID = glCreateProgram();
        glAttachShader(programID, vertexShader->shaderId);
        glAttachShader(programID, fragmentShader->shaderId);
        if (this->geometryShader != nullptr)
            glAttachShader(programID, geometryShader->shaderId);

        glLinkProgram(programID);
        checkCompileErrors(programID, "PROGRAM");

        // delete the shaders as they're linked into our program now and no longer necessery
        glDeleteShader(vertexShader->shaderId);
        glDeleteShader(fragmentShader->shaderId);
        if (geometryShader != nullptr)
            glDeleteShader(geometryShader->shaderId);
    }

    // activate the shader
    // ------------------------------------------------------------------------
    void use() {
        glUseProgram(programID);
    }

    void stop() {
        glUseProgram(0);
    }

    void cleanUp() {
        stop();
        glDetachShader(programID, vertexShader->shaderId);
        glDetachShader(programID, fragmentShader->shaderId);
        if (geometryShader != nullptr)
            glDetachShader(programID, geometryShader->shaderId);
        glDeleteProgram(programID);
    }

    // utility uniform functions
    // ------------------------------------------------------------------------
    void setBool(const std::string &name, bool value) const {
        glUniform1i(glGetUniformLocation(programID, name.c_str()), (int) value);
    }

    // ------------------------------------------------------------------------
    void setInt(const std::string &name, int value) const {
        glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
    }

    // ------------------------------------------------------------------------
    void setFloat(const std::string &name, float value) const {
        glUniform1f(glGetUniformLocation(programID, name.c_str()), value);
    }

    // ------------------------------------------------------------------------
    void setVec2(const std::string &name, const glm::vec2 &value) const {
        glUniform2fv(glGetUniformLocation(programID, name.c_str()), 1, &value[0]);
    }

    void setVec2(const std::string &name, float x, float y) const {
        glUniform2f(glGetUniformLocation(programID, name.c_str()), x, y);
    }

    // ------------------------------------------------------------------------
    void setVec3(const std::string &name, const glm::vec3 &value) const {
        glUniform3fv(glGetUniformLocation(programID, name.c_str()), 1, &value[0]);
    }

    void setVec3(const std::string &name, float x, float y, float z) const {
        glUniform3f(glGetUniformLocation(programID, name.c_str()), x, y, z);
    }

    // ------------------------------------------------------------------------
    void setVec4(const std::string &name, const glm::vec4 &value) const {
        glUniform4fv(glGetUniformLocation(programID, name.c_str()), 1, &value[0]);
    }

    void setVec4(const std::string &name, float x, float y, float z, float w) {
        glUniform4f(glGetUniformLocation(programID, name.c_str()), x, y, z, w);
    }

    // ------------------------------------------------------------------------
    void setMat2(const std::string &name, const glm::mat2 &mat) const {
        glUniformMatrix2fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    // ------------------------------------------------------------------------
    void setMat3(const std::string &name, const glm::mat3 &mat) const {
        glUniformMatrix3fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    // ------------------------------------------------------------------------
    void setMat4(const std::string &name, const glm::mat4 &mat) const {
        glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

private:
    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void checkCompileErrors(GLuint shader, std::string type) {
        GLint success;
        GLchar infoLog[1024];
        if (type != "PROGRAM") {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog
                          << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        } else {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog
                          << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }
};

#endif
